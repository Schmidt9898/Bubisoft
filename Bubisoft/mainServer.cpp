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

  // srand (static_cast <unsigned> (time(NULL)));
   //cout << "Teszt" << endl;

   //try{
      //  vector<Bubi_package> vec;
      //  Bubi_package package;
        /*cout<<package.ToString()<<endl;
        for(int i=0;i<10;i++){
            vec.push_back(package);
        }*/

        //Bubi_Server server(12345,0);
       // server->Open_Server();
        //char * a=new char('s');
        //Bubi_Client client(a,12345);
        //client.Start_matchmaking();

       // this_thread::sleep_for(chrono::milliseconds(1000));
        //client.Push_Bubivector(&vec);
        //server->Push_Bubivector(&vec);
        //cout<<"chapter"<<endl;

        //server->Close_Server();
        //cout<<vec2->size()<<" merete"<<endl;
        //this_thread::sleep_for(chrono::milliseconds(500));
       // while(true){
           /* vector<Bubi_package>* vec2 = server->Pop_Bubivector();
            //cout<<"----->"<<vec2->size()<<"<-----"<<endl;
            int j=1;
            for(Bubi_package p : *vec2){
            //    cout<<j++;
            //    cout<<p.ToString()<<endl;
            }
            delete vec2;*/
       // }

      //  SDLNet_Quit();
       // SDL_Quit();
       // }
       // catch(std::exception e){
       //     cout<<"valami nem jo"<<endl;
      //  }

}

bool MainServer::check_ready() {

    for(map<uint32_t,Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if(it->second->isReady()==false) return false;
    }
    return true;
}

void MainServer::start_game() {
    //cout << "test" << endl;

  /*  while (clients.size()<2 && check_ready()) {

        cout << "client_check" << endl << endl;
        unique_lock<std::mutex> lk(server->Clients_M);
        server->Clients_C.wait(lk);
        lk.unlock();

    }
*/
    readerthread = new thread(get_values,this);
    game = true;
    gamestart = std::chrono::system_clock::now();

    while (!end_game) {

        //cout << "asd" << endl;
       // get_values();
       treeM.lock();
        calculate();
        send_values();
        treeM.unlock();
         this_thread::sleep_for(chrono::milliseconds(10));

       /* if(check_end()) {
            end_game=true;
            send_end();
        }*/
    }
}

void MainServer::get_values() {
    //cout << "values" << endl;
    while(true){///TODO ne legyen true
this_thread::sleep_for(chrono::milliseconds(10));
    reader = server->Pop_Bubivector();
    //cout<<reader->size()<<endl;
treeM.lock();
    for( Bubi_package p : *reader) {
           // cout << p.ToString() << endl;
            if(p.flag==Flag::player && clients.find(p.p_id) == clients.end()) {
                unsigned char ch =Flag::dead;
                Client* c = new Client(p.p_id,p.pos_x,p.pos_y,ch,p.mom_x,p.mom_y); ///default start size = 0.06 for players
                clients.insert(pair<uint32_t,Client*>(p.p_id,c));
                clients.at(p.p_id)->set_r(0.06);
                put_player(p.p_id);
                send_pickups_again=true;
                //  clients.insert(p.p_id,c)
                continue;
            }

            if(clients.find(p.p_id)!=clients.end()) {
                   // cout << "Found" << endl;

               /* if(p.flag==Flag::ready) {
                    clients.at(p.p_id)->setReady();
                    //cout << "Ready" << endl;
                }*/
                //else
               // if(clients.at(p.p_id)->isReady()){
                    //if(p.flag==Flag::notset) {
                        clients.at(p.p_id)->update_Move(p.mom_x, p.mom_y);
                      //  clients.at(p.p_id)->update_Move(0.001, 0.001);
                        //cout << "Moving" << endl;
                        //  clients.insert(p.p_id,c)
                   // }
                }
                else if(p.flag==Flag::name) {
                    Bubi_Factory bf;
                    string name=bf.get_name(p);
                    if(name!="not a name") {
                        clients.at(p.p_id)->setName(name);
                    }
                }
                else if(p.pickup_flag==Flag::replay) {
                    clients.at(p.p_id)->set_r(0.06);
                    put_player(p.p_id);
                    clients.at(p.p_id)->setPoint(0);
                }
                else if(p.flag==Flag::disconn) {
                    clients.at(p.p_id)->set_flag(Flag::dead);
                }

    }
   // calculate();
   // send_values();
    treeM.unlock();
    delete reader;
    }
}

void MainServer::send_names() {
    vector<Bubi_package> *vec = new vector<Bubi_package>;
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
    if(vec->size()!=0) {
        //cout << "Sending names" << endl;
        server->Push_Bubivector(vec);
    } else delete vec;
}

void MainServer::calculate() {
    for(map<uint32_t,Client*>::iterator it = clients.begin(); it != clients.end(); ++it) { ///ha több, mint két másodperce volt utoljára frissítve a kliens, akkor a klienset halottnak tekintjük
        if(it->second->get_pickup()==Flag::dead) continue;
        auto start = it->second->getLastUpdate();
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = end-start;
        if(diff.count()>2000) {
            it->second->set_flag(Flag::dead);
            continue;
        }
        it->second->Move_one();

         if(it->second->get_r()>0.05) {
            it->second->set_r(it->second->get_r()-0.000005);
        }
    }

    for(map<uint32_t,Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
           Client* player=it->second;
        if(player->get_pickup()==Flag::dead) continue;
       // cout << "client"  << endl;
        for(map<uint32_t,PickUp*>::iterator it2 = pickups.begin(); it2 != pickups.end(); ++it2) {
            PickUp* food=it2->second;
            if(food->get_type()==Flag::notset) continue;
            if(food->get_type()==Flag::dead_pickup) continue;
            //cout << "pickup" << endl;
            if(food->inside(player)) {
                player->set_pickup(food->get_type());
                player->set_r(player->get_r()+0.01);
                //cout << "méret" << endl;
                player->addPoint(food->getPoint());
                if(player->get_pickup()==Flag::doublepoint) {
                    player->addPoint(food->getPoint());
                }
                food->set_type(Flag::dead_pickup);
                food->playerakimegevett=player->get_id();
            }
        }

        for(map<uint32_t,Client*>::iterator it2 = clients.begin(); it2 != clients.end(); ++it2) {
                Client* player2=it2->second;
            if(player==player2) continue;
            if(player->get_pickup()==Flag::immortal) continue;
            if(player2->get_pickup()!=Flag::dead){
                if(player->inside(player2)){
                        if(player->get_pickup()==Flag::killpill)
                        {

                            player->set_r(0.1+player->get_r());
                    //it->second->set_r(0);
                    player2->set_flag(Flag::dead);
                    player->addPoint(20);
                    player->set_pickup(Flag::food);

                        }else{
                    player2->set_r(player->get_r()+player2->get_r());
                    //it->second->set_r(0);
                    player->set_flag(Flag::dead);
                    player->mykillerid=player2->get_id();
                    player2->addPoint((int32_t)player->get_r()*100);
                    if(player2->get_pickup()==Flag::doublepoint) {
                        player2->addPoint((int32_t)player->get_r()*100);
                    }
                        }

                    break;
                }
            }
        }
        player->update();
    }
   /* for(map<uint32_t,Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        //it->second->Move();

    }*/
}

void MainServer::send_values() {
    vector<Bubi_package> *vec = new vector<Bubi_package>();
    Bubi_package bubi;
    for(map<uint32_t,Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if(it->second->get_pickup()!=Flag::name){
                ///if(kell még)
            bubi.pickup_flag=it->second->get_pickup();
        //cout<<bubi.pickup_flag;
            bubi.pos_x=it->second->get_x();
            bubi.pos_y=it->second->get_y();
           // cout << to_string(it->second->get_r());
            bubi.p_size=it->second->get_r();
            bubi.p_id=it->first;
            bubi.point=it->second->getPoint();
            bubi.flag=Flag::player;
            bubi.bringflag=(unsigned char)it->second->mykillerid;
            //cout << bubi.ToString() << endl;
            ///TODO - bubi feltöltése?
            vec->push_back(bubi);
           /* if(it->second->get_pickup()==Flag::player) {
                it->second->set_flag(Flag::notset);
            }*/
        }
    }
if(send_pickups_again){
    for(map<uint32_t,PickUp*>::iterator it = pickups.begin(); it != pickups.end(); ++it) {
        if(it->second->get_type()==Flag::notset) {
            bubi.flag=Flag::dead_pickup;

        } else {
            bubi.flag=Flag::pickup;
        }
        bubi.pickup_flag=it->second->get_type();
        //cout << bubi.flag << endl;
        //cout << bubi.ToString() << endl;
        bubi.pos_x=it->second->get_x();
        bubi.pos_y=it->second->get_y();
        bubi.p_size=it->second->get_r();
        bubi.p_id=it->first;
        bubi.point=it->second->getPoint();
        ///TODO - bubi feltöltése?
        vec->push_back(bubi);
    }
    send_pickups_again=false;
    }
    generatormonitor.lock();

    if(newpicup!=nullptr){
    vec->insert(vec->end(),newpicup->begin(),newpicup->end());
    newpicup=nullptr;///nézd át és gondolt át mégegyszer
    }
    generatormonitor.unlock();


    vector<uint32_t> id_torol;
    for(map<uint32_t,PickUp*>::iterator it = pickups.begin(); it != pickups.end(); ++it) {
        if(it->second->get_type()==Flag::dead_pickup || it->second->get_type()==Flag::notset) {
                id_torol.push_back(it->first);
        }
    }

    PickUp* temp=nullptr;
    for(int i=0;i<id_torol.size();i++)
    {
        temp= pickups.at(id_torol[i]);
        pickups.erase(id_torol[i]);

        bubi.flag=Flag::pickup;
        bubi.p_id=temp->get_id();
        bubi.bringflag=(unsigned char)temp->playerakimegevett;
        bubi.pickup_flag=Flag::dead_pickup;

        vec->push_back(bubi);
        delete temp;
    }

    if(vec->size()!=0) {
        //cout << "Sending" << endl;
        server->Push_Bubivector(vec);
    }

     vector<uint32_t> player_torol;
    for(map<uint32_t,Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if(it->second->get_pickup()==Flag::dead) {
                player_torol.push_back(it->first);
        }
    }
    Client* temp2=nullptr;
    for(int i=0;i<player_torol.size();i++)
    {

         temp2= clients.at(player_torol[i]);
        clients.erase(player_torol[i]);

        delete temp2;
    }






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
            if(it->second->getPoint()>max_point) {
                winner=it;
                max_point=it->second->getPoint();
            }
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
        float pos_x = clients.at(id)->getMin_x() + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(clients.at(id)->getMax_x()-clients.at(id)->getMin_x())));
        float pos_y = clients.at(id)->getMin_y() + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(clients.at(id)->getMax_y()-clients.at(id)->getMin_y())));
        clients.at(id)->setPosition(pos_x,pos_y);

        map<uint32_t,Client*>::iterator it;

        for(it = clients.begin(); it != clients.end(); ++it) {
            if(it->second->get_pickup()==Flag::dead) continue;
            if(it->first==id) continue;
            if(clients.at(id)->inside(it->second)) break;
        }

        if(it == clients.end()) {
            clients.at(id)->set_flag(Flag::player);
            clients.at(id)->set_pickup(Flag::notset);
            clients.at(id)->setPoint(0);
            break;
        }
    }
}

void MainServer::conn_client() {

   ///cout << "conn_client" << endl << endl;

   // while(!game) {
        /*reader = server->Pop_Bubivector();
        for( Bubi_package p : *reader) {
                if(p.flag==Flag::player) {
                    unsigned char ch =Flag::player;
                    Client* c = new Client(p.p_id,p.pos_x,p.pos_y,0.06,ch,p.mom_x,p.mom_y);
                    clients.insert(pair<uint32_t,Client*>(p.p_id,c));
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
        /*get_values();
        send_values();
        send_names();
    }
    pickup_generator();*/

}

void MainServer::pickup_generator() {
    uint32_t picid=0;
    for(int i=0;i<20;i++)
    {
        float pos_x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/20)) -10;
            float pos_y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/20)) -10;
            while((pow(pos_x,2)+pow(pos_y,2))>=70) {
                pos_x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/20)) -10;
                pos_y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/20)) -10;
            }

            unsigned char flag;
            int32_t point = 5;

            if((rand() % 16)==0){
            flag=Flag::immortal;
            point+=2;
            }
            else if((rand() % 8)==0){
            flag=Flag::doublepoint;
            point*=2;
            }
            else if((rand() % 4)==0){
            flag=Flag::food1;
            point++;
            }
            else
            flag=Flag::food;


            PickUp *pickup = new PickUp(picid,pos_x,pos_y,0.04,flag,point);


               generatormonitor.lock();
            if(newpicup==nullptr)
            {
                newpicup=new vector<Bubi_package>();
            }
            Bubi_package bubi;
            bubi.flag=Flag::pickup;
        bubi.pickup_flag=pickup->get_type();
        bubi.pos_x=pickup->get_x();
        bubi.pos_y=pickup->get_y();
        bubi.p_size=pickup->get_r();
        bubi.p_id=pickup->get_id();
        bubi.point=pickup->getPoint();
        ///TODO - bubi feltöltése?
        newpicup->push_back(bubi);





            generatormonitor.unlock();



            pickups.insert(pair<uint32_t,PickUp*>(picid,pickup));
            picid++;

    }
while(true){
    if(pickups.size()<30) {


            float pos_x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/15)) -7;
            float pos_y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/15)) -7;
            while((pow(pos_x,2)+pow(pos_y,2))>=70) {
                pos_x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/15)) -7;
                pos_y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/15)) -7;
                //cout<<"+";
            }
            //cout<<endl;

            unsigned char flag;
            int32_t point = 5;
            if((rand() % 16)==0){
            flag=Flag::killpill;
            point+=2;
            }
            else if((rand() % 16)==0){
            flag=Flag::immortal;
            point+=2;
            }
            else if((rand() % 8)==0){
            flag=Flag::doublepoint;
            point*=2;
            }
            else if((rand() % 4)==0){
            flag=Flag::food1;
            point++;
            }
            else
            flag=Flag::food;



            /*
            switch(rflag) {
                case 1: flag=Flag::food;
                    break;
                case 2: flag=Flag::food1;
                    break;
                case 3: flag=Flag::immortal;
                    break;
                case 4: flag=Flag::doublepoint;
                    break;
            }*/
            PickUp *pickup = new PickUp(picid,pos_x,pos_y,0.04,flag,point);

            generatormonitor.lock();
            if(newpicup==nullptr)
            {
                newpicup=new vector<Bubi_package>();
            }
            Bubi_package bubi;
            bubi.flag=Flag::pickup;
        bubi.pickup_flag=pickup->get_type();
        bubi.pos_x=pickup->get_x();
        bubi.pos_y=pickup->get_y();
        bubi.p_size=pickup->get_r();
        bubi.p_id=pickup->get_id();
        bubi.point=pickup->getPoint();
        ///TODO - bubi feltöltése?
        newpicup->push_back(bubi);





            generatormonitor.unlock();

            pickups.insert(pair<uint32_t,PickUp*>(picid,pickup));
            picid++;


    }
      int sleeptime = rand() % 2000 + 1000;
            this_thread::sleep_for(chrono::milliseconds(sleeptime));
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
    //cout << "mainServer" << endl << endl;

    server = new Bubi_Server(12345);
server->Open_Server();
this_thread::sleep_for(chrono::milliseconds(100));
   // thread t1(MainServer::start_net,this);
    //t1.join();

   // thread t3(MainServer::closepanel,this);

  //  while(!close) {
        thread t2(MainServer::pickup_generator,this);

        start_game();
        t2.join();
   // }

  SDLNet_Quit();
        SDL_Quit();
    //t3.join();

    for(map<uint32_t,Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        clients.erase(it);
    }

}
