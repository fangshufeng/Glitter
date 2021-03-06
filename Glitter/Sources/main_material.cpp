

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
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    unsigned int vao,vbo,ebo;
    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);
    //    glGenBuffers(1,&ebo);
    
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_TRUE,6 * sizeof(float),(void *)0);
    glEnableVertexAttribArray(0);
    
    
    glVertexAttribPointer(1,3,GL_FLOAT,GL_TRUE,6 * sizeof(float),(void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    glBindVertexArray(0);
    
    Shader  ourShader  = Shader("/Users/fangshufeng/Desktop/thirdPart/Glitter/Glitter/Sources/3.3.material.vs",
                                "/Users/fangshufeng/Desktop/thirdPart/Glitter/Glitter/Sources/3.3.material.fs");
    
    Shader  lampShader  = Shader("/Users/fangshufeng/Desktop/thirdPart/Glitter/Glitter/Sources/3.3.lamp.vs",
                                 "/Users/fangshufeng/Desktop/thirdPart/Glitter/Glitter/Sources/3.3.lamp.fs");
    
    
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
        
        
        
        glUniform3f(glGetUniformLocation(ourShader.programID, "objectColor"),  1.0f, 0.5f, 0.31f);
        glUniform3f(glGetUniformLocation(ourShader.programID, "lightColor"),  1.0f, 1.0f, 1.0f);
        
        glUniform3f(glGetUniformLocation(ourShader.programID, "lightPos"),  1.2f, 1.0f, 2.0f);
        glUniform3fv(glGetUniformLocation(ourShader.programID, "viewPos"),  1,&camera.Position[0]);
        
        
        glUniform3f(glGetUniformLocation(ourShader.programID, "material.ambient"),  1.0f, 0.5f, 0.31f);
        glUniform3f(glGetUniformLocation(ourShader.programID, "material.diffuse"),  1.0f, 0.5f, 0.31f);
        glUniform3f(glGetUniformLocation(ourShader.programID, "material.specular"),  0.5f, 0.5f, 0.5f);
        glUniform1f(glGetUniformLocation(ourShader.programID, "material.shininess"), 32.0f);
        
        
        glm::vec3 lightColor;
        lightColor.x = sin(glfwGetTime() * 2.0f);
        lightColor.y = sin(glfwGetTime() * 0.7f);
        lightColor.z = sin(glfwGetTime() * 1.3f);

        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); // 降低影响
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // 很低的影响

        
//        glUniform3f(glGetUniformLocation(ourShader.programID, "light.ambient"),  0.1f,0.1f,0.1f  );
//        glUniform3f(glGetUniformLocation(ourShader.programID, "light.diffuse"),  1.0f, 1.0f, 1.0f);
//        glUniform3f(glGetUniformLocation(ourShader.programID, "light.specular"),  .5f, .5f, 0.5f);
        
        glUniform3fv(glGetUniformLocation(ourShader.programID, "light.ambient"),  1,&ambientColor[0] );
        glUniform3fv(glGetUniformLocation(ourShader.programID, "light.diffuse"),  1,&diffuseColor[0]);
        glUniform3f(glGetUniformLocation(ourShader.programID, "light.specular"),  1.0f, 1.0f, 1.0f);
        
        
        //        glUniform3fv(glGetUniformLocation(ourShader.programID, "lightPos"), 1, &lightPos[0]);
        
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
        lampShader.user();
        
        // Model matrix
        glm::mat4 model2 = glm::mat4(1.0f);
        model2 = glm::translate(model2,lightPos);
        model2 = glm::scale(model2, glm::vec3(0.2f)); // a smaller cube
        
        // view
        //        glm::mat4 view2 = camera.GetViewMatrix();
        
        
        glUniformMatrix4fv(glGetUniformLocation(lampShader.programID,"model"),1, GL_FALSE,glm::value_ptr(model2));
        glUniformMatrix4fv(glGetUniformLocation(lampShader.programID,"view"),1, GL_FALSE,glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(lampShader.programID,"projection"),1, GL_FALSE,glm::value_ptr(projection));
        
        
        glBindVertexArray(vao);
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        
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
