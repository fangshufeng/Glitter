
#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

const float offset = 1.0 / 300.0;

const int obscure = 16;

void main()
{
        FragColor = texture(texture1, TexCoords);
}
