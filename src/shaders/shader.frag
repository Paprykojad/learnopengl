#version 330 core
in vec4 vertexColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    //FragColor = vertexColor;
    FragColor = mix(mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2), vertexColor, 0.2);
} 

