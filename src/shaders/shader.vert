#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec4 color;

out vec4 vertexColor;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    //vertexColor = color;
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
}

