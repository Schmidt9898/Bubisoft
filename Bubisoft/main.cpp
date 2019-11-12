#include <iostream>

#include "Bubisoft_Net.hpp"
//#include "mainClient.h"
#include "mainServer.h"
#include "MainLaci.hpp"

//#include "Bubi_package.h"
/*
#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_net.h>
*/
using namespace std;

int main()
{
    char tipus;

    cout << "Hello!" << endl << endl;
      MainLaci();
  /*  cout << "Server(s) or Client(c): ";
    cin >> tipus;

    switch(tipus) {
        case 's' : MainServer(); break;
        case 'c' : MainClient(); break;
    }
    cout << endl << "Waiting for character..." << endl;*/
    string c;
    cin>>c;

    return 0;
}
