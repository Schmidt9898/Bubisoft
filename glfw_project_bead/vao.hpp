#ifndef VAO_HPP_INCLUDED
#define VAO_HPP_INCLUDED

extern GLFWwindow* window;

#include "game_vertices.h"

struct VAO
{
public:
    float *data;
    unsigned num_floats, num_vertices;
    unsigned vao, vbo, texture;
//    GLuint texture;

    VAO(float* _data, unsigned _num_floats, unsigned _num_vertices, std::string texture_path);

    void draw();

    ~VAO();

};


VAO::~VAO()
    {
        delete[] data;
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
    }

VAO::VAO(float* _data, unsigned _num_floats, unsigned _num_vertices, std::string texture_path){
        glfwMakeContextCurrent(window);
        data = nullptr;
        num_floats = _num_floats;
        num_vertices = _num_vertices;
        data = _data;

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(data) * num_floats, data, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);


        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        unsigned char *tex_data = stbi_load(texture_path.c_str(), &width, &height, &nrChannels, 0);
        if (tex_data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture: " << texture_path <<std::endl;
        }
        stbi_image_free(tex_data);






    }
void VAO::draw()
{
    glfwMakeContextCurrent(window);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(vao);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glDrawArrays(GL_TRIANGLES, 0, num_vertices);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);
    glDrawArrays(GL_TRIANGLES, 0, num_vertices);


}






#endif // VAO_HPP_INCLUDED
