// Local Headers
#include "glitter.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>

#include <iostream>

using namespace std;

int main(int argc, char * argv[]) {
    
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
   GLFWwindow *window =  glfwCreateWindow(800, 600, "Hello World", nullptr, nullptr);
    if (window == nullptr) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    gladLoadGL();
    
    // Rendering Loop
    while (glfwWindowShouldClose(window) == false) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

            // Background Fill Color
            glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // Flip Buffers and Draw
            glfwSwapBuffers(window);
            glfwPollEvents();
    }
    glfwTerminate();
    
    return EXIT_SUCCESS;
    
}


//// Load GLFW and Create a Window
//glfwInit();
//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//auto mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGL", nullptr, nullptr);
//
//// Check for Valid Context
//if (mWindow == nullptr) {
//    fprintf(stderr, "Failed to Create OpenGL Context");
//    return EXIT_FAILURE;
//}
//
//// Create Context and Load OpenGL Functions
//glfwMakeContextCurrent(mWindow);
//gladLoadGL();
//fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
//
//// Rendering Loop
//while (glfwWindowShouldClose(mWindow) == false) {
//    if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(mWindow, true);
//
//        // Background Fill Color
//        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // Flip Buffers and Draw
//        glfwSwapBuffers(mWindow);
//        glfwPollEvents();
//        }   glfwTerminate();
//return EXIT_SUCCESS;
