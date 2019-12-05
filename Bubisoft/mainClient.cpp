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
            if(window)
                SDL_DestroyWindow(window);

    atmos.Stop();

}


Scene MainClient::Setup() {///load here everithing
cout << "Setup.." << endl;

        atmos.Unload();
        if(window)
                SDL_DestroyWindow(window);
        atmos.Load_sounds("Bubi_Sounds/sound_list.txt");
        ///load graf
        window = SDL_CreateWindow(
        "Dwendallan",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        width,                               // width, in pixels
        hight,                               // height, in pixels
        0                  // flags - see below
    );
 /*   renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
img = IMG_LoadTexture(renderer, "Drawable/Background.png");
if(!img)
    cout<<SDL_GetError();*/



        return menu_scene;

}



Scene MainClient::Menu() {
cout << "Menu.." << endl;

atmos.Bubi_change_atmos("menu");

//////////////


while(true){
    SDL_Event e;
		if ( SDL_PollEvent(&e) ) {
			if (e.type == SDL_QUIT)
				break;
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
				break;
		}

}


//////////////

return game_scene;

}

Scene MainClient::Game() {
cout << "Game.." << endl;


atmos.Bubi_change_atmos("game2");

while(true){
    SDL_Event e;
		if ( SDL_PollEvent(&e) ) {
			if (e.type == SDL_QUIT)
				break;
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
				break;
		}

}

return load_scene;


}

Scene MainClient::Load() {
cout << "Load.." << endl;
atmos.Bubi_change_atmos("game1");


while(true){
    SDL_Event e;
		if ( SDL_PollEvent(&e) ) {
			if (e.type == SDL_QUIT)
				break;
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
				break;
		}

}




return close_game;

}









