#ifndef BUBI_SERVER_H_INCLUDED
#define BUBI_SERVER_H_INCLUDED

#include "Bubisoft_Net.hpp"
#include "Bubi_exceptions.h"
#include <cstring>
#include <thread>
#include <mutex>
#include <vector>
#include <list>
#include "Bubi_package.h"

class Bubi_Server
{
    Bubi_Factory factory;

    IPaddress tcp_ip;
    IPaddress udp_ip;
    TCPsocket tcp_server;
    UDPsocket udp_server;
    std::list<TCPsocket> clients;

     int package_size=1024;

    std::thread* sender;
    std::thread* receiver;
    std::thread* Accepter;
    std::thread* Broadcaster;


    std::mutex OUT_buff_M;
    std::mutex IN_buff_M;

    std::vector<std::vector<Bubi_package>> OUT_buffer;
    std::vector<std::vector<Bubi_package>> IN_buffer;

    void Broadcasting_loop(){};///TODO
    void Accepting_TCP_loop();
    void Send_Buffer();///TODO
    void Read_Buffer();///TODO

    void Sender_loop();///TODO
    void Reader_loop();///TODO

private:
    void udp_broadcast(){};///TODO

    ~Bubi_Server();
public :

    Bubi_Server(int tcp_port,int udp_port);
    bool Open_Server();
    /*{

        ///start broadcast
        ///start threds
        return true;
    }*/

};

#endif // BUBI_SERVER_H_INCLUDED
