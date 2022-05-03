#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 Color;

out vec3 OutColor;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(position, 1);

    OutColor = Color;
};
#shader fragement
#version 330 core

out vec3 color;

in vec3 OutColor;

void main()
{
    color = OutColor;
};