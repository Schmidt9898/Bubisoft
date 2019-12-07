    #include <iostream>
    #include <glad/glad.h>
    ///sets up openGl pointers
    #include <GL/glfw3.h>
    #include "shader.hpp"

    #include <thread>
    #include <chrono>
    #define STB_IMAGE_IMPLEMENTATION
    #include "stb_image.h"
    #include <glm/glm/glm.hpp>
    #include <glm/glm/gtc/matrix_transform.hpp>
    #include <glm/glm/gtc/type_ptr.hpp>
    #include "camera.hpp"
    #include <iostream>
    #include <random>
    #include "vao.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

// settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;
bool RENDER = true;

// camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 2.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

enum CameraState {DYNAMIC, STATIC};
CameraState cameraState;


/// GLOBAL MATRICES
///====================
glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
glm::mat4 view;
glm::mat4 MVP;
glm::mat4 model = glm::mat4(1.0f);
const unsigned num_grass = 6;
glm::mat4 grass_pos[num_grass];
glm::vec3 water_color(0.4f, 0.8f, 0.95f);
glm::vec3 no_color(1.0f, 1.0f, 1.0f);
float wave_time = 0.0f;


void buttonTest(){std::cout<<"function is alive!\n";}

GLFWwindow* window;
int main()
{

    cameraState = CameraState::STATIC;
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    srand(time(NULL));
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    // glfw window creation
    // --------------------
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);

    Shader waterShader("shader/water/vertex.txt", "shader/water/fragment.txt");
    VAO floor(floor_triangles, 90, 18, "textures/sand_full_res.jpg");
    VAO grass(grass_triangles, 900, 180, "textures/grass_mid_res.jpg");
    for(unsigned int i = 0; i < num_grass; i++){
        grass_pos[i]=glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.45f));
    }
    ///*grass positions*/
    grass_pos[0]=glm::translate(grass_pos[0], glm::vec3(-3.0f, +2.0f, 0.0f));
    grass_pos[1]=glm::translate(grass_pos[1], glm::vec3(-3.0f, 0.0f, 0.0f));
    grass_pos[2]=glm::translate(grass_pos[2], glm::vec3(-2.5f, +1.0f, 0.0f));

    grass_pos[3]=glm::translate(grass_pos[3], glm::vec3(+3.0f, -2.0f, 0.0f));
    grass_pos[4]=glm::translate(grass_pos[4], glm::vec3(+3.0f, 0.0f, 0.0f));
    //grass_pos[4]=glm::scale(grass_pos[4], glm::vec3(0.0f, 0.0f, 1.3f));
    grass_pos[5]=glm::translate(grass_pos[5], glm::vec3(+2.5f, -1.0f, 0.0f));



    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if ( RENDER )
    while (!glfwWindowShouldClose(window))
    {
        wave_time+=0.025f;
        //camera / cursor workings
        //---------------------
        if(cameraState == CameraState::STATIC) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        else glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        waterShader.use();
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        model = glm::mat4(1.0f);
        MVP = projection * view * model;
        waterShader.setMat4("MVP", MVP);
        waterShader.setVec3("aColor", water_color);
        waterShader.setFloat("aAlpha", 1.0f);
        floor.draw();
        glClear(GL_DEPTH_BUFFER_BIT);

        waterShader.setFloat("aAlpha", 0.65f);
        for(unsigned i = 0; i < num_grass; i++){
            model = grass_pos[i];
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, -1.0f));
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, +2.9f));
            model = glm::scale(model, glm::vec3(1.0f+sin(wave_time + i)/10, 1.0f+cos(wave_time+wave_time*0.4)/10, 1.0f));
            MVP = projection * view * model;
            waterShader.setMat4("MVP", MVP);
            grass.draw();
        }
        waterShader.setVec3("aColor", no_color);
        waterShader.setFloat("aAlpha", 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT);
        for(unsigned i = 0; i < num_grass; i++){
            model = grass_pos[i];
            MVP = projection * view * model;
            waterShader.setMat4("MVP", MVP);
            grass.draw();
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 3.2 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos.y+=1 * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        cameraPos.y-=1 * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        cameraPos = glm::vec3(0.0, 0.1, 0.0);
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS);
        //mesh->addTrig();
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    if(cameraState == CameraState::DYNAMIC){
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
        cameraState = CameraState::DYNAMIC;
        firstMouse = true;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
        cameraState = CameraState::STATIC;

    /*
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE && cameraState==CameraState::STATIC){
        mesh->addVert(cameraPos.x + cameraFront.x, cameraPos.y + cameraFront.y, cameraPos.z + cameraFront.z,
                      (float)(rand()%100)/100, (float)(rand()%100)/100, (float)(rand()%100)/100);
    }*/
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}
