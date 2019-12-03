#include "mainClient.h"
#include <iostream>
#include <thread>
#include "Bubisoft_Net.hpp"
#include "Drawable.h"

void MainClient::Start() {

    Bubi_Factory F;


        while(true){
          ///true main
        }



}

MainClient::MainClient(string ip,int port) {

    cout << "Setup.." << endl;
    echo.setIPort(ip.c_str(),port);


}
