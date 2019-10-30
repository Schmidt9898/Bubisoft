#ifndef BUBI_SERVER_H_INCLUDED
#define BUBI_SERVER_H_INCLUDED

#include "Bubisoft_Net.hpp"
#include "Bubi_exceptions.h"
#include <cstring>
#include <thread>
#include <mutex>
#include <vector>
#include "Bubi_package.h"

class Bubi_Server
{
    IPaddress tcp_ip;
    IPaddress udp_ip;
    TCPsocket tcp_socket;
    UDPsocket udp_socket;
    SDLNet_SocketSet clients;

    std::thread sender;
    std::thread receiver;
    std::thread searcher;





private:
    void udp_broadcast()
    {


    }





    ~Bubi_Server(){
    ///Legyen vége a szálaknak.
    sender.join();
    receiver.join();
    searcher.join();

    }

public :
    Bubi_Server(int tcp_port,int udp_port)
    {
        clients=SDLNet_AllocSocketSet(3);
        SDLNet_ResolveHost(&tcp_ip,NULL,tcp_port);
        SDLNet_ResolveHost(&udp_ip,NULL,udp_port);
    }
    bool Open_Server()
    {

        ///start broadcast
        ///start threds
        return true;
    }

};

#endif // BUBI_SERVER_H_INCLUDED
