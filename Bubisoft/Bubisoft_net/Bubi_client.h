#ifndef BUBI_CLIENT_H_INCLUDED
#define BUBI_CLIENT_H_INCLUDED

#include "Bubisoft_Net.hpp"
#include "Bubi_exceptions.h"
#include "Bubi_package.h"
#include <cstring>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <atomic>
class Bubi_Client
{
    uint32_t Bubi_ID=0;/// 4 byte a packageből
     std::atomic_bool connected{false};
     std::atomic_bool run{true};

    Bubi_Factory factory;

    IPaddress tcp_ip;
    IPaddress udp_ip;
    TCPsocket tcp_socket;
    UDPsocket udp_socket;

    int package_size=28;

    std::thread* sender;
    std::thread* receiver;
    std::thread* searcher;

    std::mutex OUT_buff_M;
    std::mutex IN_buff_M;

    std::condition_variable OUT_buff_C;
    std::condition_variable IN_buff_C;

    std::vector<std::vector<Bubi_package>> OUT_buffer;
    std::vector<std::vector<Bubi_package>> IN_buffer;


    Bubi_Client(TCPsocket & ready_socket);

    void Server_searching(){};
    void Connect(){};
    void CleanUp(){};
    void Send_package(Bubi_package * tomb,unsigned int size_);

   //void Send_to_client(TCPsocket &tcp_socket,Bubi_package * tomb,unsigned int size_);
    //void Read_Buffer();
    void Sender_loop();
    void Reader_loop();
public :

    Bubi_Client() {};

    Bubi_Client(char * _ip,int _port);
~Bubi_Client();
    unsigned int Get_ID();
    bool IsConected();

    void Start_matchmaking();// throw (Cant_cast_ip_exception);
    void Close_Client();

    void Push_Bubivector(std::vector<Bubi_package> &vec);
    std::vector<Bubi_package>* Pop_Bubivector();



};



#endif // BUBI_CLIENT_H_INCLUDED
