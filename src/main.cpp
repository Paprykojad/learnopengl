#include <cmath>
#include <exception>
#include <iostream>
#include <iterator>
#include <fstream>
#include <ostream>
#include "../dependencies/headers/glad.h"
#include "../dependencies/headers/glfw3.h"

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
    //cout << "read: '" << dest << "'" << endl;
    return dest;
}

int compileVertexShader(string path) {
    unsigned int vertexShader;
    string src = loadFile(path).c_str();
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

int compileFragmentShader(string path) {
    unsigned int fragmentShader;
    string src = loadFile(path).c_str();
    const char *fragmentShaderSource = src.c_str();
    //cout << "\"" << *fragmentShaderSource << "\"" <<  endl;

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
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
    };
    unsigned int indicies[] = {
        0, 1, 3,
        1, 2, 3,
    };
    unsigned int VBO; // verted buffer object
    unsigned int VAO; // vertex array object
    unsigned int EBO; // element buffer object
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    //kompilacja shaderu
    unsigned int vertexShader = compileVertexShader("../src/shaders/shader.vert");
    unsigned int fragmentShader = compileFragmentShader("../src/shaders/shader.frag");
    unsigned int shaderProgram = createShaderProgram(vertexShader, fragmentShader);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    cout << "Terminating program" << endl;
    return 0;
}
