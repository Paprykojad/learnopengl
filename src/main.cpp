#include <cmath>
#include <exception>
#include <iostream>
#include <iterator>
#include <fstream>
#include <ostream>
#include <stdexcept>
#include "../dependencies/headers/glad.h"
#include "../dependencies/headers/glfw3.h"
// #include <glad.h>
// #include <glfw3.h>

using namespace std;

const uint windowWidth = 800;
const uint windowHeight = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}


string loadFile(string path) {
    string dest;
    try {
        ifstream file(path);
        if (!file)
            dest = nullptr;
        dest = string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>()); // Read file content
    } catch (const exception e) {
        throw e;
    }
    cout << "read: '" << dest << "'" << endl;
    return dest;
}

int compileVertexShader(string path) {
    unsigned int vertexShader;
    string src = loadFile(path).c_str();
    const char *vertexShaderSource = src.c_str();
    cout << "\"" <<  *vertexShaderSource << "\"" <<  endl;

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

int compileFragmentShader(string path) {
    unsigned int fragmentShader;
    string src = loadFile(path).c_str();
    const char *fragmentShaderSource = src.c_str();
    cout << "\"" << *fragmentShaderSource << "\"" <<  endl;

    int  success;
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

int createShaderProgram(int vertexShader, int fragmentShader) {

    int  success;
    char infoLog[512];

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        throw "ERROR::SHADER::PROGRAM::LINKING_FAILED";
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, windowWidth, windowHeight);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    //tworzenie danych
    float verticies[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
    };
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);



    //kompilacja shaderu
    unsigned int vertexShader;
    vertexShader = compileVertexShader("../src/shaders/shader.vert");
    // const char *vertexShaderSource = loadFile("../src/shaders/shader.vert").c_str();
    //
    // int  success;
    // char infoLog[512];
    //
    // vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // glCompileShader(vertexShader);
    //
    // glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    // if (!success) {
    //     glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    //     std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    // }

    unsigned int fragmentShader;
    fragmentShader = compileFragmentShader("../src/shaders/shader.frag");
    // const char *fragmentShaderSource = loadFile("../src/shaders/shader.frag").c_str();
    // fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // glCompileShader(fragmentShader);
    //
    // glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    // if (!success) {
    //     glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    //     std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    // }

    unsigned int shaderProgram;
    shaderProgram = createShaderProgram(vertexShader, fragmentShader);
    // shaderProgram = glCreateProgram();
    // glAttachShader(shaderProgram, vertexShader);
    // glAttachShader(shaderProgram, fragmentShader);
    // glLinkProgram(shaderProgram);
    //
    // glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    // if(!success) {
    //     glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    //     std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    // }

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // glDeleteShader(vertexShader);
    // glDeleteShader(fragmentShader);

    glUseProgram(shaderProgram);


    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    cout << "Terminating program" << endl;
    return 0;
}
