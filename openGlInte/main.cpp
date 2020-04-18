#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {//ESC键退出
		glfwSetWindowShouldClose(window, true);
	}
}

int main(int argc, char* argv[]) {

	//初始化GLFW windows
	glfwInit();//初始化glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//版本为3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建window
	GLFWwindow* window = glfwCreateWindow(800, 600, "openGL Inte", NULL, NULL);
	if (window == NULL) {
		std::cout << "Open GLFW Windows Failed!" << std::endl;
		glfwTerminate();//销毁所有数据
		return -1;
	}
	glfwMakeContextCurrent(window);

	//初始化GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "Init GLEW Failed!" << std::endl;
		glfwTerminate();
			return -1;
	}

	glViewport(0, 0, 600, 800);
		
	return 0;

}