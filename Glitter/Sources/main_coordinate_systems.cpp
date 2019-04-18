
// 抽取 编写、编译、管理着色器

// Local Headers
#include "glitter.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Standard Headers
#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <math.h>

#include "Shader.hpp"
#include "stb_image.h"

using namespace std;

using namespace Our;

float mixValue = 0.2f;
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main(int argc, char * argv[]) {
    
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    GLFWwindow *window =  glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", nullptr, nullptr);
    if (window == nullptr) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    gladLoadGL();
    
    glEnable(GL_DEPTH_TEST);
    
    // ------------------------------------------------------------------
    
//    float vertices[] = {
//        // positions          // colors           // texture coords
//        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
//        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
//        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
//        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
//    };
//
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
    
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    
//    unsigned int indices[] = {
//        0, 1, 3, // first triangle
//        1, 2, 3  // second triangle
//    };
    
    unsigned int vao,vbo,ebo;
    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);
//    glGenBuffers(1,&ebo);
    
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_TRUE,5 * sizeof(float),(void *)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1,2,GL_FLOAT,GL_TRUE,5 * sizeof(float),(void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
//    glVertexAttribPointer(2,2,GL_FLOAT,GL_TRUE,8 * sizeof(float),(void *)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);
    
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    glBindVertexArray(0);
    
    
    
    Shader  ourShader  = Shader("/Users/fangshufeng/Desktop/thirdPart/Glitter/Glitter/Sources/3.3.coordinate.vs", "/Users/fangshufeng/Desktop/thirdPart/Glitter/Glitter/Sources/3.3.coordinate.fs");
    
    
    // 创建纹理
    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture); // 2d纹理
    
    // 设置纹理的环绕方式
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    
    // 设置纹理过滤
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    // 读取图片到内存中
    
    int width,height,nrChannels;
    unsigned char *data = stbi_load("/Users/fangshufeng/Desktop/thirdPart/Glitter/container.jpg", &width, &height, &nrChannels, 0);
    
    // d绑定到buffer上
    if (data != nullptr) {
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    
    stbi_image_free(data);
    
    
    // 创建纹理
    unsigned int texture2;
    glGenTextures(1,&texture2);
    glBindTexture(GL_TEXTURE_2D,texture2); // 2d纹理
    
    // 设置纹理的环绕方式
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    
    // 设置纹理过滤
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    
    
    int width2,height2,nrChannels2;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data2 = stbi_load("/Users/fangshufeng/Desktop/thirdPart/Glitter/awesomeface.png", &width2, &height2, &nrChannels2, 0);
    
    // 绑定到buffer上
    if (data2 != nullptr) {
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width2,height2,0,GL_RGBA,GL_UNSIGNED_BYTE,data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    
    stbi_image_free(data2);
    
    ourShader.user();
    glUniform1i(glad_glGetUniformLocation(ourShader.programID,"texture1"),0);
    glUniform1i(glad_glGetUniformLocation(ourShader.programID,"texture2"),1);

    
    // Rendering Loop
    while (glfwWindowShouldClose(window) == false) {
        
        processInput(window);
        
        // Background Fill Color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glUniform1f(glGetUniformLocation(ourShader.programID, "mixValue"), mixValue);
        
        ourShader.user();
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,texture);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,texture2);
        
        glBindVertexArray(vao);
        
        // view matrix
        glm::mat4 view;
        float radius = 1.0f;
        view = glm::translate(view, glm::vec3(sin(glfwGetTime()) * radius,cos(glfwGetTime()) * radius, -5.0f));

        // projection
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        
        
        glUniformMatrix4fv(glGetUniformLocation(ourShader.programID,"view"),1, GL_FALSE,glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(ourShader.programID,"projection"),1, GL_FALSE,glm::value_ptr(projection));
        
        for (int i = 0; i < 1; i++) {
            
            // Model matrix
            glm::mat4 model ;
            model = glm::translate(model, cubePositions[i]);
            float angle = 50 * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(0.5f, 0.5f, 0.0f));

            
            glUniformMatrix4fv(glGetUniformLocation(ourShader.programID,"model"),1, GL_FALSE,glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES,0,36);
        }
        
//        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        
        
        // Flip Buffers and Draw
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    
    glfwTerminate();
    
    
    
    return EXIT_SUCCESS;
    
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        mixValue += 0.001f;
        if(mixValue >= 1.0f)
            mixValue = 1.0f;
    }
    
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        mixValue -= 0.001f;
        if(mixValue <= 0.0f)
            mixValue = 0.0f;
    }
    
}
