#ifndef MAINLACI_HPP_INCLUDED
#define MAINLACI_HPP_INCLUDED


#include <iostream>

using namespace std;

void MainLaci()
{

    cout << "Hello Laci!" << endl;

    {


  //  SDL_Init(SDL_INIT_EVERYTHING); ///ez a 2 sor kell
    //SDLNet_Init();
/*
    IPaddress cim;
    TCPsocket socket;

    SDLNet_ResolveHost(&cim , NULL, 12345);
    socket=SDLNet_TCP_Open(&cim);
    TCPsocket client;


vector<Bubi_package> vec;
Bubi_package package;
for(int i=0;i<10;i++){
    vec.push_back(package);
}
//Bubi_Server server(12345,0);
//server.Open_Server();
char * a=new char('s');
Bubi_Client client2(a,12345);
client2.Start_matchmaking();

client2.Push_Bubivector(vec);



do
{
    client = SDLNet_TCP_Accept(socket);
    cout<<client<<endl;
}while(!client);///nem nulla 0
cout<<"csatlakozva"<<endl;
int bytesize;
unsigned int gotnumber;
char data[28];

//server.Push_Bubivector(vec);





    while(true)
    {
        bytesize = SDLNet_TCP_Recv(client,&data,28);
        //if(bytesize>0)
        std::memcpy(&gotnumber, data, 28);
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
/*
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

*/




}


Bubi_Factory F;


try{
/*
    cout<<sizeof(Bubi_package)<<endl;

    Bubi_package* package0=new Bubi_package();
    Bubi_package* package1 =(Bubi_package*) malloc(sizeof(Bubi_package));

    char* buff=(char*) malloc(sizeof (char));
   // F.to_buffer_from_array(buff,package0,1);
    //F.to_array_from_buffer(package1,buff,28);


    cout<<package0->ToString()<<endl;
    cout<<package1->ToString()<<endl;
    cout<<"----------------------"<<endl;
    //buff=(char*) malloc(sizeof (char));
    //F.to_buffer_from_array(buff,package1,1);
    //F.to_array_from_buffer(package1,buff,28);
   // cout<<package0->ToString()<<endl;
    cout<<package1->ToString()<<endl;


*/








vector<Bubi_package> vec;
Bubi_package package;
cout<<"asd:"<<package.ToString()<<endl;
for(int i=0;i<1;i++){
    vec.push_back(package);

}
/*
char* tomb;   //=(char*)malloc(28);

//F.Make_buffer_from_vector(&vec,tomb);

tomb=(char*)&vec[0];

vector<Bubi_package> *vec3;

vec3=F.Make_vector_from_buffer(tomb,28);

Bubi_package packageb=(*vec3)[0];

cout<<"vec2 | "<<packageb.ToString() <<endl;

cout<<endl;
   for(int i=0;i<28;i++){
        std::printf("%02x ", tomb[i]);
        }
*/







Bubi_Server server(12345,0);
server.Open_Server();
char * a=new char('s');
Bubi_Client client(a,12345);
client.Start_matchmaking();

this_thread::sleep_for(chrono::milliseconds(1000));
//client.Push_Bubivector(&vec);
server.Push_Bubivector(&vec);
 //cout<<"chapter"<<endl;

 vector<Bubi_package>* vec2 = client.Pop_Bubivector();
 cout<<"-----------------"<<endl;
 //server.Close_Server();
 //cout<<vec2->size()<<" merete"<<endl;
 for(Bubi_package p : *vec2){

    cout<<p.ToString()<<endl;
 }

    SDLNet_Quit();
    SDL_Quit();


cout<<"the end Laci"<<endl;
}catch(std::exception e){
    cout<<"sssssshiiiiiiithhhhhh"<<endl;
}

}


#endif // MAINLACI_HPP_INCLUDED
