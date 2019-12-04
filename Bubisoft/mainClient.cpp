#include "mainClient.h"
#include <iostream>
#include <thread>
#include "Bubisoft_Net.hpp"
#include "Drawable.h"



MainClient::MainClient(string ip,int port) {

    cout << "Init.." << endl;
    echo.setIPort(ip.c_str(),port);

}



void MainClient::Loop() {///load here everithing
Scene scene=setup_scene;
while(scene!=close_game)
{
    switch(scene){///you can change scene by returning enum ,same thread
    case setup_scene: scene = Setup(); break;
    case menu_scene: scene = Menu(); break;
    case game_scene: scene = Game(); break;
    case load_scene: scene = Load(); break;
    }

}
   cout << "exit game.." << endl;

}


Scene MainClient::Setup() {///load here everithing
cout << "Setup.." << endl;
        atmos.Load_sounds("Bubi_Sounds/sound_list.txt");
        ///load graf

        return menu_scene;

}



Scene MainClient::Menu() {
cout << "Menu.." << endl;

atmos.Bubi_change_atmos("menu");
/*

        while(true){
          ///true main
        }
*/
string a;
cin >> a;
return game_scene;

}

Scene MainClient::Game() {
cout << "Game.." << endl;


atmos.Bubi_change_atmos("game2");


/*
        while(true){
          ///true main
        }
*/

string a;
cin >> a;
return load_scene;


}

Scene MainClient::Load() {
cout << "Load.." << endl;
atmos.Bubi_change_atmos("game1");
/*
        while(true){
          ///true main
        }
*/
string a;
cin >> a;
return close_game;

}









