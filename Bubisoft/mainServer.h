#ifndef MAINSERVER_H_INCLUDED
#define MAINSERVER_H_INCLUDED

#include <map>
#include <stdint.h>

using namespace std;

class MainServer
{
    struct client {
        float pos_x, pos_y;
        float mom_x, mom_y;
        int32_t p_size;
        bool ready;
    };

    bool end_game=false;

    map<uint32_t,client> clients;

    void start_net();

    bool check_ready();
    void start_game();

    void get_values();
    void calculate();
    void send_values();

    bool check_end();
    void send_end();

    public: MainServer();

};

#endif // MAINSERVER_H_INCLUDED
