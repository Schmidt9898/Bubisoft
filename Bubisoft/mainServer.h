#ifndef MAINSERVER_H_INCLUDED
#define MAINSERVER_H_INCLUDED

#include <map>
#include <stdint.h>
#include <Bubisoft_Net.hpp>
#include "Drawable.h"
#include <chrono>
#include <mutex>
#include <vector>

using namespace std;

class MainServer
{
private:

    Bubi_Server *server = nullptr;

    std::chrono::system_clock::time_point gamestart;
    double max_game_time = 15*60*1000;

    /*struct client {
        float pos_x, pos_y;
        float mom_x, mom_y;
        int32_t p_size;
        bool ready;
    };*/

    bool end_game = false;
    bool game = false;
    bool close = false;

    vector<Bubi_package>* reader;

    map<uint32_t,Client*> clients;
    map<uint32_t,PickUp*> pickups;

    vector<Bubi_package>* newpicup=nullptr;
    mutex generatormonitor;
    bool send_pickups_again=false;
    void start_net();
    void conn_client();
    void put_player(uint32_t);
    void pickup_generator();

    bool check_ready();
    void start_game();

    void get_values();
    void calculate();
    void send_values();
    void send_names();

    bool check_end();
    void send_end();

    void closepanel();

    const int timeout = 2000;

    public: MainServer();

};

#endif // MAINSERVER_H_INCLUDED
