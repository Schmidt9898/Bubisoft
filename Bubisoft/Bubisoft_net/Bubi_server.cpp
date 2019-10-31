#include "Bubi_server.h"

 Bubi_Server::~Bubi_Server(){
    ///Legyen vége a szálaknak.
    sender->join();
    receiver->join();
    Accepter->join();
    Broadcaster->join();
///TODO bővíteni
    }

Bubi_Server::Bubi_Server(int tcp_port,int udp_port)
    {

        SDLNet_ResolveHost(&tcp_ip,NULL,tcp_port);
        SDLNet_ResolveHost(&udp_ip,NULL,udp_port);

    }
bool Bubi_Server::Open_Server(){
    tcp_server=SDLNet_TCP_Open(&tcp_ip);

    if(!tcp_server){
        return false;
    }
/* not ready
    udp_server=SDLNet_UDP_Open(11111);

    if(!udp_server){
        return false;
    }
Broadcaster= new std::thread(Bubi_server::Broadcasting_loop,this);

*/

Accepter =  new std::thread(Bubi_Server::Accepting_TCP_loop,this);




 return true;
}

 void Bubi_Server::Accepting_TCP_loop()
{
TCPsocket client;

while(true){

    client = SDLNet_TCP_Accept(tcp_server);
    if(!client)
    {
        //levéd
        clients.push_back(client);
        //felold
    }



}


}
