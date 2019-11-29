#include <iostream>
#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_mixer.h>
#include "Bubi_Sound.h"
using namespace std;

int main()
{
/*
    if(SDL_Init(SDL_INIT_AUDIO)==-1) {
    printf("SDL_Init: %s\n", SDL_GetError());
    exit(1);
}///ha használsz sdl-t akkor ezt a sort szedd ki.

if(Mix_Init(MIX_INIT_MP3)==-1) {
    printf("mix_Init: %s\n", SDL_GetError());
    exit(1);
}
    //Mix_Init(MIX_INIT_MP3);
       cout << "Hello world!" << endl;

    if((Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,2048)) <0)
       cout<<"mix hiba"<<endl;
       string path_head="Sounds/";
    Mix_Music * music=Mix_LoadMUS((path_head+"Bish.mp3").c_str());//
    if(!music) {
    printf("Mix_LoadMUS(\"Bish.mp3\"): %s\n", Mix_GetError());
    }
    // this might be a critical error...*//*
    Mix_Chunk * metal=Mix_LoadWAV("test.wav");
    Mix_Chunk * test1=Mix_LoadWAV("Sounds/channel_created.wav");
    Mix_Chunk * test2=Mix_LoadWAV("Sounds/channel_deleted.wav");



 //  if( Mix_PlayMusic(music,1)<0) cout<< Mix_GetError()<<endl;
   //Mix_PlayChannel(1,metal,1);
   Mix_PlayChannel(0,test1,1);
   Mix_PlayChannel(1,test2,0);


   //  string ss;
  //  cin>>ss;
   // Mix_FadeOutMusic(1000);

   while(true){
    int vol;
    cin>>vol;
     Mix_PlayChannel(1,test2,0);
/*
   if(ss=="stop")
    Mix_Pause(1);

   if(ss=="resu")
    Mix_Resume(1);

    if(ss=="fo")
    Mix_FadeOutChannel(1,1000);

    if(ss=="fi")
    Mix_FadeInChannelTimed(1,metal,1,1000,1);

*//*
//Mix_VolumeMusic(vol);
Mix_Volume(-1,vol);
   if(vol==-1)
    break;



   }



    Mix_FreeChunk(metal);
    Mix_FreeChunk(test1);
    Mix_FreeChunk(test2);
    Mix_FreeMusic(music);

    music=nullptr;
    metal=nullptr;

     test2=nullptr;
     test1=nullptr;

    Mix_Quit();
    SDL_Quit();

*/

Bubi_Sound sound;
sound.Load_sounds("Sounds/sound_list.txt");




sound.Volume(50);



sound.Bubi_change_atmos(menu);

while(true){

 string ss;
cin>>ss;
sound.Bubibip("created");
sound.Bubi_change_atmos(loading);
sound.Bubi_change_atmos(game);

sound.Bubibip("deleted");///<- itt már igen
if(ss=="exit")
    break;


}







    return 0;
}
