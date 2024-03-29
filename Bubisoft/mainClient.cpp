#include "mainClient.h"
#include <iostream>
#include <thread>

#include  <mutex>
#include <condition_variable>
#include "Bubisoft_Net.hpp"
#include "Drawable.h"
#include "objects.h"
#include "Windows.h"

void MainClient::tick()
{

    while(!timerstop)
    {

if (timerevent != ((Uint32)-1)) {
    SDL_Event event;
    SDL_memset(&event, 0, sizeof(event));
    event.type = timerevent;
//    event.user.code = my_event_code;
long int* time= new long int(GetTickCount());
   event.user.data1 = (void*) time;
   // event.user.data2 = 0;
    SDL_PushEvent(&event);
}
this_thread::sleep_for(chrono::milliseconds(20));


    }


}



MainClient::MainClient(string ip,int port) {

    cout << "Init.." << endl;
    echo.setIPort(ip.c_str(),port);
    timerevent = SDL_RegisterEvents(1);
    timer=new thread(tick,this);

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




        return game_scene;//menu_scene;

}



Scene MainClient::Menu() {
cout << "Menu.." << endl;

atmos.Bubi_change_atmos("menu");

//////////////


SDL_Event e;
int i=0;
int x=200,y=200;
while(true){



		if ( SDL_PollEvent(&e) ) {
                //get event here

			if (e.type == SDL_QUIT)
				break;
			if (e.type == SDL_MOUSEMOTION)
            {
                x=e.motion.x;
                y=e.motion.y;

            }


            if(e.type==timerevent){
            //i++;
            if(GetTickCount()-*((long int*)e.user.data1)<1)
            {
            //draw menu here


            SDL_SetRenderDrawColor(renderer,0,0,0,255);
			SDL_RenderClear(renderer);
			//draw

			SDL_SetRenderDrawColor(renderer,255,255,0,255);
            Circle(renderer,20,x,y);

			//show
            SDL_RenderPresent(renderer);
            }
            else
            {
                cout<<"late"<<endl;
            }
            }



		}


}


//////////////

return game_scene;

}

Scene MainClient::Game() {
cout << "Game.." << endl;


atmos.Bubi_change_atmos("game2");
SDL_Event e;
int i=0;
int x=200,y=200;


while(true){
if ( SDL_PollEvent(&e) ) {
                //get event here

			if (e.type == SDL_QUIT)
				break;
			if (e.type == SDL_MOUSEMOTION)
            {
                x=e.motion.x;
                y=e.motion.y;

            }


            //tick time
            if(e.type==timerevent){
            //i++;
            if(GetTickCount()-*((long int*)e.user.data1)<1)
            {



            //put updated changes in com out <- this could be 2 step
            ///todo


            //(calculate stat)





            //call draw on tree
            //draw myself
            //(draw hud , stats)


            //draw menu here


            SDL_SetRenderDrawColor(renderer,0,0,0,255);
			SDL_RenderClear(renderer);
			//draw

			SDL_SetRenderDrawColor(renderer,0,100,255,255);
            Circle(renderer,20,x,y);

			//show
            SDL_RenderPresent(renderer);
            }
            else
            {
                cout<<"late"<<endl;
            }
            }
}

}

//echo.Close_Client();
//tree_updater->join();
return menu_scene;


}

Scene MainClient::Load() {
cout << "Loading.." << endl;
atmos.Bubi_change_atmos("game1");

//echo.setIPort(0,0);
//echo.Start_matchmaking();
//tree_updater = new thread(MainClient::Tree_update,this);

return game_scene;

}



void MainClient::Tree_update()
{
    vector<Bubi_package>* vec=0;
    while(echo.IsConected())
    {
    vec=echo.Pop_Bubivector();
        for(int i=0;i<vec->size();i++)
        {
               Tree_package(vec->at(i));
        }
    delete vec;
    }
    cout<<"tree_updater ended"<<endl;
}

void MainClient::Tree_package(Bubi_package p)
{

///mit csináljon a csomagokkal;
switch(p.doflag){
    case purpose::add :
        if(p.flag==Flag::player)
        {
            Player* temp= new Player(p.p_id,p.pos_x,p.pos_y,p.p_size,p.pickup_flag);
                Players.insert(pair<uint32_t,Player*>(p.p_id,temp));
        }

    break;
    case purpose::delet :

    break;
    case purpose::update :

    break;
   // case purpose::get_stat :break;
    case purpose::get_name :

        break;
    //case purpose::set_name :break;
    case purpose::stat :

    break;
   // case purpose::get_tree :break;




}





}







