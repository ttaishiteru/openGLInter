#version 330 core								
layout(location = 0) in vec3 aPos;					
layout(location = 1) in vec3 aNormal;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec3 Normal;
out vec3 FragPos;
void main() {
	gl_Position = projMat * viewMat * modelMat * vec4(aPos, 1.0f);
	FragPos =  (modelMat * vec4(aPos, 1.0f)).xyz;
	Normal = mat3(transpose(inverse(modelMat))) * aNormal;
}