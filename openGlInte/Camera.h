#pragma once//一个标头只编译一次
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#ifndef  CAMERA_H
//#define  CAMERA_H
class Camera
{
public:
	Camera(glm::vec3 _position,glm::vec3 target,glm::vec3 worlfup);

	glm::vec3 Position;
	glm::vec3 Forword;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	//~Camera();
	glm::mat4 getViewMat();
};
//#endif

