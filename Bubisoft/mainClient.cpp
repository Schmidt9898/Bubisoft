#include "mainClient.h"
#include <iostream>
#include <thread>

#include  <mutex>
#include <condition_variable>
#include "Bubisoft_Net.hpp"
#include "Drawable.h"
#include "objects.h"

void tick(Uint32 timerevent)
{

    while(true)
    {

if (timerevent != ((Uint32)-1)) {
    SDL_Event event;
    SDL_memset(&event, 0, sizeof(event));
    event.type = timerevent;
//    event.user.code = my_event_code;
//   event.user.data1 = significant_data;
    event.user.data2 = 0;
    SDL_PushEvent(&event);
}
this_thread::sleep_for(chrono::milliseconds(20));
    }


}



MainClient::MainClient(string ip,int port) {

    cout << "Init.." << endl;
    echo.setIPort(ip.c_str(),port);
    timerevent = SDL_RegisterEvents(1);
    timer=new thread(tick,timerevent);
}



void MainClient::Loop() {///load here everithing
Scene scene=setup_scene;
while(scene!=close_game)
{
    switch(scene){///you can change scene by returning enum ,same thread
    case setup_scene: scene = Setup(); break;
    case menu_scene: scene = Menu(); break;
    case game_scene: scene = Game(); break;
   // case load_scene: scene = Load(); break;
    }

}
   cout << "exit game.." << endl;
            if(window)
                SDL_DestroyWindow(window);
            if(renderer)
                SDL_DestroyRenderer(renderer);

    atmos.Stop();
    timer->join();

}


Scene MainClient::Setup() {///load here everithing
cout << "Setup.." << endl;

        atmos.Unload();
        atmos.Load_sounds("Bubi_Sounds/sound_list.txt");

        if(window)
                SDL_DestroyWindow(window);
        if(renderer)
            SDL_DestroyRenderer(renderer);


        window = SDL_CreateWindow(
        "Dwendallan",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        width,                               // width, in pixels
        hight,                               // height, in pixels
        0                  // flags - see below
    );

        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC);




        return menu_scene;

}



Scene MainClient::Menu() {
cout << "Menu.." << endl;

//atmos.Bubi_change_atmos("menu");

//////////////


SDL_Event e;
int i=0;
int x=200,y=200;
while(true){



		if ( SDL_PollEvent(&e) ) {
			if (e.type == SDL_QUIT)
				break;
			if (e.type == SDL_MOUSEMOTION)
            {
                x=e.motion.x;
                y=e.motion.y;

            }


            if(e.type==timerevent){
            i++;
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
			SDL_RenderClear(renderer);
			//draw

			SDL_SetRenderDrawColor(renderer,255,255,0,255);
            Circle(renderer,20,x,y);

			//show
            SDL_RenderPresent(renderer);

            }



		}


}


//////////////

return game_scene;

}

Scene MainClient::Game() {
cout << "Game.." << endl;


//atmos.Bubi_change_atmos("game2");

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

Scene MainClient::Load() {
cout << "Load.." << endl;
atmos.Bubi_change_atmos("game1");

/*
while(true){
    SDL_Event e;
		if ( SDL_PollEvent(&e) ) {
			if (e.type == SDL_QUIT)
				break;
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
				break;
		}

}
*/



return close_game;

}









