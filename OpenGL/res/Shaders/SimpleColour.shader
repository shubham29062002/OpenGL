#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 Color;

out vec3 Color_info;

uniform mat4 MVP;

void main()
{
   gl_Position = MVP * vec4(position,1);
   Color_info = Color;
};

#shader fragement
#version 330 core

out vec4 color;

in vec3 Color_info;

void main()
{
   color = vec4(Color_info,1);
};
