#version 330 core 
//in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;

out vec4 FragColor;

void main(){
	//Phong
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,Normal);//reflect light
	vec3 cameraVec = normalize(cameraPos - FragPos);

	float specularAmount = pow(max(dot(reflectDir,cameraVec),0),256);
	vec3 specular = specularAmount * lightColor;

	vec3 diffuse = max(dot(lightDir,Normal),0) * lightColor;//diffuse Intensity * lightColor
	//FragColor = vec4(objColor * ambientColor,1.0f);
	FragColor = vec4((diffuse + ambientColor + specular)*objColor,1.0f);

}
