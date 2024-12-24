//
// Created by fg on 12/22/24.
//

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
//#include <glad.h>
#include "../dependencies/headers/glad.h"
#include <iostream>

class Shader {
private:
    std::string loadFile(std::string path);
    int compileVertexShader(std::string path);
    int compileFragmentShader(std::string path);
    int createShaderProgram(int vertexShader, int fragmentShader);

public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(std::string vertexPath, std::string fragmentPath);

    // use/activate the shader
    void use();

    // utility uniform functions
    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;
};



#endif //SHADER_H
