#ifndef BUBI_CLIENT_H_INCLUDED
#define BUBI_CLIENT_H_INCLUDED

#include "Bubisoft_Net.hpp"
#include "Bubi_exceptions.h"
#include "Bubi_package.h"
#include <cstring>
#include <thread>
#include <mutex>
#include <vector>
class Bubi_Client
{
   // char Bubi_ID=0;/// 1 byte
    bool connected=false;

    Bubi_Factory factory;

    IPaddress tcp_ip;
    IPaddress udp_ip;
    TCPsocket tcp_socket;
    UDPsocket udp_socket;

    int package_size=1024;

    std::thread* sender;
    std::thread* receiver;
    std::thread* searcher;

    std::mutex OUT_buff_M;
    std::mutex IN_buff_M;

    std::vector<std::vector<Bubi_package>> OUT_buffer;
    std::vector<std::vector<Bubi_package>> IN_buffer;


    Bubi_Client(TCPsocket & ready_socket);
    ~Bubi_Client();
    void Server_searching();
    void Connect();
    void CleanUp();
    void Send_Buffer();
    void Read_Buffer();
public :

    Bubi_Client() {};

    Bubi_Client(char * _ip,int _port);



    void Start_matchmaking() throw (Cant_cast_ip_exception);

    void Push_Bubivector(std::vector<Bubi_package> &vec);
    std::vector<Bubi_package>* Pop_Bubivector();



};



#endif // BUBI_CLIENT_H_INCLUDED
