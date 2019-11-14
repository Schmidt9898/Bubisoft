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
    /// Dolgok amikkel nem törõdsz.
    uint32_t Bubi_ID=0;
     std::atomic_bool connected{false};
     std::atomic_bool run{true};

    Bubi_Factory factory;

    IPaddress tcp_ip;
    IPaddress udp_ip;
    TCPsocket tcp_socket;
    UDPsocket udp_socket;

    uint16_t package_size=sizeof(Bubi_package)*50;

    std::thread* sender;
    std::thread* receiver;
    std::thread* searcher;

    std::mutex OUT_buff_M;
    std::mutex IN_buff_M;

    std::condition_variable OUT_buff_C;
    std::condition_variable IN_buff_C;

    std::vector<std::vector<Bubi_package>*> OUT_buffer;
    std::vector<std::vector<Bubi_package>*> IN_buffer;

    /// Fügvények amiket nem használsz
    Bubi_Client(TCPsocket & ready_socket);

    void Server_searching(){};
    void Connect(){};
    void CleanUp(){};
   // void Send_package(Bubi_package * tomb,unsigned int size_);


    void Sender_loop();
    void Reader_loop();
public :

    /// A fügvények amiket használhatsz.
    /// Client construktor létrekoz egy clientet.
    ///ezt ne használd
    Bubi_Client();
    /// ip, port és burst méretet lehet megadni, hiba esetén dob kivételt.
    Bubi_Client(const char * _ip,int _port);//throw (Cant_cast_ip_exception);
    Bubi_Client(const char * _ip,int _port,size_t burst_size);//throw (Cant_cast_ip_exception);

    /// váni fog a szálakra
    ~Bubi_Client();
    /// szerver oldali port cím, egyedi minden clientnél, csak csatlakozott cliensnél érvényes
    unsigned int Get_ID();
    /// atomic bool értékét nézi, a client csatlakozott e a kiszolgálóhoz
    bool IsConected();
    /// mennyi csomagot fogadjon max egy olvasással alap 50
    void Set_burst_size(size_t size);
    /// Dobhat kivételt, csatlakozik a szerverre és elindítja az író olvasó szálakat.
    void Start_matchmaking();// Cant_connect_exception
    void Close_Client();//befejezi a komunikációt

    ///kiveszi az összes beérkezett csomagot a bufferbõl, felszabadítani nem fogja
    void Push_Bubivector(std::vector<Bubi_package> *vec);
    ///beteszi a küldõ bufferbe a vectort és azt majd elküldi a szervernek a kliens, a vectort majd a küldõ felszabadítja
    std::vector<Bubi_package>* Pop_Bubivector();



};



#endif // BUBI_CLIENT_H_INCLUDED
