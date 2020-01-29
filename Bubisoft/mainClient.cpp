#include "mainClient.h"
#include <iostream>

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
    #include <math.h>
//

/*
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
*/


MainClient::MainClient(string ip,int port) {

    cout << "Init.." << endl;
    echo.setIPort(ip.c_str(),port);
  //  timerevent = SDL_RegisterEvents(1);
    //timer=new thread(tick,this);

}



void MainClient::Loop() {///load here everything

        atmos.Unload();
        atmos.Load_sounds("Bubi_Sounds/sound_list.txt");
        atmos.Volume_atmos(64);
        atmos.Volume_bip(128);
       // atmos.Bubi_change_atmos("game1");
echo.Start_matchmaking();
myid=echo.Get_ID();
tree_updater = new thread(MainClient::Tree_update,this);
 vector<Bubi_package> *vec = new vector<Bubi_package>();

    Bubi_package p;
    p.flag=Flag::player;
    p.p_id=echo.Get_ID();

    vec->push_back(p);
    echo.Push_Bubivector(vec);

if(!globalGraphicsInit()) RENDER = false;
    ///MODELS / MESHES / OBJECTS
//atmos.Bubi_change_atmos("game1");
int r=0,g=0,b=0;
SDL_Event e;

    if ( RENDER )
    while (!glfwWindowShouldClose(window))
    {
        /*Bubi_package p3;
        p3.flag=Flag::replay;
        p3.p_id=echo.Get_ID();
        vector<Bubi_package> *vec2 = new vector<Bubi_package>();
        vec->push_back(p3);
        vec->push_back(p3);
        echo.Push_Bubivector(vec2);

        Bubi_package p2;
        p2.flag=Flag::ready;
        p2.p_id=echo.Get_ID();
        vector<Bubi_package> *vec3 = new vector<Bubi_package>();
        vec3->push_back(p2);
        echo.Push_Bubivector(vec3);
*/
        gamebool = true;

        while(gamebool) {

            float mom_x=0;
            float mom_y=0;

            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, true);


            float cameraSpeed = 1.3 * deltaTime;
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
                //cameraPos.y+= 1 * cameraSpeed;
                //global_player_positions[0].y+= 1 * cameraSpeed;
                mom_y+=0.001;
            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
                //cameraPos.y-=1 * cameraSpeed;
                //global_player_positions[0].y-=1 * cameraSpeed;
                mom_y-=0.001;
            }
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
                //cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
                //global_player_positions[0].x -= 1 * cameraSpeed;
                mom_x-=0.001;
            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
                //cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
                //global_player_positions[0].x += 1 * cameraSpeed;
                mom_x+=0.001;
            }

          /*  if(Players.find(echo.Get_ID())!=Players.end()) {
                //cout << "Found"<< endl;

            }  else {game->update_camera(0,0,2.5);}
*/
            game->Draw_map();

        m.lock();
            for(map<uint32_t,PickUp*>::iterator it = pickups.begin(); it != pickups.end(); ++it) {
                PickUp* temp=it->second;

                    switch(temp->get_type())
                    {
                   case Flag::food :
                       game->Draw_player(temp->get_x(),temp->get_y(),temp->get_r(),255,179,0);
                    break;
                   case Flag::food1 :
                       game->Draw_player(temp->get_x(),temp->get_y(),temp->get_r(),76,200,0);
                    break;
                   case Flag::immortal :
                       game->Draw_player(temp->get_x(),temp->get_y(),temp->get_r(),0,255,242);
                    break;
                   case Flag::doublepoint :
                       game->Draw_player(temp->get_x(),temp->get_y(),temp->get_r(),255,255,100);
                    break;
                   case Flag::dead_pickup:

                    break;
                   default:
                       game->Draw_player(temp->get_x(),temp->get_y(),temp->get_r(),0,0,0);
                    break;

                    }


            }

            for(map<uint32_t,Player*>::iterator it = Players.begin(); it != Players.end(); ++it) {
                           Player* temp=it->second;
               // if(temp->get_pickup()==Flag::dead) continue;
                if(temp->get_id()==myid)
                {
                    game->Draw_player(temp->get_x(), temp->get_y(), temp->get_r(), 20,255,20);
                    game->update_camera(temp->get_x(), temp->get_y(),3.5+2*temp->get_r());
                }else
                {
                game->Draw_player(temp->get_x(), temp->get_y(), temp->get_r(), 255,20,10);
                }

                switch(temp->get_pickup())
                    {
                   case Flag::food :
                       game->Draw_pickup(temp->get_x(),temp->get_y(),255,179,0);
                    break;
                   case Flag::food1 :
                       game->Draw_pickup(temp->get_x(),temp->get_y(),76,200,0);
                    break;
                   case Flag::immortal :
                       game->Draw_pickup(temp->get_x(),temp->get_y(),0,255,242);
                    break;
                   case Flag::doublepoint :
                       game->Draw_pickup(temp->get_x(),temp->get_y(),255,255,100);
                    break;
                   default:
                      // game->Draw_player(temp->get_x(),temp->get_y(),temp->get_r()/2,0,0,0);
 //cout<<temp->get_pickup();
                    break;

                    }

            }
        m.unlock();
            if(Players.find(echo.Get_ID())!=Players.end()) {
                game->drawScore(Players.at(echo.Get_ID())->getPoint(), glm::vec3(38.0f, 28.0f, 0.0f), glm::vec3 (0.99f, 0.99f, 0.99f));
            }
            //game->Draw_player(0,0,0.06,255,255,255);
            //game->Draw_player(0.2,0.2,0.06,255,255,255);
            //game->Show();

            //game->Draw_menu();
            game->Show();


            if(Players.find(echo.Get_ID())!=Players.end())
            {
            Player* me=Players.find(echo.Get_ID())->second;
            if(me->get_pickup()==Flag::dead)
            {
            p.flag=Flag::player;
            p.pickup_flag=Flag::replay;
            }
            p.p_id=myid;
            p.mom_x=mom_x;
            p.mom_y=mom_y;
            }else{
            p.flag=Flag::player;
            p.p_id=myid;
            p.mom_x=0;
            p.mom_y=0;
            }
            vector<Bubi_package> *vec = new vector<Bubi_package>();
            cout<<p.ToString()<<endl;
            vec->push_back(p);
            echo.Push_Bubivector(vec);
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        game->draw_endScreen(Players.at(echo.Get_ID())->getPoint(), glm::vec3 (0.99f, 0.99f, 0.99f));
        game->Show();

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
/*           if(swindow)
                SDL_DestroyWindow(swindow);
            if(srenderer)
                SDL_DestroyRenderer(srenderer);
*/
    atmos.Stop();
   // timer->join();

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
   //m.lock();
        for(int i=0;i<vec->size();i++)
        {
               Tree_package(vec->at(i));
               //if(!gamebool) break;
              // cout << "Tree updated" << endl;
        }
     //   m.unlock();
    delete vec;
    }
    cout<<"tree_updater ended"<<endl;
}

void MainClient::Tree_package(Bubi_package p) {

///mit csináljon a csomagokkal;
    last_update = std::chrono::system_clock::now();
    if(p.flag==Flag::player) {
        if(Players.find(p.p_id)==Players.end())
        {
            Player* temp= new Player(p.p_id,p.pos_x,p.pos_y,p.p_size,p.pickup_flag);
            Players.insert(pair<uint32_t,Player*>(p.p_id,temp));
        }
        else if(Players.find(p.p_id)!=Players.end()) {
            //cout << p.ToString() << endl;
           // cout<<p.pickup_flag;
            switch(p.pickup_flag) {
                case Flag::notset :
                    //cout << p.ToString() << endl;
                    //cout << "Update..." << endl;
                    Players.at(p.p_id)->update(p.pos_x,p.pos_y,p.p_size,p.pickup_flag,p.point);
                    break;
                case Flag::dead :

                    Players.erase(p.p_id);
///todo
                    if(p.p_id==echo.Get_ID()) {}//gamebool=false;
                    break;
                case Flag::dead_flag :
                    Players.at(p.p_id)->setDead();
                    break;
                case Flag::ready :
                    Players.at(p.p_id)->setReady(true);
                    break;
                case Flag::not_ready :
                    Players.at(p.p_id)->setReady(false);
                    break;
                case Flag::winner :
                    gamebool=false;
                default:
                    Players.at(p.p_id)->update(p.pos_x,p.pos_y,p.p_size,p.pickup_flag,p.point);
                    break;
            }
            } else {
                    Player* temp= new Player(p.p_id,p.pos_x,p.pos_y,p.p_size,p.pickup_flag);
                    Players.insert(pair<uint32_t,Player*>(p.p_id,temp));
                }

    } else if(p.flag == Flag::pickup) {
        //cout<<p.pickup_flag;
        if(p.pickup_flag == Flag::dead_pickup && pickups.find(p.p_id) != pickups.end() ) {
               delete pickups.at(p.p_id);
            pickups.erase(p.p_id);
            atmos.Bubibip("Pickup");
        } else {
            PickUp *pickup = new PickUp(p.p_id,p.pos_x,p.pos_y,p.p_size,p.pickup_flag,p.point);
            pickups.insert(pair<uint32_t,PickUp*>(p.p_id,pickup));
        }
    }

}
