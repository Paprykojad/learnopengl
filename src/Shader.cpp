#include "Shader.h"

std::string Shader::loadFile(std::string path) {
    std::string dest;
    try {
        std::ifstream file(path);
        if (!file)
            dest = nullptr;
        dest = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()); // Read file content
    } catch (const std::exception e) {
        throw e;
    }
    //cout << "read: '" << dest << "'" << endl;
    return dest;
}

int Shader::compileFragmentShader(std::string path) {
    unsigned int fragmentShader;
    std::string src = loadFile(path).c_str();
    const char *fragmentShaderSource = src.c_str();
    //cout << "\"" << *fragmentShaderSource << "\"" <<  endl;

    int success;
    char infoLog[512];

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        throw "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED";
    }
    return fragmentShader;
}

int Shader::compileVertexShader(std::string path) {
    unsigned int vertexShader;
    std::string src = loadFile(path).c_str();
    const char *vertexShaderSource = src.c_str();
    //cout << "\"" <<  *vertexShaderSource << "\"" <<  endl;

    int  success;
    char infoLog[512];

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        throw "ERROR::SHADER::VERTEX::COMPILATION_FAILED";
    }
    return vertexShader;
}

int Shader::createShaderProgram(int vertexShader, int fragmentShader) {
    int success;
    char infoLog[512];

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        throw "ERROR::SHADER::PROGRAM::LINKING_FAILED";
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

Shader::Shader(std::string vertexPath, std::string fragmentPath) {
    unsigned int vertexShader = compileVertexShader(vertexPath);
    unsigned int fragmentShader = compileFragmentShader(fragmentPath);
    ID = createShaderProgram(vertexShader, fragmentShader);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}