#include <mainClient.h>
#include <iostream>
#include <thread>
#include <Bubisoft_Net.hpp>

void MainClient::start_net(string ip) {

    Bubi_Factory F;

    try{
        vector<Bubi_package> vec;
        Bubi_package package;
        cout<<"asd:"<<package.ToString()<<endl;
        for(int i=0;i<10;i++){
            vec.push_back(package);
        }

        //Bubi_Server server(12345,0);
        //server.Open_Server();
        //char * a=new char('s');
        Bubi_Client client(ip.c_str(),12345);
        client.Start_matchmaking();

        this_thread::sleep_for(chrono::milliseconds(1000));
        client.Push_Bubivector(&vec);
        //server.Push_Bubivector(&vec);
        //cout<<"chapter"<<endl;

        //server.Close_Server();
        //cout<<vec2->size()<<" merete"<<endl;
        //this_thread::sleep_for(chrono::milliseconds(500));
        while(true){
            vector<Bubi_package>* vec2 = client.Pop_Bubivector();
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

MainClient::MainClient() {

    cout << "mainClient" << endl << endl;
    cout << "Give server address: ";
    string ip;
    cin >> ip;

    thread th1(MainClient::start_net,this,ip);
    th1.join();

}