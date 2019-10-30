#include <iostream>
#include "Bubisoft_Net.hpp"
//#include "Bubi_package.h"
/*
#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_net.h>
*/
using namespace std;

int main()
{

    cout << "Hello world!" << endl;

  //  SDL_Init(SDL_INIT_EVERYTHING); ///ez a 2 sor kell
    //SDLNet_Init();
/*
    IPaddress cim;
    TCPsocket socket;

    SDLNet_ResolveHost(&cim , NULL, 12345);
    socket=SDLNet_TCP_Open(&cim);
    TCPsocket client;
do
{
    client = SDLNet_TCP_Accept(socket);
    cout<<client<<endl;
}while(!client);///nem nulla 0
cout<<"csatlakozva"<<endl;
int bytesize;
unsigned int gotnumber;
char data[4];
    while(true)
    {
        bytesize = SDLNet_TCP_Recv(client,&data,4);
        //if(bytesize>0)
        std::memcpy(&gotnumber, data, 4);
        cout<<data<<" - "<<sizeof(data);
        cout<<" ["<<gotnumber<<"] the number";
        cout<<" "<<bytesize<<endl;





        if(bytesize<0)
        {

            cout<<SDLNet_GetError()<<endl;
            break;
        }
       // char * msg= "valasz\n";
        //cout<<msg<<endl;
        //SDLNet_TCP_Send(client,msg,8);

    }
*/
/*

    cout << "whats next? 1: server 2:client" << endl;
    int code = -1;
    cin>>code;
    cout<< "the code : "<<code<<" selected"<<endl;
try{

    switch (code)
    {
        case 1:



        break;
        case 2:
            Bubi_Client client;
            client.Start_matchmaking();
        break;

     //   default :
       //     cout<<"error"<<endl;


    }
}catch (Cant_cast_ip_exception e)
{
    cout<<"error"<<endl;
}
*/
//Bubi_package package;
cout<<sizeof(Bubi_package)<<endl;
Bubi_package p;
cout<<sizeof(Bubi_name_package)<<endl;
//Bubi_name_package
char * buff = new char[28];

//std::memcpy(buff, &p, 28);

//cout<<*buff<<endl;
cout<<p.ToString()<<endl;
//bool t[8];
//cout<<sizeof(t) <<endl;









    SDLNet_Quit();
    SDL_Quit();


cout<<"the end"<<endl;




    return 0;
}
