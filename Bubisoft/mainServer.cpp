#include "mainServer.h"
#include <Bubisoft_Net.hpp>
#include <thread>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "Drawable.h"

//4#include <limits>

using namespace std;

void MainServer::start_net() {

    //Bubi_Factory F;
   // cout << numeric_limits<float>::max() << endl << "test" << endl;

   srand(time(NULL));

    try{
        vector<Bubi_package> vec;
        Bubi_package package;
        cout<<"asd:"<<package.ToString()<<endl;
        for(int i=0;i<10;i++){
            vec.push_back(package);
        }

        //Bubi_Server server(12345,0);
        server->Open_Server();
        //char * a=new char('s');
        //Bubi_Client client(a,12345);
        //client.Start_matchmaking();

        this_thread::sleep_for(chrono::milliseconds(1000));
        //client.Push_Bubivector(&vec);
        server->Push_Bubivector(&vec);
        //cout<<"chapter"<<endl;

        //server->Close_Server();
        //cout<<vec2->size()<<" merete"<<endl;
        //this_thread::sleep_for(chrono::milliseconds(500));
        while(true){
            vector<Bubi_package>* vec2 = server->Pop_Bubivector();
            cout<<"----->"<<vec2->size()<<"<-----"<<endl;
            int j=1;
            for(Bubi_package p : *vec2){
                cout<<j++;
                cout<<p.ToString()<<endl;
            }
            delete vec2;
        }

        SDLNet_Quit();
        SDL_Quit();
        }
        catch(std::exception e){
            cout<<"valami nem jo"<<endl;
        }

}

bool MainServer::check_ready() {

    for(map<uint32_t,Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if(it->second->isReady()==false) return false;
    }
    return true;
}

void MainServer::start_game() {

    while (clients.size()<2 && check_ready()) {

        cout << "client_check" << endl << endl;
        unique_lock<std::mutex> lk(server->Clients_M);
        server->Clients_C.wait(lk);
        lk.unlock();

    }

    game = true;
    gamestart = std::chrono::system_clock::now();

    while (!end_game) {
        get_values();
        calculate();
        send_values();
        if(check_end()) {
            end_game=true;
            send_end();
        }
    }
}

void MainServer::get_values() {
    reader = server->Pop_Bubivector();
    for( Bubi_package p : *reader) {
            if(p.flag==Flag::player) {
                unsigned char ch =Flag::player;
                Client* c = new Client(p.p_id,p.pos_x,p.pos_y,6,ch,p.mom_x,p.mom_y); ///default start size = 6 for players
                clients.insert(pair<uint32_t,Client*>(p.p_id,c));
                put_player(p.p_id);
                //  clients.insert(p.p_id,c)
            }
            else if(p.pickup_flag==Flag::ready) {
                clients.at(p.p_id)->setReady();
            }
            else if(clients.at(p.p_id)->isReady()){
                    if(p.flag==Flag::notset) {
                        clients.at(p.p_id)->Move(p.mom_x, p.mom_y);
                        //  clients.insert(p.p_id,c)
                    }
            }
            else if(p.flag==Flag::name) {
                Bubi_Factory bf;
                string name=bf.get_name(p);
                if(name!="not a name") {
                    clients.at(p.p_id)->setName(name);
                }
            }
            else if(p.flag==Flag::replay) {
                clients.at(p.p_id)->set_r(6);
                put_player(p.p_id);
            }
            else if(p.flag==Flag::disconn) {
                clients.at(p.p_id)->set_flag(Flag::dead);
            }
    }
    delete reader;
}

void MainServer::send_names() {
    vector<Bubi_package> *vec=0;
    Bubi_package bubi;
    for(map<uint32_t,Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if(it->second->get_pickup()!=Flag::name) continue;

        bubi.flag=Flag::name;
        bubi.p_id=it->first;
        Bubi_Factory bf;
        bf.set_name(bubi,it->second->getName());
        vec->push_back(bubi);

        it->second->set_flag(Flag::notset);
    }
    server->Push_Bubivector(vec);
}

void MainServer::calculate() {
    for(map<uint32_t,Client*>::iterator it = clients.begin(); it != clients.end(); ++it) { ///ha több, mint két másodperce volt utoljára frissítve a kliens, akkor a klienset halottnak tekintjük
        if(it->second->get_pickup()==Flag::dead) continue;
        auto start = it->second->getLastUpdate();
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = end-start;
        if(diff.count()>2000) {
            it->second->set_flag(Flag::dead);
        }
    }
    for(map<uint32_t,Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if(it->second->get_pickup()==Flag::dead) continue;
        for(uint32_t i = 0; i<UINT32_MAX; ++i) {
            if(pickups.at(i)->get_type()==0) continue;
            it->second->set_flag(pickups.at(i)->get_type());
            it->second->set_r(it->second->get_r()+pickups.at(i)->get_r());
            it->second->addPoint(pickups.at(i)->getPoint());
            pickups.at(i)->set_type(0);
        }

        for(map<uint32_t,Client*>::iterator it2 = clients.begin(); it2 != clients.end(); ++it2) {
            if(it==it2) continue;
            if(it->second->get_pickup()==Flag::immortal) continue;
            if(it2->second->get_pickup()!=Flag::dead){
                if(it->second->inside(it2->second)){
                    it2->second->set_r(it->second->get_r()+it2->second->get_r());
                    //it->second->set_r(0);
                    it->second->set_flag(Flag::dead);
                    it2->second->addPoint(it->second->get_r());
                    if(it2->second->get_pickup()==Flag::doublepoint) {
                        it2->second->addPoint(it->second->get_r());
                    }
                    break;
                }
            }
        }
        it->second->update();
    }
    for(map<uint32_t,Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        it->second->set_r(it->second->get_r()-0.01);
    }
}

void MainServer::send_values() {
    vector<Bubi_package> *vec=0;
    Bubi_package bubi;
    for(map<uint32_t,Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if(it->second->get_pickup()!=Flag::name){
            bubi.flag=it->second->get_pickup();
            bubi.pos_x=it->second->get_x();
            bubi.pos_y=it->second->get_y();
            bubi.p_size=it->second->get_r();
            bubi.p_id=it->first;
            bubi.point=it->second->getPoint();
            ///TODO - bubi feltöltése?
            vec->push_back(bubi);
        }
    }
    server->Push_Bubivector(vec);
}

bool MainServer::check_end() {
    for(map<uint32_t,Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if(it->second->getPoint()>=UINT32_MAX/2) {
            it->second->set_flag(Flag::winner);
            for(map<uint32_t,Client*>::iterator it2 = clients.begin(); it2 != clients.end(); ++it2) {
                if(it==it2) continue;
                it2->second->set_flag(Flag::game_end);
            }
            return true;
        }
    }
    std::chrono::system_clock::time_point actual_time = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = actual_time - gamestart;
    if(diff.count()>=max_game_time) {
        uint32_t max_point=0;
        map<uint32_t,Client*>::iterator winner = clients.begin();
        for(map<uint32_t,Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
            if(it->second->getPoint()>max_point) winner=it;
        }
        winner->second->set_flag(Flag::winner);
        for(map<uint32_t,Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
            if(it!=winner) it->second->set_flag(Flag::game_end);
        }
        return true;
    }

    return false;
}

void MainServer::send_end() {
    send_values();
}

void MainServer::put_player(uint32_t id) {

    while(true) {
        float pos_x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/clients.at(id)->getMax_x()));
        float pos_y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/clients.at(id)->getMax_y()));

        map<uint32_t,Client*>::iterator it;

        for(it = clients.begin(); it != clients.end(); ++it) {
            if(it->second->get_pickup()==Flag::dead) break;
            if(it->first==id) continue;
            if(it->second->inside(clients.at(id))) break;
        }

        if(it == clients.end()) {
            break;
        }
    }
}

void MainServer::conn_client() {

    cout << "conn_client" << endl << endl;

    while(!game) {
        /*reader = server->Pop_Bubivector();
        for( Bubi_package p : *reader) {
                if(p.flag==Flag::player) {
                    unsigned char ch =Flag::player;
                    Client* c = new Client(p.p_id,p.pos_x,p.pos_y,6,ch,p.mom_x,p.mom_y);
                    clients.insert(pair<uint32_t,Client*>(p.p_id,c));
                  //  clients.insert(p.p_id,c)
                }
                if(p.flag==Flag::name) {
                        Bubi_Factory bf;
                        string name=bf.get_name(p);
                        if(name!="not a name") {
                            clients.at(p.p_id)->setName(name);
                            clients.at(p.p_id)->set_flag(Flag::name);
                        }
                }
        }
        delete reader;*/
        get_values();
        send_values();
        send_names();
    }
    pickup_generator();

}

void MainServer::pickup_generator() {
    for(uint32_t i=0; i<UINT32_MAX; i++) {
        if(i<4) {
            float pos_x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1000));
            float pos_y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1000));
            int32_t point = rand() % 21 + 5;
            unsigned char flag = rand() % 4 + 11;

            PickUp *pickup = new PickUp(i,pos_x,pos_y,3,flag,point);
            pickups.insert(pair<uint32_t,PickUp*>(i,pickup));
        }
        else {
            float pos_x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1000));
            float pos_y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1000));
            int32_t point = rand() % 21 + 5;
            unsigned char flag = rand() % 4 + 11;

            PickUp *pickup = new PickUp(i,pos_x,pos_y,3,flag,point);
            pickups.insert(pair<uint32_t,PickUp*>(i,pickup));

            int sleeptime = rand() % 4001 + 1000;
            this_thread::sleep_for(chrono::milliseconds(sleeptime));
        }
    }
}

void MainServer::closepanel() {
    while(true) {
        cout << "type in close to shut down server at end of game: ";
        string s;
        cin >> s;
        if(s=="close") {
            close=true;
            break;
        }
    }
}

MainServer::MainServer() {
    cout << "mainServer" << endl << endl;

    server = new Bubi_Server(12345);

    thread t1(MainServer::start_net,this);
    //t1.join();

    thread t3(MainServer::closepanel,this);

    while(!close) {
        thread t2(MainServer::conn_client,this);
        start_game();
        t2.join();
    }

    t3.join();

    for(map<uint32_t,Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        clients.erase(it);
    }

}
