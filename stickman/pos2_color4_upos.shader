#shader vertex
#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;

out vec4 vColor;

uniform mat4 uMvp;
uniform vec2 uOffset = vec2(0.f, 0.f);

void main()
{
    gl_Position = uMvp * vec4(aPos + uOffset, 0.f, 1.f);
    vColor = aColor;
}

#shader fragment
#version 330 core

in vec4 vColor;

out vec4 FragColor;

void main()
{
    FragColor = vColor;
}