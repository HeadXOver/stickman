#shader vertex
#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;

uniform mat4 uMvp;

out vec2 texCoord;

void main()
{
    gl_Position = uMvp * vec4(aPos, 0.0, 1.0);
    texCoord = aTex;
}

#shader fragment
#version 330 core

out vec4 FragColor;
in vec2 texCoord;

uniform vec3 uColor;
uniform sampler2D uTexture;

void main()
{
    FragColor = vec4(uColor, 1.f) * texture(uTexture, texCoord);
}