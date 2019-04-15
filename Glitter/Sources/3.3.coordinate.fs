

#version 330 core

out vec4 FragColor;

in vec4 ourColor;
in vec2 ourTextCoords;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;

void main() {
    //    FragColor = mix(texture(texture1,ourTextCoords),texture(texture2,ourTextCoords),0.2)  ;
    FragColor =  mix(texture(texture1, ourTextCoords), texture(texture2, vec2(1.0 - ourTextCoords.x, ourTextCoords.y)), mixValue);
}
