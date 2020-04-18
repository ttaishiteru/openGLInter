#pragma once
#include <string>

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
	void use();//µ÷ÓÃglUseProgram
private:
	void checkComplieError(unsigned int ID,string type);
};


