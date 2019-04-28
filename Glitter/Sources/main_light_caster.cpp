


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
#include "camera.h"

using namespace std;

using namespace Our;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int loadTexture(char const *path);

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;



Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

void processInput(GLFWwindow *window);

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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    
    //    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    gladLoadGL();
    
    glEnable(GL_DEPTH_TEST);
    
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
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
    
    unsigned int vao,vbo,ebo;
    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);
    //    glGenBuffers(1,&ebo);
    
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_TRUE,8 * sizeof(float),(void *)0);
    glEnableVertexAttribArray(0);
    
    
    glVertexAttribPointer(1,3,GL_FLOAT,GL_TRUE,8 * sizeof(float),(void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2,2,GL_FLOAT,GL_TRUE,8 * sizeof(float),(void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    glBindVertexArray(0);
    
    Shader  ourShader  = Shader("/Users/fangshufeng/Desktop/thirdPart/Glitter/Glitter/Sources/3.3.light_caster.vs",
                                "/Users/fangshufeng/Desktop/thirdPart/Glitter/Glitter/Sources/3.3.light_caster.fs");
    
    Shader  lampShader  = Shader("/Users/fangshufeng/Desktop/thirdPart/Glitter/Glitter/Sources/3.3.lamp.vs",
                                 "/Users/fangshufeng/Desktop/thirdPart/Glitter/Glitter/Sources/3.3.lamp.fs");
    
    
    unsigned int diffuseMap =   loadTexture("/Users/fangshufeng/Desktop/thirdPart/Glitter/container2.png");
    unsigned int specularMap =   loadTexture("/Users/fangshufeng/Desktop/thirdPart/Glitter/container2_specular.png");

    
    
    ourShader.user();
    glUniform1i(glad_glGetUniformLocation(ourShader.programID,"material.diffuse"),0);
    glUniform1i(glad_glGetUniformLocation(ourShader.programID,"material.specular"),1);
    
    // Rendering Loop
    while (glfwWindowShouldClose(window) == false) {
        
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        processInput(window);
        
        // Background Fill Color
        //         glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        ourShader.user();
        
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,diffuseMap);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,specularMap);
        
        
        glUniform3f(glGetUniformLocation(ourShader.programID, "lightColor"),  1.0f, 1.0f, 1.0f);
        
        glUniform3f(glGetUniformLocation(ourShader.programID, "lightPos"),  1.2f, 1.0f, 2.0f);
        
        glUniform3fv(glGetUniformLocation(ourShader.programID, "viewPos"),  1,&camera.Position[0]);
        
        
        glUniform1f(glGetUniformLocation(ourShader.programID, "material.shininess"), 32.0f);
        
//        glUniform3f(glGetUniformLocation(ourShader.programID, "light.direction"),  -1.2f, -1.0f, -2.0f);
        glUniform3f(glGetUniformLocation(ourShader.programID, "light.ambient"),  0.1f,0.1f,0.1f  );
        glUniform3f(glGetUniformLocation(ourShader.programID, "light.diffuse"),  1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(ourShader.programID, "light.specular"),  .5f, .5f, 0.5f);
        
        glUniform1f(glGetUniformLocation(ourShader.programID, "light.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(ourShader.programID, "light.linear"), 0.09f);
        glUniform1f(glGetUniformLocation(ourShader.programID, "light.quadratic"), 0.032f);
        
        // Model matrix
        glm::mat4 model = glm::mat4(1.0f);
        //       model =  glm::rotate(model, glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        
        // view
        glm::mat4 view = camera.GetViewMatrix();
        
        // projection
        glm::mat4 projection;
        //        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        
        
        glUniformMatrix4fv(glGetUniformLocation(ourShader.programID,"model"),1, GL_FALSE,glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(ourShader.programID,"view"),1, GL_FALSE,glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(ourShader.programID,"projection"),1, GL_FALSE,glm::value_ptr(projection));
        
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES,0,36);
        
        
        // also draw the lamp object
//        lampShader.user();
        
        // Model matrix
//        glm::mat4 model2 = glm::mat4(1.0f);
//        model2 = glm::translate(model2,lightPos);
//        model2 = glm::scale(model2, glm::vec3(0.2f)); // a smaller cube
        
        // view
        //        glm::mat4 view2 = camera.GetViewMatrix();
        
        
//        glUniformMatrix4fv(glGetUniformLocation(lampShader.programID,"model"),1, GL_FALSE,glm::value_ptr(model2));
//        glUniformMatrix4fv(glGetUniformLocation(lampShader.programID,"view"),1, GL_FALSE,glm::value_ptr(view));
//        glUniformMatrix4fv(glGetUniformLocation(lampShader.programID,"projection"),1, GL_FALSE,glm::value_ptr(projection));
//        
//        
//        glBindVertexArray(vao);
//        
//        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
           glUniformMatrix4fv(glGetUniformLocation(ourShader.programID,"model"),1, GL_FALSE,glm::value_ptr(model));
            
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        
        
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

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
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
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    
    lastX = xpos;
    lastY = ypos;
    
    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}


unsigned int loadTexture(char const *path) {
    
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
    
    int width,height,nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    
    // d绑定到buffer上
    if (data != nullptr) {
        GLenum format = GL_RGBA ;
        if (nrComponents == 1) {
            format = GL_RED;
        } else if (nrComponents == 3) {
            format = GL_RGB;
        } else if (nrComponents == 4) {
            format = GL_RGBA;
        }
        
        glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
    }
    
    stbi_image_free(data);
    
    return texture;
}
