//
//  Shader.hpp
//  Glitter
//
//  Created by fangshufeng on 2019/4/10.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


namespace Our {
    class Shader {
    public:
        unsigned int programID;
        Shader(const char *vertexPath, const char *fragmentPath);
        void  user() ;
    private:
        void checkError(GLuint shader,std::string type);
    };
}


#endif /* Shader_hpp */
