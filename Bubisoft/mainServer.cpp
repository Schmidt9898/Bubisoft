#include <mainServer.h>
#include <Bubisoft_Net.hpp>
#include <thread>
#include <iostream>

//4#include <limits>

using namespace std;

void MainServer::start_net() {

    Bubi_Factory F;
   // cout << numeric_limits<float>::max() << endl << "test" << endl;

    try{
        vector<Bubi_package> vec;
        Bubi_package package;
        cout<<"asd:"<<package.ToString()<<endl;
        for(int i=0;i<10;i++){
            vec.push_back(package);
        }

        Bubi_Server server(12345,0);
        server.Open_Server();
        char * a=new char('s');
        //Bubi_Client client(a,12345);
        //client.Start_matchmaking();

        this_thread::sleep_for(chrono::milliseconds(1000));
        //client.Push_Bubivector(&vec);
        server.Push_Bubivector(&vec);
        //cout<<"chapter"<<endl;

        //server.Close_Server();
        //cout<<vec2->size()<<" merete"<<endl;
        //this_thread::sleep_for(chrono::milliseconds(500));
        while(true){
            vector<Bubi_package>* vec2 = server.Pop_Bubivector();
            cout<<"----->"<<vec2->size()<<"<-----"<<endl;
            int j=1;
            for(Bubi_package p : *vec2){
                cout<<j++;
                cout<<p.ToString()<<endl;
            }
        }

        SDLNet_Quit();
        SDL_Quit();
        }
        catch(std::exception e){
            cout<<"valami nem jo"<<endl;
        }

}

bool MainServer::check_ready() {

    for(map<uint32_t,client>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if(it->second.ready==false) return false;
    }

    return true;
}

void MainServer::start_game() {
}

MainServer::MainServer() {
    cout << "mainServer" << endl << endl;

    thread t1(MainServer::start_net,this);
    t1.join();

}
