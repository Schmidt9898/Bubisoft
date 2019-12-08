#ifndef MAINCLIENT_H_INCLUDED
#define MAINCLIENT_H_INCLUDED

#include <string>
#include <map>
#include "Bubisoft_Net.hpp"
#include "Drawable.h"
#include "Bubi_Sound.h"
#include <SDL_image.h>

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

    Bubi_Factory F;
    Bubi_Sound atmos;
    Bubi_Client echo;

    string username = "Larry";
    int volume=50;
    int sound_volume=100;
    int music_volume=100;
    int width=800;
    int hight=600;

    SDL_Window* window=NULL;
    //SDL_Renderer *renderer = NULL;
	//SDL_Texture *img = NULL;




    map<uint32_t,Drawable*> Entities;
    map<uint32_t,Player*> Players;

    public:
        MainClient(string ip,int port);
        void Loop();
        Scene Setup();
        Scene Menu();
        Scene Game();
        Scene Load();

};




#endif // MAINCLIENT_H_INCLUDED
