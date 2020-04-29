#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	string vertexString;
	string fragmentString;
	const char* vectexSource;
	const char* fragmentSource;
	unsigned int ID;//shaderProgram ID
	//~Shader();
	void use();//useglUseProgram
	void SetUniform3f(const char* paraNameString, glm::vec3 param);
	void SetUniform1f(const char* paraNameString, float param);
private:
	void checkComplieError(unsigned int ID,string type);
};


