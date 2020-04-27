#version 330 core 
//in vec4 vertexColor;
in vec2 texCoord;
uniform sampler2D ourTexture;
uniform sampler2D ourFace;
out vec4 FragColor; 
void main() {
//FragColor = texture(ourTexture,texCoord) * vertexColor;
FragColor = mix(texture(ourTexture,texCoord),texture(ourFace,texCoord),0.1);
}