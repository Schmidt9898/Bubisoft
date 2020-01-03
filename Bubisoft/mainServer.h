#ifndef MAINSERVER_H_INCLUDED
#define MAINSERVER_H_INCLUDED

#include <map>
#include <stdint.h>
#include <Bubisoft_Net.hpp>
#include "Drawable.h"

using namespace std;

class MainServer
{
private:

    Bubi_Server *server = nullptr;

    /*struct client {
        float pos_x, pos_y;
        float mom_x, mom_y;
        int32_t p_size;
        bool ready;
    };*/

    bool end_game = false;
    bool game = false;

    vector<Bubi_package>* reader;

    map<uint32_t,Client*> clients;

    void start_net();
    void conn_client();
    void put_player(uint32_t);

    bool check_ready();
    void start_game();

    void get_values();
    void calculate();
    void send_values();
    void send_names();

    bool check_end();
    void send_end();

    const int timeout = 20000;

    public: MainServer();

};

#endif // MAINSERVER_H_INCLUDED
