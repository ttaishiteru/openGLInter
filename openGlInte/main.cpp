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
#include "Material.h"

using namespace std;

#pragma region Model Data
GLfloat vertices[] = {//����ͷ�����
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
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
};//������λ��
#pragma endregion

#pragma region Camera Declare
//Camera camera(glm::vec3(0.0, 0.0, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0));//���camera
Camera camera_ora(glm::vec3(0, 0, 3.0f), glm::radians(-15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));
#pragma endregion

#pragma region Input Declare
float lastX;
float lastY;
bool firstMouse = true;

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {//ESC���˳�
		glfwSetWindowShouldClose(window, true);
	}
	//z
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera_ora.speedZ = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		camera_ora.speedZ = -1.0f;
	}
	else {
		camera_ora.speedZ = 0.0f;
	}
	//x
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera_ora.speedX = -1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera_ora.speedX = 1.0f;
	}
	else {
		camera_ora.speedX = 0.0f;
	}
	//y
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		camera_ora.speedY = -1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		camera_ora.speedY = 1.0f;
	}
	else {
		camera_ora.speedY = 0.0f;
	}
}

void mouse_callBack(GLFWwindow *window,double xPos,double yPos) {
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}//�ж��ǲ��ǵ�һ�ν���

	float deltaX, deltaY;
	deltaX = xPos - lastX;
	deltaY = yPos - lastY;
	lastX = xPos;
	lastY = yPos;

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
		//jpg��GL_RGB
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
	//��ʼ��GLFW windows
	glfwInit();//��ʼ��glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//�汾Ϊ3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//����window
	GLFWwindow* window = glfwCreateWindow(800, 600, "openGL Inte", NULL, NULL);
	if (window == NULL) {
		std::cout << "Open GLFW Windows Failed!" << std::endl;
		glfwTerminate();//������������
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//�ر��α�
	glfwSetCursorPosCallback(window, mouse_callBack);

	//��ʼ��GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "Init GLEW Failed!" << std::endl;
		glfwTerminate();
			return -1;
	}

	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);
#pragma endregion

	#pragma region Init and Load Models
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);//��VAO

	unsigned int VBO;
	glGenBuffers(1, &VBO);//����VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	#pragma endregion

	#pragma region Load Textures
	unsigned int TexBufferA;
	TexBufferA = LoadImageToGPU("container.jpg",GL_RGB,GL_RGB,0);
	unsigned int TexBufferB;
	TexBufferB = LoadImageToGPU("awesomeface.png", GL_RGBA, GL_RGBA, 1);
	#pragma endregion

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
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
	Shader *shaderIn = new Shader("Light.vert", "LightColor.frag");
	
#pragma endregion
	
	#pragma region Init Material
	Material *myMaterial = new Material(shaderIn,
		glm::vec3(0.0f,0.0f,1.0f),
		glm::vec3(1.0f,1.0f,1.0f),
		glm::vec3(1.0f,1.0f,1.0f),
		32.0f);

	#pragma endregion

#pragma 
	while (!glfwWindowShouldClose(window)) {//��Ⱦѭ��
		
		//̽���û��Ƿ�Ҫ�ر�window
		processInput(window);

		//trans = glm::translate(trans, glm::vec3(0.001f, 0.0f, 0.0f));��̬�ƶ�
		//glClearColor(0, 0.5f, 0.5f, 1.0f);//RGB,͸��ֵ
		glClearColor(0, 0, 0, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�������������һ֡����

		viewMat = camera_ora.getViewMat();

		//����Draw Call
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
			//glUniform1i(glGetUniformLocation(shaderIn->ID, "ourTexture"), 0);
			//glUniform1i(glGetUniformLocation(shaderIn->ID, "ourFace"), 1);
			myMaterial->shader->SetUniform3f("material.ambient", myMaterial->ambient);
			myMaterial->shader->SetUniform3f("material.diffuse", myMaterial->diffuse);
			myMaterial->shader->SetUniform3f("material.specular", myMaterial->specular);
			myMaterial->shader->SetUniform1f("material.shineiness", myMaterial->shineiness);

			glUniform3f(glGetUniformLocation(shaderIn->ID, "objColor"), 1.0f, 0.5f, 0.3f);//ģ����ɫ
			glUniform3f(glGetUniformLocation(shaderIn->ID, "ambientColor"), 0.2f, 0.1f, 0.0f);//������
			glUniform3f(glGetUniformLocation(shaderIn->ID, "lightPos"), 10.0f, 10.0f, -5.0f);//diffuseλ��
			glUniform3f(glGetUniformLocation(shaderIn->ID, "lightColor"), 1.0f, 1.0f, 1.0f);//diffuse��ɫ
			glUniform3f(glGetUniformLocation(shaderIn->ID, "cameraPos"), camera_ora.Position.x, camera_ora.Position.y, camera_ora.Position.z);
			glUniformMatrix4fv(glGetUniformLocation(shaderIn->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(shaderIn->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(shaderIn->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));//�ֲ��ռ�->ͶӰ�ռ�
			//SetModel
			glBindVertexArray(VAO);
			//DrawCall
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//Clean up,prepare for next render loop
		glfwSwapBuffers(window);//������ɫ�������飬buffer������ɫ����Ϣ
		glfwPollEvents();
		camera_ora.UpdateCameraPos();
	}
	//Exit Program
	glfwTerminate();
	return 0;
}