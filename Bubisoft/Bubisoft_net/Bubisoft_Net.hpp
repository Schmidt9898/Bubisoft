#ifndef BUBISOFT_NET_HPP_INCLUDED
#define BUBISOFT_NET_HPP_INCLUDED

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_net.h>

#include "Bubi_exceptions.h"
//#include <string>
#include "Bubi_client.h"
#include "Bubi_server.h"
//#include "Bubi_package.h"
class BUBISOFT_NET
{
///init lefut main elött.

  public:BUBISOFT_NET();
/*
    static void initial()
    {
        SDL_Init(SDL_INIT_EVERYTHING);///ha használsz sdl-t akkor ezt a sort szedd ki.
        SDLNet_Init();
    }

    friend struct init_0_0_1;
///belsõ valtozók
protected:

IPaddress ip;
TCPsocket socket;
bool conected=false;

char * OUT_buffer;
char * IN_buffer;

public:
    BUBISOFT_NET();

    //bool isConected(){return conected;}

    virtual ~BUBISOFT_NET(){};
    virtual get_controlMatrix()=0;
    virtual send_controlMatrix()=0;
    virtual end_connection()=0;

*/

};
/*
struct init_0_0_1
{
    init_0_0_1()
    {
        BUBISOFT_NET::initial();
    }
};
extern init_0_0_1 __1;

*/



#endif // BUBISOFT_NET_HPP_INCLUDED
