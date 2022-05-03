#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 UV;

out vec2 UV_Coords;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(position, 1);
    UV_Coords = UV;
};
#shader fragement
#version 330 core

out vec4 color;
in vec2 UV_Coords;

uniform sampler2D Texture;

void main()
{
    color = texture(Texture, UV_Coords);
};