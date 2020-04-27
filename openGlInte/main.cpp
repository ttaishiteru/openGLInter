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

#pragma region Camera Declare
//Camera camera(glm::vec3(0.0, 0.0, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0));//造出camera
Camera camera_ora(glm::vec3(0, 0, 3.0f), glm::radians(-15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));
#pragma endregion

#pragma region Input Declare
float lastX;
float lastY;
bool firstMouse = true;

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {//ESC键退出
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera_ora.speedZ = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		camera_ora.speedZ = -1.0f;
	}
}

void mouse_callBack(GLFWwindow *window,double xPos,double yPos) {
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}//判断是不是第一次进入

	float deltaX, deltaY;
	deltaX = xPos - lastX;
	deltaY = yPos - lastY;
	lastX = xPos;
	lastY - yPos;

	camera_ora.ProcessMouseMovement(deltaX, deltaY);
}
#pragma endregion

unsigned int LoadImageToGPU(const char* fileName,GLint internalFormat,GLenum format,int textureSlot) {

	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, TexBuffer);

	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(fileName, &width, &height, &nrChannel, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		//jpg用GL_RGB
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Load Image Failed" << endl;
	}
	stbi_image_free(data);
	return TexBuffer;
}

int main(int argc, char* argv[]) {

	#pragma region Open Window
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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//关闭游标
	glfwSetCursorPosCallback(window, mouse_callBack);

	//初始化GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "Init GLEW Failed!" << std::endl;
		glfwTerminate();
			return -1;
	}

	glViewport(0, 0, 600, 800);
	glEnable(GL_DEPTH_TEST);
#pragma endregion

	#pragma region Init and Load Models
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);//绑定VAO

	unsigned int VBO;
	glGenBuffers(1, &VBO);//生成VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	#pragma endregion

	#pragma region Load Textures
	unsigned int TexBufferA;
	TexBufferA = LoadImageToGPU("container.jpg",GL_RGB,GL_RGB,0);
	unsigned int TexBufferB;
	TexBufferB = LoadImageToGPU("awesomeface.png", GL_RGBA, GL_RGBA, 1);
	#pragma endregion

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	#pragma region Prepare MVP Matrices
	glm::mat4 modelMat = glm::mat4(1.0f);
	//modelMat = glm::rotate(modelMat, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 1.0f));
	glm::mat4 viewMat = glm::mat4(1.0f);
	//viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 projMat = glm::mat4(1.0f);
	projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	#pragma endregion

	#pragma region Init Shader
	Shader *shaderIn = new Shader("vertexSource.vert", "fragmentSource.frag");
	
#pragma endregion
	
#pragma 
	while (!glfwWindowShouldClose(window)) {//渲染循环
		
		//探测用户是否要关闭window
		processInput(window);

		//trans = glm::translate(trans, glm::vec3(0.001f, 0.0f, 0.0f));动态移动
		glClearColor(0, 0.5f, 0.5f, 1.0f);//RGB,透明值
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清屏避免出现上一帧画面

		viewMat = camera_ora.getViewMat();

		//发出Draw Call
		for (int i = 0;i < 10;i++) {
			modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);

			//Set Merterial -> Shader Program
			shaderIn->use();
			//Set Merterial -> Texture
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, TexBufferA);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, TexBufferB);
			//Set Merterial ->Uniform
			glUniform1i(glGetUniformLocation(shaderIn->ID, "ourTexture"), 0);
			glUniform1i(glGetUniformLocation(shaderIn->ID, "ourFace"), 1);
			glUniformMatrix4fv(glGetUniformLocation(shaderIn->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(shaderIn->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(shaderIn->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));//局部空间->投影空间
			//SetModel
			glBindVertexArray(VAO);
			//DrawCall
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//Clean up,prepare for next render loop
		glfwSwapBuffers(window);//交换颜色缓存区块，buffer包含颜色的信息
		glfwPollEvents();
		camera_ora.UpdateCameraPos();
	}
	//Exit Program
	glfwTerminate();
	return 0;
}