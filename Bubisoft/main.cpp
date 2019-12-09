#include <iostream>

#include "Bubisoft_Net.hpp"
#include "Bubi_Sound.h"
//#include "mainClient.h"
#include "mainServer.h"
//#include "MainLaci.hpp"

//#include "Bubi_package.h"
/*
#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_net.h>
*/
using namespace std;

int main()
{
//    char tipus;

    cout << "Hello!" << endl << endl;
     // MainLaci();
/*
    cout << "Server(s) or Client(c): ";
    cin >> tipus;

    switch(tipus) {
        case 's' : MainServer(); break;
        case 'c' : MainClient(); break;
    }
*/
/*
string ip;
    cout << "Give server address: ";
    cin >> ip;
    int port;
    cout << "Give server port: ";
    cin >> port;
MainClient Main( (ip=="0")? "localhost" : ip ,(port==0)?12345:port);   ///init
Main.Loop();

   cin >> ip;
*/
    return 0;
}
