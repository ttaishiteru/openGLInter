#version 330 core 
//in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shineiness;
};

uniform Material material;
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;

out vec4 FragColor;

void main(){
	//Phong Mode
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,Normal);//reflect light
	vec3 cameraVec = normalize(cameraPos - FragPos);

	float specularAmount = pow(max(dot(reflectDir,cameraVec),0),material.shineiness);
	vec3 specular = material.specular * specularAmount * lightColor;

	vec3 diffuse = material.diffuse * max(dot(lightDir,Normal),0) * lightColor;
	//diffuse Intensity * lightColor

	vec3 ambient = material.ambient * ambientColor;
	FragColor = vec4((diffuse + ambient + specular)*objColor,1.0f);

}
