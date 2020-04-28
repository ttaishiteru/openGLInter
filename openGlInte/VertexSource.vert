#version 330 core									
layout(location = 0) in vec3 aPos;					
layout(location = 1) in vec3 aNormal;
//layout(location = 2) in vec2 aTexCoord;
//out vec4 vertexColor;
//out vec2 texCoord;
out vec3 Normal;
out vec3 FragPos;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;
void main() {
gl_Position = projMat * viewMat * modelMat * vec4(aPos, 1.0f);
//vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0);
//texCoord = aTexCoord;
}