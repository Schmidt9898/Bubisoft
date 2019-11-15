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
    /// Dolgok amikkel nem t�r�dsz.
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

    /// F�gv�nyek amiket nem haszn�lsz
    Bubi_Client(TCPsocket & ready_socket);

    void Server_searching(){};
    void Connect(){};
    void CleanUp(){};
   // void Send_package(Bubi_package * tomb,unsigned int size_);


    void Sender_loop();
    void Reader_loop();
public :

    /// A f�gv�nyek amiket haszn�lhatsz.
    /// Client construktor l�trekoz egy clientet.
    ///ezt ne haszn�ld
    Bubi_Client();
    /// ip, port �s burst m�retet lehet megadni, hiba eset�n dob kiv�telt.
    Bubi_Client(const char * _ip,int _port);//throw (Cant_cast_ip_exception);
    Bubi_Client(const char * _ip,int _port,size_t burst_size);//throw (Cant_cast_ip_exception);

    /// v�ni fog a sz�lakra
    ~Bubi_Client();
    /// szerver oldali port c�m, egyedi minden clientn�l, csak csatlakozott cliensn�l �rv�nyes
    unsigned int Get_ID();
    /// atomic bool �rt�k�t n�zi, a client csatlakozott e a kiszolg�l�hoz
    bool IsConected();
    /// mennyi csomagot fogadjon max egy olvas�ssal alap 50
    void Set_burst_size(size_t size);
    /// Dobhat kiv�telt, csatlakozik a szerverre �s elind�tja az �r� olvas� sz�lakat.
    void Start_matchmaking();// Cant_connect_exception
    void Close_Client();//befejezi a komunik�ci�t

    ///kiveszi az �sszes be�rkezett csomagot a bufferb�l, felszabad�tani nem fogja
    void Push_Bubivector(std::vector<Bubi_package> *vec);
    ///beteszi a k�ld� bufferbe a vectort �s azt majd elk�ldi a szervernek a kliens, a vectort majd a k�ld� felszabad�tja
    std::vector<Bubi_package>* Pop_Bubivector();



};



#endif // BUBI_CLIENT_H_INCLUDED
