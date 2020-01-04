#ifndef MAINCLIENT_H_INCLUDED
#define MAINCLIENT_H_INCLUDED

#include <string>
#include <map>
#include "Bubisoft_Net.hpp"
#include "Drawable.h"
#include "Bubi_Sound.h"
//#include <SDL_image.h>

using namespace std;

enum Scene
{
    setup_scene,
    menu_scene,
    game_scene,
    load_scene,
    close_game
};

class MainClient {


    string username = "Larry";
    int volume=50;
    int sound_volume=100;
    int music_volume=100;
    int width=800;
    int hight=600;


    Bubi_Factory F;
    Bubi_Sound atmos;
    Bubi_Client echo;

    thread * tree_updater=nullptr;
    //bool updaterstop=false;

    SDL_Window* swindow=NULL;
    SDL_Renderer *srenderer = NULL;
	//SDL_Texture *img = NULL;
	Uint32 timerevent=0;
    thread *timer;
    bool timerstop=false;



    map<uint32_t,Drawable*> Entities;
    map<uint32_t,Player*> Players;

    void Tree_update();
    void Tree_package(Bubi_package);
    void tick();

    public:
        MainClient(string ip,int port);
        void Loop();
        Scene Setup();//destroy and rebuild window
        Scene Menu();//draw and navigate menu
        Scene Game();//draw game

        Scene Load();//

};




#endif // MAINCLIENT_H_INCLUDED
