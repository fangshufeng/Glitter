//
//  Shader.cpp
//  Glitter
//
//  Created by fangshufeng on 2019/4/10.
//

#include "Shader.hpp"

using namespace std;
namespace Our {
    
    Shader::Shader(const char *vertexPath, const char *fragmentPath) {
        // 读取文件内容
        string vertexCode ;
        string fragmentCode ;
        ifstream vShaderFile;
        ifstream fShaderFile;
        
        try {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);

            stringstream vShaderStream,fShaderStream;

            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            vShaderFile.close();
            fShaderFile.close();

            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();

        } catch (ifstream::failure e) {
            cout << "打开文件出错" << endl;
        }
        
        const char *vertexShaderSource = vertexCode.c_str();
        const char *fragmentShaderSource = fragmentCode.c_str();
        
        if (strcmp(vertexShaderSource, "") == 0 || strcmp(fragmentShaderSource, "") == 0) {
             cout << "文件内容为空" << endl;
        };
      
        // 创建着色器
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader,1,&vertexShaderSource,nullptr);
        glCompileShader(vertexShader);
        
        checkError(vertexShader, "VERTEX");
        
        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader,1,&fragmentShaderSource,nullptr);
        glCompileShader(fragmentShader);
        
        checkError(fragmentShader, "FRAGMENT");
        
        // 创建程序
        programID = glCreateProgram();
        
        glAttachShader(programID,vertexShader);
        glAttachShader(programID,fragmentShader);
        glLinkProgram(programID);
        
        checkError(programID, "PROGRAM");
        
        // 回收着色器
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    
    void Shader::user()  {
        glUseProgram(programID);
    }

    void Shader::checkError(GLuint shader, std::string type) {
        GLint success;
        GLchar infoLog[1024];
        if(type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if(!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if(!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
    
}

