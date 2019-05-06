#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

void main()
{
    vec4 texColor = texture(texture1, TexCoords);
    if(texColor.a < 0.1) { // 告诉OpenGL什么情况下丢弃，关键字（discard）
        discard;
    }
    FragColor = texColor;
}
