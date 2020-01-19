#include "mainClient.h"
#include <iostream>
#include <thread>

#include  <mutex>
#include <condition_variable>
#include "Bubisoft_Net.hpp"
#include "Drawable.h"
#include "objects.h"
#include "Windows.h"

//
	#include <iostream>
    //#include "depend/include/glad/glad.h"
    #include <glad/glad.h>
    ///sets up openGl pointers
    #include "depend/include/GLFW/glfw3.h"
    #include "shader.hpp"

    #include <thread>
    #include <chrono>
    #define STB_IMAGE_IMPLEMENTATION
    #include "stb_image.h"
    #include "depend/include/glm/glm.hpp"
    #include "depend/include/glm/gtc/matrix_transform.hpp"
    #include "depend/include/glm/gtc/type_ptr.hpp"
    #include "camera.hpp"
    #include <iostream>
    #include <random>
    #include "vao.hpp"
    #include "global_variables.h"
//


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
  //  timerevent = SDL_RegisterEvents(1);
    //timer=new thread(tick,this);

}



void MainClient::Loop() {///load here everything

        atmos.Unload();
        atmos.Load_sounds("Bubi_Sounds/sound_list.txt");
       // atmos.Bubi_change_atmos("game2");
echo.Start_matchmaking();
tree_updater = new thread(MainClient::Tree_update,this);

    Bubi_package p;
    p.flag=Flag::player;
    p.p_id=echo.Get_ID();
    vector<Bubi_package> *vec = new vector<Bubi_package>();
    vec->push_back(p);
    echo.Push_Bubivector(vec);

    Bubi_package p2;
    p2.flag=Flag::ready;
    p2.p_id=echo.Get_ID();
    vector<Bubi_package> *vec3 = new vector<Bubi_package>();
    vec3->push_back(p2);
    echo.Push_Bubivector(vec3);

if(!globalGraphicsInit()) RENDER = false;
    ///MODELS / MESHES / OBJECTS

int r=0,g=0,b=0;
SDL_Event e;

    if ( RENDER )
    while (!glfwWindowShouldClose(window))
    {

    float mom_x=0;
    float mom_y=0;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);


    float cameraSpeed = 1.3 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        //cameraPos.y+= 1 * cameraSpeed;
        //global_player_positions[0].y+= 1 * cameraSpeed;
        mom_y+=0.00001;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        //cameraPos.y-=1 * cameraSpeed;
        //global_player_positions[0].y-=1 * cameraSpeed;
        mom_y-=0.00001;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        //cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        //global_player_positions[0].x -= 1 * cameraSpeed;
        mom_x-=0.00001;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        //cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
       // global_player_positions[0].x += 1 * cameraSpeed;
       mom_x+=0.00001;
    }

        if(Players.find(echo.Get_ID())!=Players.end()) {
                //cout << "Found"<< endl;
            game->update_camera(Players.at(echo.Get_ID())->get_x(),Players.at(echo.Get_ID())->get_y(),2.5*Players.at(echo.Get_ID())->get_r()/0.04);
        }  else {game->update_camera(0,0,2.5);}

        game->Draw_map();

        for(map<uint32_t,PickUp*>::iterator it = pickups.begin(); it != pickups.end(); ++it) {
            game->Draw_pickup(it->second->get_x(),it->second->get_y(),255,255,255);
        }
        for(map<uint32_t,Player*>::iterator it = Players.begin(); it != Players.end(); ++it) {
                game->Draw_player(it->second->get_x(), it->second->get_y(), it->second->get_r(), 255,255,255);
        }
        game->Draw_player(0,0,0.06,255,255,255);
        game->Draw_player(0.2,0.2,0.06,255,255,255);
      //  game->Show();



     //  game->Draw_menu();
        game->Show();
        //std::this_thread::sleep_for(std::chrono::milliseconds(20));

        Bubi_package p;
        p.flag=Flag::notset;
        p.p_id=echo.Get_ID();
        p.mom_x=mom_x;
        p.mom_y=mom_y;
        vector<Bubi_package> *vec = new vector<Bubi_package>();
        vec->push_back(p);
        echo.Push_Bubivector(vec);
    }

    game->cleanup();
    delete game;
    tree_updater->join();




//Scene scene=game_scene;
/*
while(scene!=close_game)
{
    switch(scene){///you can change scene by returning enum ,same thread
    case setup_scene: scene = Setup(); break;
    case menu_scene: scene = Menu(); break;
    case game_scene: scene = Game(); break;
   // case load_scene: scene = Load(); break;
    }

}

*/
   cout << "exit game.." << endl;
            if(swindow)
                SDL_DestroyWindow(swindow);
            if(srenderer)
                SDL_DestroyRenderer(srenderer);

    atmos.Stop();
    timer->join();

}

/*
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


*/
/*
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
*/
/*
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


}*/
/*
Scene MainClient::Load() {
cout << "Loading.." << endl;
atmos.Bubi_change_atmos("game1");

//echo.setIPort(0,0);
//echo.Start_matchmaking();
//tree_updater = new thread(MainClient::Tree_update,this);

return game_scene;

}

*/

void MainClient::Tree_update()
{
   // cout << "Tree update in" << endl;
    vector<Bubi_package>* vec=0;
    while(echo.IsConected())
    {
        //cout << "Tree to update" << endl;
    vec=echo.Pop_Bubivector();
        for(int i=0;i<vec->size();i++)
        {
               Tree_package(vec->at(i));
              // cout << "Tree updated" << endl;
        }
    delete vec;
    }
    cout<<"tree_updater ended"<<endl;
}

void MainClient::Tree_package(Bubi_package p) {

///mit csináljon a csomagokkal;
    last_update = std::chrono::system_clock::now();
    if(p.flag==Flag::player && Players.find(p.p_id)==Players.end())
    {
        Player* temp= new Player(p.p_id,p.pos_x,p.pos_y,p.p_size,p.pickup_flag);
        Players.insert(pair<uint32_t,Player*>(p.p_id,temp));
    }
    else if(Players.find(p.p_id)!=Players.end()) {
            cout << p.ToString() << endl;
    switch(p.flag) {
        case Flag::notset :
            Players.at(p.p_id)->update(p.pos_x,p.pos_y,p.p_size,p.pickup_flag,p.point);
            break;
        case Flag::dead :
            Players.erase(p.p_id);
            break;
        case Flag::pickup :
            if(pickups.find(p.p_id)==pickups.end()) {
                PickUp *pickup = new PickUp(p.p_id,p.pos_x,p.pos_y,p.p_size,p.flag,p.point);
                pickups.insert(pair<uint32_t,PickUp*>(p.p_id,pickup));
            }
            break;
        case Flag::dead_flag :
            if(pickups.find(p.p_id)!=pickups.end()) {
                pickups.erase(p.p_id);
            }
            break;
        case Flag::ready :
            if(Players.find(p.p_id)!=Players.end()) {
                Players.at(p.p_id)->setReady(true);
            }
            break;
        case Flag::not_ready :
            if(Players.find(p.p_id)!=Players.end()) {
                Players.at(p.p_id)->setReady(false);
            }
            break;
    }
    } else {
        Player* temp= new Player(p.p_id,p.pos_x,p.pos_y,p.p_size,p.pickup_flag);
        Players.insert(pair<uint32_t,Player*>(p.p_id,temp));
    }

}
