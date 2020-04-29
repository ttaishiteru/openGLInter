#pragma once
#include"Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Material
{
public:
	Shader* shader;
	glm::vec3 diffuse;
	glm::vec3 ambient;
	glm::vec3 specular;
	float shineiness;
	Material(Shader* _shader, glm::vec3 _diffuse, glm::vec3 _ambient, glm::vec3 _specular, float _shineiness) :
		shader(_shader),
		diffuse(_diffuse),
		specular(_specular),
		ambient(_ambient),
		shineiness(_shineiness) 
	{
	}
	~Material();
};

