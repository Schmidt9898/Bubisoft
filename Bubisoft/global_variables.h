#ifndef GLOBAL_VARIABLES_H_INCLUDED
#define GLOBAL_VARIABLES_H_INCLUDED
//asd
#include <math.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
int globalGraphicsInit();
void globalMatricesInit();

const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;
bool RENDER = true;
bool GLOBAL_IN_MENU=true;
bool GLOBAL_IN_OPTIONS=false;
bool LOOK_AROUND=false;


// camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 2.5f);
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

glm::mat4 mat_play_button;
glm::mat4 mat_options_button;
glm::mat4 mat_volume_slider;
glm::mat4 mat_other_slider;
glm::mat4 mat_victory;

const unsigned num_grass = 6;
glm::mat4 grass_pos[num_grass];
glm::vec3 water_color(0.4f, 0.8f, 0.95f);
glm::vec3 no_color(1.0f, 1.0f, 1.0f);
glm::vec3 select_color(0.9f, 0.8f, 0.5f);

///PLAYER STUFF
///===========================================
glm::vec3 global_player_colors[3];
glm::vec3 global_player_positions[3];
float global_player_size[3]={0.5f, 0.5f, 0.5f};
glm::vec3 global_pickup_positions[50];
bool global_players_alive[3];

float global_map_size=2.0f;


///DRAW FUNC
void drawPlayer(unsigned id, VAO &vao, float wave, float size);
void drawLocalPlayer(VAO &vao, float wave, float size);
void drawMenu(VAO &_screen, VAO &_play_button, VAO &_options_button, VAO &_options_screen, VAO &_volume_slider);
void drawMap(VAO &_gamefloor, VAO &_water, VAO &_grass, VAO &_sky);
void drawPickup(VAO *_pickup, glm::vec3 _pos, float wave);
void drawVictory(VAO &_vic0, VAO &_vic1, VAO &_vic2, unsigned id);
void drawDisconnect(VAO &_disc);
void drawPickups(VAO *vao, float &wave_time);
void managePositions();
void drawScore(unsigned score, unsigned id, VAO* score_table, VAO* number);

float GLOBAL_PICKUP_SCALE = 1.0f;


float wave_time = 0.0f;

float GLOBAL_VOLUME_SLIDER = 0.5f;
float GLOBAL_OTHER_SLIDER = 0.5f;
char GLOBAL_SELECT_BUTTON = 'P';

char global_match_state = 'A';

Shader* waterShader;
Shader* numberShader;
GLFWwindow* window;


void play(){
        GLOBAL_IN_MENU = !GLOBAL_IN_MENU;
        //std::cout<<"play = "<<GLOBAL_IN_MENU<<"\n";
}
void options(){
    GLOBAL_IN_OPTIONS = !GLOBAL_IN_OPTIONS;
    //std::cout<<"options = "<<GLOBAL_IN_OPTIONS<<"\n";
}



class GAME{


     VAO* gamefloor;
     VAO* grass;
     VAO* water;
     VAO* sky;
     VAO* screen;
     VAO* options_screen;
     VAO* play_button;
     VAO* options_button;
     VAO* volume_slider;
     VAO* player;
     VAO* pickup;
     VAO* blue_victory;
     VAO* red_victory;
     VAO* yellow_victory;
     VAO* disconnect;
     VAO* score_table;
     VAO* number;



    public:
    GAME(){
        gamefloor = new VAO(floor_triangles, 90, 18, "textures/sand_full_res.jpg");
        grass = new VAO(grass_triangles, 900, 180, "textures/grass_mid_res.jpg");
        water = new VAO(floor_triangles, 90, 18, "textures/water_mid.jpg");
        sky = new VAO(floor_triangles, 90, 18, "textures/sky_mid_clouds.jpg");
        screen = new VAO(screen_background, 30, 6, "textures/sky_mid_clouds.jpg");
        options_screen = new VAO(screen_background, 30, 6, "textures/options_menu.jpg");
        play_button = new VAO(button_vertices, 150, 30, "textures/button_play.jpg");
        options_button = new VAO(button_vertices, 150, 30, "textures/button_options.jpg");
        volume_slider = new VAO(slider_vertices, 30, 6, "textures/slider.jpg");
        player = new VAO(slime_vertices, 1020, 204, "textures/slime.jpg");
        pickup = new VAO(pickup_vertices, 15, 3, "textures/slider.jpg");
        blue_victory = new VAO(screen_background, 30, 6, "textures/player3.jpg");
        red_victory = new VAO(screen_background, 30, 6, "textures/player1.jpg");
        yellow_victory = new VAO(screen_background, 30, 6, "textures/player2.jpg");
        disconnect = new VAO(screen_background, 30, 6, "textures/DISCONNECTED.jpg");
        score_table = new VAO(screen_background, 30, 6, "textures/score.jpg");
        number = new VAO(number_vertices, 30, 6, "textures/number.jpg");

        for(unsigned i = 0; i < 3; i++)
            global_players_alive[i]=true;

        glm::vec3 nullvec(0.0f, 0.0f, 0.0f);
        for(unsigned i = 0; i<50; i++)
            global_pickup_positions[i]=nullvec;
    }
    void loop(){
        wave_time+=0.025f;
        if(cameraState == CameraState::STATIC) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        else glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);

        glClearColor(0.3f, 0.3f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawMenu(*screen, *play_button, *options_button, *options_screen, *volume_slider);
        drawMap(*gamefloor, *water, *grass, *sky);
        //drawLocalPlayer(*player, wave_time, 1.0f);

        for(int i=0;i<3;i++)
        {
            if(global_players_alive[i])
                drawPlayer(i,*player,wave_time+(i*0.3f),global_player_size[i]);
        }
        managePositions();
        drawPickups(pickup, wave_time);
        //drawVictory(*red_victory, *yellow_victory, *blue_victory, 0);
        //drawScore(72, 0, score_table, number);


        if(global_players_alive[0] && !global_players_alive[1] && !global_players_alive[2]){
            drawVictory(*red_victory, *yellow_victory, *blue_victory, 0);
        }
        if(!global_players_alive[0] && global_players_alive[1] && !global_players_alive[2]){
            drawVictory(*red_victory, *yellow_victory, *blue_victory, 1);
        }
        if(!global_players_alive[0] && !global_players_alive[1] && global_players_alive[2]){
            drawVictory(*red_victory, *yellow_victory, *blue_victory, 2);
        }





        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    void update_player_pos(int id,float x,float y,float size_)
    {
        if(id<0)
            return;
        global_player_positions[id]=glm::vec3(x,y,0.0);
        global_player_size[id]=size_;


    }
    void update_cameraZ(float d)
    {
        cameraPos.z=d;
    }

    void cleanup(){
        delete waterShader;
        delete gamefloor;
        delete grass;
        delete water;
        delete sky;
        delete screen;
        delete options_screen;
        delete play_button;
        delete options_button;
        delete volume_slider;
        delete player;
        delete pickup;
        delete blue_victory;
        delete red_victory;
        delete yellow_victory;
        delete disconnect;
        delete number;
        delete score_table;
        glfwTerminate();
    }
};

GAME *game;

void drawPickups(VAO *vao, float &wave_time){
    glm::vec3 nullvec(0.0f, 0.0f, 0.0f);
    for(unsigned i = 0; i < 50; i++){
        if(global_pickup_positions[i] == nullvec) continue;
        else drawPickup(vao, global_pickup_positions[i], wave_time);
    }
}

const float PI = 3.1415f;

void managePositions(){
    auto dist=[](glm::vec3 _vec1, glm::vec3 _vec2) -> float
    {
        return (float)std::sqrt
        (
            (_vec1.x - _vec2.x)*(_vec1.x - _vec2.x) +
            (_vec1.y - _vec2.y)*(_vec1.y - _vec2.y)
        );
    };

    auto place=[](glm::vec3 &vec) -> void
    {
        float r = 12.0f * std::sqrt( (double)(rand()%5000)/5000);
        float theta = (double)(rand()%5000)/5000 * 2 * PI;
        vec.x= r * sin(theta);
        vec.y= r * cos(theta);

    };

    auto eat=[&](unsigned p1, unsigned p2) -> void
    {
        if(global_players_alive[p1] && global_players_alive[p2])
        {
            if(dist(global_player_positions[p1], global_player_positions[p2]) < (global_player_size[p1] + global_player_size[p2])/5.0f )
            {
                if(global_player_size[p1] == global_player_size[p2]) return;
                if(global_player_size[p1] > global_player_size[p2]) {global_player_size[p1]+=0.03; global_players_alive[p2]=false;}
                if(global_player_size[p1] < global_player_size[p2]) {global_player_size[p2]+=0.03; global_players_alive[p1]=false;}
            }
        } else return;
    };

    eat(0, 1);
    eat(1, 2);
    eat(2, 0);

    glm::vec3 nullvec(0.0f, 0.0f, 0.0f);

    for(unsigned p = 0; p < 3; p++){
        if(!global_players_alive[p]) continue;
        for(unsigned i = 0; i < 50; i++){

            if(global_pickup_positions[i] == nullvec) {
                place(global_pickup_positions[i]);
                continue;
            }

            if(dist(global_player_positions[p], global_pickup_positions[i]) < global_player_size[p]/3.0 ){
                global_player_size[p]+=0.01;
                global_pickup_positions[i]=nullvec;
            }
        }
        float border_dist = dist(nullvec, global_player_positions[p]);
        if(border_dist >= 12.0f ){
            global_player_positions[p]+= 0.01f * (border_dist-12.0f) * (nullvec-global_player_positions[p]);
        }
    }
    if(global_match_state == 'A'){
        place(global_player_positions[0]);
        cameraPos.x=global_player_positions[0].x;
        cameraPos.y=global_player_positions[0].y;
        place(global_player_positions[1]);
        place(global_player_positions[2]);
        global_match_state='B';
    }


}

void globalMatricesInit(){
    glm::mat4 E = glm::mat4(1.0f);
    //glm::mat4 water = E * mat_MS;
    mat_play_button = glm::translate(E, glm::vec3(-0.05f, 0.4f, 0.0f));
    //mat_play_button = glm::rotate(mat_play_button, glm::radians(180.0f),glm::vec3(0.0f, 1.0f, 0.0f));
    mat_play_button = glm::scale(mat_play_button, glm::vec3(0.04f, 0.04f, 0.04f));
    mat_options_button = glm::translate(mat_play_button, glm::vec3(0.0f, -2.3f, 0.0f));
    mat_volume_slider = glm::scale(E, glm::vec3(0.6f, 0.6f, 0.6f));
    mat_volume_slider = glm::translate(mat_volume_slider, glm::vec3(0.0f, 0.065f, 0.0f));
    mat_other_slider = glm::scale(E, glm::vec3(0.6f, 0.6f, 0.6f));
    mat_other_slider = glm::translate(mat_other_slider, glm::vec3(0.0f, -0.28f, 0.0f));
    mat_victory = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 1.0f));

    for(unsigned int i = 0; i < num_grass; i++){
        grass_pos[i]=glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.45f));
    }
    ///*grass positions*/
    grass_pos[0]=glm::translate(grass_pos[0], glm::vec3(-3.0f, +2.0f, 0.0f));
    grass_pos[1]=glm::translate(grass_pos[1], glm::vec3(-3.0f, 0.0f, 0.0f));
    grass_pos[2]=glm::translate(grass_pos[2], glm::vec3(-2.5f, +1.0f, 0.0f));

    grass_pos[3]=glm::translate(grass_pos[3], glm::vec3(+3.0f, -2.0f, 0.0f));
    grass_pos[4]=glm::translate(grass_pos[4], glm::vec3(+3.0f, 0.0f, 0.0f));
    grass_pos[5]=glm::translate(grass_pos[5], glm::vec3(+2.5f, -1.0f, 0.0f));

    global_player_positions[0] = glm::vec3(0.0f, 0.0f, 0.0f);
    global_player_positions[1] = glm::vec3(0.0f, 0.0f, 0.0f);
    global_player_positions[2] = glm::vec3(0.0f, 0.0f, 0.0f);

    global_player_colors[0]=glm::vec3(0.89f, 0.2f, 0.5f);
    global_player_colors[1]=glm::vec3(0.5f, 0.89f, 0.2f);
    global_player_colors[2]=glm::vec3(0.2f, 0.5f, 0.89f);
}

int globalGraphicsInit(){
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
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "BUBISOFT", NULL, NULL);
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
    glfwSetKeyCallback(window, key_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    globalMatricesInit();
    waterShader = new Shader("shader/water/vertex.txt", "shader/water/fragment.txt");
    numberShader = new Shader("shader/number/vertex.txt", "shader/number/fragment.txt");
    game = new GAME();
    return (int)true;
}

void drawMenu(VAO &screen, VAO &play_button, VAO &options_button, VAO &options_screen, VAO &volume_slider){
    if(GLOBAL_IN_MENU) {
        glfwMakeContextCurrent(window);
        waterShader->use();
        view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::mat4(1.0f);
        MVP = projection * view * model;
        waterShader->setMat4("MVP", MVP);
        waterShader->setVec3("aColor", no_color);
        waterShader->setFloat("aAlpha", 1.0f);

        screen.draw();
        glClear(GL_DEPTH_BUFFER_BIT);

        model = mat_play_button;
        MVP = projection * view * model;
        waterShader->setMat4("MVP", MVP);
        if(GLOBAL_SELECT_BUTTON == 'P')
             waterShader->setVec3("aColor", select_color);
        else waterShader->setVec3("aColor", no_color);
        play_button.draw();

        model = mat_options_button;
        MVP = projection * view * model;
        waterShader->setMat4("MVP", MVP);
        if(GLOBAL_SELECT_BUTTON == 'O')
             waterShader->setVec3("aColor", select_color);
        else waterShader->setVec3("aColor", no_color);
        options_button.draw();
        glClear(GL_DEPTH_BUFFER_BIT);

        if(GLOBAL_IN_OPTIONS){
            model = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.3f, 0.0f));
            MVP = projection * view * model;
            waterShader->setMat4("MVP", MVP);
            waterShader->setVec3("aColor", no_color);
            options_screen.draw();
            glClear(GL_DEPTH_BUFFER_BIT);

            model = mat_volume_slider;
            model = glm::translate(model, glm::vec3((2.0f*0.26f*GLOBAL_VOLUME_SLIDER)-0.26f, 0.0f, 0.0f));
            MVP = projection * view * model;
            waterShader->setMat4("MVP", MVP);
            if(GLOBAL_SELECT_BUTTON == 'V')
                 waterShader->setVec3("aColor", select_color);
            else waterShader->setVec3("aColor", no_color);
            volume_slider.draw();

            model = mat_other_slider;
            model = glm::translate(model, glm::vec3((2.0f*0.26f*GLOBAL_OTHER_SLIDER)-0.26f, 0.0f, 0.0f));
            MVP = projection * view * model;
            waterShader->setMat4("MVP", MVP);
            if(GLOBAL_SELECT_BUTTON == 'W')
                 waterShader->setVec3("aColor", select_color);
            else waterShader->setVec3("aColor", no_color);
            volume_slider.draw();
        }
    } else return;

}

void drawMap(VAO &floor, VAO &water, VAO &grass, VAO &sky){
    if(GLOBAL_IN_MENU) return;
    glfwMakeContextCurrent(window);
    waterShader->use();
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    model = glm::scale(model, glm::vec3(global_map_size, global_map_size, 1.0f));
    MVP = projection * view * model;
    waterShader->setMat4("MVP", MVP);
    waterShader->setVec3("aColor", water_color);
    waterShader->setFloat("aAlpha", 1.0f);
    floor.draw();
    glClear(GL_DEPTH_BUFFER_BIT);

    model = glm::scale(glm::mat4(1.0f), glm::vec3(5.0f, 5.0f, 1.0f));
    MVP = projection * view * model;
    waterShader->setMat4("MVP", MVP);
    waterShader->setVec3("aColor", no_color);
    waterShader->setFloat("aAlpha", 0.7f);
    water.draw();
    glClear(GL_DEPTH_BUFFER_BIT);

    model = glm::mat4(1.0f);
    MVP = projection * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -6.f)) * model;
    waterShader->setMat4("MVP", MVP);
    waterShader->setVec3("aColor", no_color);
    waterShader->setFloat("aAlpha", 0.45f);
    sky.draw();
    glClear(GL_DEPTH_BUFFER_BIT);

    waterShader->setFloat("aAlpha", 0.3f);
    for(unsigned i = 0; i < num_grass; i++){
        model = grass_pos[i];
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, -1.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, +2.9f));
        model = glm::scale(model, glm::vec3(1.0f+sin(wave_time + i)/10, 1.0f+cos(wave_time+wave_time*0.4)/10, 1.0f));
        MVP = projection * view * model;
        waterShader->setMat4("MVP", MVP);
        grass.draw();
    }

    waterShader->setVec3("aColor", no_color);
    waterShader->setFloat("aAlpha", 1.0f);
    //glClear(GL_DEPTH_BUFFER_BIT);
    for(unsigned i = 0; i < num_grass; i++){
        model = grass_pos[i];
        MVP = projection * view * model;
        waterShader->setMat4("MVP", MVP);
        grass.draw();
    }



}

void drawPlayer(unsigned id, VAO &vao, float wave, float size){
    if(GLOBAL_IN_MENU) return;
    glfwMakeContextCurrent(window);
    waterShader->use();
    float scale = (1.0f+sin(2.1f*wave))/4 - 0.25f;//-0.25-0.25
    glm::mat4 M = glm::mat4(1.0f);
    M = glm::translate(M, glm::vec3(global_player_positions[id]));
    M = glm::scale(M, glm::vec3(1.0f+scale, 1.0f-scale, 1.0f));
    M = glm::scale(M, glm::vec3(size, size, 1.0f));
    MVP = projection * view * M;
    waterShader->setMat4("MVP", MVP);
    waterShader->setVec3("aColor", global_player_colors[id]);
    waterShader->setFloat("aAlpha", 0.7f);
    vao.draw();
}

void drawLocalPlayer(VAO &vao, float wave, float size){
    if(GLOBAL_IN_MENU) return;
    glfwMakeContextCurrent(window);
    waterShader->use();
    float scale = 1.0f + (1.0f+sin(2.1f*wave))/4;
    glm::mat4 M = glm::mat4(1.0f);
    M = glm::translate(M, glm::vec3(global_player_positions[0]));
    M = glm::scale(M, glm::vec3(scale, 2.5f-scale, 1.0f));
    M = glm::scale(M, glm::vec3(size, size, 1.0f));
    MVP = projection * view * M;
    waterShader->setVec3("aColor", global_player_colors[0]);
    waterShader->setFloat("aAlpha", 0.7f);
    waterShader->setMat4("MVP", MVP);
    vao.draw();
}

void drawPickup(VAO *vao, glm::vec3 pos, float wave){
	if(GLOBAL_IN_MENU) return;
    glfwMakeContextCurrent(window);
    waterShader->use();
    glm::mat4 M = glm::mat4(1.0f);
    M = glm::translate(M, pos);
    M = glm::translate(M, glm::vec3(0.0f, 0.0f, (float)( sin(wave*pos.x)+cos(wave*pos.y) ) /4.0 + 0.25f ) );
    M = glm::scale(M, glm::vec3(GLOBAL_PICKUP_SCALE, GLOBAL_PICKUP_SCALE, 1.0f));
    MVP = projection * view * M;
    waterShader->setVec3("aColor", no_color);
    waterShader->setFloat("aAlpha", 1.0f);
    waterShader->setMat4("MVP", MVP);
    vao->draw();
}

void drawScore(unsigned score, unsigned id, VAO* score_table, VAO* number){
    glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.4f, -0.65f, 0.0f));
    if(GLOBAL_IN_MENU) return;
	glfwMakeContextCurrent(window);
	waterShader->use();
    glClear(GL_DEPTH_BUFFER_BIT);
    MVP = model;

	waterShader->setFloat("aAlpha", 1.0f);
	waterShader->setMat4("MVP", MVP);
	waterShader->setVec3("aColor", global_player_colors[id]);
	score_table->draw();

    numberShader->use();
	glClear(GL_DEPTH_BUFFER_BIT);
	model = glm::scale(model, glm::vec3(0.25f, 1.9f, 1.0f));
	model = glm::translate(model, glm::vec3(5.0f, -0.4f, 0.0f));
	MVP = model;
	numberShader->setFloat("aAlpha", 1.0f);
	numberShader->setMat4("MVP", MVP);
	numberShader->setVec3("aColor", global_player_colors[id]);
	numberShader->setFloat("aOffset", (unsigned)score/10);
	number->draw();

    numberShader->setFloat("aOffset", (unsigned)score%10);
    model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
    MVP = model;
    numberShader->setMat4("MVP", MVP);
    number->draw();


}



void drawVictory(VAO &_vic0, VAO &_vic1, VAO &_vic2, unsigned id){
	if(GLOBAL_IN_MENU) return;
	glfwMakeContextCurrent(window);
    waterShader->use();
	glClear(GL_DEPTH_BUFFER_BIT);
	MVP =  glm::translate(mat_victory, glm::vec3(0.0f, 0.8f, 0.0f));
	waterShader->setFloat("aAlpha", 1.0f);
	waterShader->setMat4("MVP", MVP);
	waterShader->setVec3("aColor", global_player_colors[id]);
	switch(id){
		case 0: {
				_vic0.draw();
			break;
		}
		case 1: {
				_vic1.draw();
			break;
		}
		case 2: {
				_vic2.draw();
			break;
		}

	}
}

void drawDisconnect(VAO &_disc){
	if(GLOBAL_IN_MENU) return;
	glfwMakeContextCurrent(window);
    waterShader->use();
	glClear(GL_DEPTH_BUFFER_BIT);
	MVP =  mat_victory;
	waterShader->setFloat("aAlpha", 1.0f);
	waterShader->setMat4("MVP", MVP);
	waterShader->setVec3("aColor", no_color);
	_disc.draw();
}

void processInput(GLFWwindow *window){
///this function is for movement only
    ///ESC
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    ///ESC should work always
    if(GLOBAL_IN_MENU) return;

    float cameraSpeed = 1.3 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        global_player_positions[0].y+= 1 * cameraSpeed;
        cameraPos.y=global_player_positions[0].y;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        global_player_positions[0].y-=1 * cameraSpeed;
        cameraPos.y=global_player_positions[0].y;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        global_player_positions[0].x -= 1 * cameraSpeed;
        cameraPos.x=global_player_positions[0].x;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        global_player_positions[0].x += 1 * cameraSpeed;
        cameraPos.x=global_player_positions[0].x;
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        GLOBAL_IN_MENU = true;
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        std::cout<<"Camera State: "<<cameraPos.x<<" "<<cameraPos.y<<" "<<cameraPos.z<<"\n";

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    ///this function is for menu selection only
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    ///ESC works here aswell
    if(!GLOBAL_IN_MENU) return;

    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        GLOBAL_IN_MENU = false;
    }
    if (key == GLFW_KEY_O && action == GLFW_PRESS)
    {
        ///toggle options menu
        options();
    }
    if (key == GLFW_KEY_I && action == GLFW_PRESS)
    {
        std::cout<<"Camera State: "<<cameraPos.x<<" "<<cameraPos.y<<" "<<cameraPos.z<<"\n";
        LOOK_AROUND = !LOOK_AROUND;
        for(unsigned i = 0; i < 50; i++){
            std::cout<<"\n  pickup_pos: "<<global_pickup_positions[i].x<<" "
            <<global_pickup_positions[i].y<<" "
            <<global_pickup_positions[i].z;
        }
    }
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        if(!GLOBAL_IN_OPTIONS){
            if(GLOBAL_SELECT_BUTTON == 'P')
                GLOBAL_SELECT_BUTTON = 'O';
            else {
                GLOBAL_SELECT_BUTTON = 'P';
            }
        }
        else {
            if(GLOBAL_SELECT_BUTTON == 'V')
                GLOBAL_SELECT_BUTTON = 'W';
            else {
                GLOBAL_SELECT_BUTTON = 'V';
            }
        }
    }
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        if(GLOBAL_IN_OPTIONS){
            if(GLOBAL_SELECT_BUTTON == 'V'){
                if(GLOBAL_VOLUME_SLIDER > 0.0f){
                    GLOBAL_VOLUME_SLIDER-=0.025f;
                }
            }
            if(GLOBAL_SELECT_BUTTON == 'W'){
                if(GLOBAL_OTHER_SLIDER > 0.0f){
                    GLOBAL_OTHER_SLIDER-=0.025f;
                }
            }
        }
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        if(!GLOBAL_IN_OPTIONS){
                    if(GLOBAL_SELECT_BUTTON == 'P')
                        GLOBAL_SELECT_BUTTON = 'O';
                    else {
                        GLOBAL_SELECT_BUTTON = 'P';
                    }
                }
        else {
            if(GLOBAL_SELECT_BUTTON == 'V')
                GLOBAL_SELECT_BUTTON = 'W';
            else {
                GLOBAL_SELECT_BUTTON = 'V';
            }
        }
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        if(GLOBAL_IN_OPTIONS){
            if(GLOBAL_SELECT_BUTTON == 'V'){
                if(GLOBAL_VOLUME_SLIDER < 1.0f){
                    GLOBAL_VOLUME_SLIDER+=0.025f;
                }
            }
            if(GLOBAL_SELECT_BUTTON == 'W'){
                if(GLOBAL_OTHER_SLIDER < 1.0f){
                    GLOBAL_OTHER_SLIDER+=0.025f;
                }
            }
        }

    }
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
    {
        if(GLOBAL_SELECT_BUTTON == 'P') play();
        if(GLOBAL_SELECT_BUTTON == 'O') {
            GLOBAL_IN_OPTIONS = true;
            GLOBAL_SELECT_BUTTON = 'V';
        }
        else {
            if(GLOBAL_SELECT_BUTTON == 'V' || GLOBAL_SELECT_BUTTON == 'W') {
                GLOBAL_SELECT_BUTTON = 'O';
                GLOBAL_IN_OPTIONS = false;
            }
        }
    }

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
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
    /**/
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS && LOOK_AROUND){
        cameraState = CameraState::DYNAMIC;
        firstMouse = true;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
        cameraState = CameraState::STATIC;

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){

}






#endif // GLOBAL_VARIABLES_H_INCLUDED
