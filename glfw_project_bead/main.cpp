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


int main()
{
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
    return 0;
}
