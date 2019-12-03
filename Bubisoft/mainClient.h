#ifndef MAINCLIENT_H_INCLUDED
#define MAINCLIENT_H_INCLUDED

#include <string>
#include "Bubisoft_Net.hpp"

using namespace std;

class MainClient {

    Bubi_Client echo;



    public:
        MainClient(string ip,int port);
        void Start();

};

#endif // MAINCLIENT_H_INCLUDED
