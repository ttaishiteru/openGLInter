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
#include "Camera.h"
#include "Shader.h"

using namespace std;

#pragma region Model Data
float vertices[] = {//正方体的顶点/uv
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};//正方体位置
#pragma endregion


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

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);//绑定VAO

	unsigned int VBO;
	glGenBuffers(1, &VBO);//生成VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	unsigned int TexBufferA;
	glGenTextures(1, &TexBufferA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexBufferA);//默认进入uniform
	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannel, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//jpg用GL_RGB
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Load Image Failed" << endl;
	}
	stbi_image_free(data);

	unsigned int TexBufferB;
	glGenTextures(1, &TexBufferB);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TexBufferB);
	unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrChannel, 0);
	if (data2) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		//png用GL_RGBA
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Load Image Failed" << endl;
	}
	stbi_image_free(data2);

	Camera camera(glm::vec3(0.0, 0.0, 3.0f), glm::vec3(0,0,0),glm::vec3(0,1.0f,0));//造出camera

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);

	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 viewMat = glm::mat4(1.0f);
	viewMat = camera.getViewMat();
	glm::mat4 projMat = glm::mat4(1.0f);
	projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	
	Shader *shaderIn = new Shader("vertexSource.vert", "fragmentSource.frag");

	while (!glfwWindowShouldClose(window)) {//渲染循环
		//探测用户是否要关闭window
		processInput(window);

		//trans = glm::translate(trans, glm::vec3(0.001f, 0.0f, 0.0f));动态移动
		glClearColor(0, 0.5f, 0.5f, 1.0f);//RGB,透明值
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清屏避免出现上一帧画面

		glBindVertexArray(VAO);

		//发出10次Draw Call
		for (int i = 0;i < 10;i++) {
			glm::mat4 tmpMat = glm::mat4(1.0f);
			tmpMat = glm::translate(tmpMat, cubePositions[i]);
			glUniform1i(glGetUniformLocation(shaderIn->ID, "ourTexture"), 0);
			glUniform1i(glGetUniformLocation(shaderIn->ID, "ourFace"), 1);

			glUniformMatrix4fv(glGetUniformLocation(shaderIn->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(tmpMat));
			glUniformMatrix4fv(glGetUniformLocation(shaderIn->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(shaderIn->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));//局部空间->投影空间的变化

			shaderIn->use();

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glfwSwapBuffers(window);//交换颜色缓存区块，buffer包含颜色的信息
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}