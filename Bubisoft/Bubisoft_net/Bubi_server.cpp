#include "Bubi_server.h"

 Bubi_Server::~Bubi_Server(){
    ///Legyen v�ge a sz�laknak.
    sender.join();
    receiver.join();
    searcher.join();

    }

Bubi_Server::Bubi_Server(int tcp_port,int udp_port)
    {

        SDLNet_ResolveHost(&tcp_ip,NULL,tcp_port);
        SDLNet_ResolveHost(&udp_ip,NULL,udp_port);
    }
