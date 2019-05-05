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
    
    void Shader::use()  {
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
    
    void Shader::setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void Shader::setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void Shader::setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
    {
        glUniform2fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
    }
    void Shader::setVec2(const std::string &name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(programID, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
    }
    void Shader::setVec3(const std::string &name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(programID, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
    {
        glUniform4fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
    }
    void Shader::setVec4(const std::string &name, float x, float y, float z, float w)
    {
        glUniform4f(glGetUniformLocation(programID, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

}


