#include <iostream>

#include "Bubisoft_Net.hpp"
#include "Bubi_Sound.h"

////////
/*
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

*/

///////////


//#include "mainClient.h"


#include "mainServer.h"
//#include "MainLaci.hpp"

//#include "Bubi_package.h"
/*
#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_net.h>
*/
using namespace std;

int main()
{
//    char tipus;

    cout << "Hello!" << endl << endl;
    MainServer();
     // MainLaci();
/*
    cout << "Server(s) or Client(c): ";
    cin >> tipus;

    switch(tipus) {
        case 's' : MainServer(); break;
        case 'c' : MainClient(); break;
    }
*/
/*
if(!globalGraphicsInit()) RENDER = false;
    ///MODELS / MESHES / OBJECTS

    if ( RENDER )
    while (!glfwWindowShouldClose(window))
    {
        game->loop();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    game->cleanup();
    delete game;
*/

/*
string ip;
    cout << "Give server address: ";
    cin >> ip;
    int port;
    cout << "Give server port: ";
    cin >> port;
MainClient Main( (ip=="0")? "localhost" : ip ,(port==0)?12345:port);   ///init
Main.Loop();

   cin >> ip;
*/
    return 0;
}
