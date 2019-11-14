#ifndef BUBI_SERVER_H_INCLUDED
#define BUBI_SERVER_H_INCLUDED

#include "Bubisoft_Net.hpp"
#include "Bubi_exceptions.h"
#include <cstring>
#include <thread>
#include <mutex>
#include <vector>
#include <list>
#include <condition_variable>
#include "Bubi_package.h"
#include <atomic>


class Bubi_Server
{


    Bubi_Factory factory;

    IPaddress tcp_ip;
    IPaddress udp_ip;
    TCPsocket tcp_server;
    UDPsocket udp_server;

    std::list<TCPsocket> clients;
    std::vector<std::thread*> Readers;

    int package_size=sizeof(Bubi_package)*50;

    std::atomic_bool run{true};
    //bool run=true;


    std::thread* Sender;
    //std::thread* receiver;
    std::thread* Accepter;
    std::thread* Broadcaster;




    std::mutex OUT_buff_M;
    std::mutex IN_buff_M;

    std::condition_variable OUT_buff_C;
    std::condition_variable IN_buff_C;

    std::vector<std::vector<Bubi_package>*> OUT_buffer;
    std::vector<std::vector<Bubi_package>*> IN_buffer;

    void Broadcasting_loop() {}; ///TODO
    void Accepting_TCP_loop();
    //void Send_package(Bubi_package * tomb,unsigned int size_);
    //void Read_Buffer();///TODO

    void Sender_loop();
    //void Reader_loop();
    void Reader_loop(TCPsocket client);

    void udp_broadcast() {}; ///TODO


public :

    ~Bubi_Server();
    ///Csak létrehozza a szervert ,+ paraméterezni lehet
     Bubi_Server(int tcp_port);
    Bubi_Server(int tcp_port,size_t burst_size);
    Bubi_Server(int tcp_port,int udp_port,size_t burst_size);
    /**Elindítja szervert, a küldést és a fogadást
    true ha sikeresen elindul false ha nem
    */
    bool Open_Server();
    ///Vége a szervernek.
    void Close_Server();
    ///kiveszi az összes beérkezett csomagot a bufferbõl, felszabadítani nem fogja
    void Push_Bubivector(std::vector<Bubi_package> *vec);
    ///beteszi a küldõ bufferbe a vectort és azt majd elküldi az összes kliensnek, a vectort majd a küldõ felszabadítja
    std::vector<Bubi_package>* Pop_Bubivector();


};






#endif // BUBI_SERVER_H_INCLUDED
