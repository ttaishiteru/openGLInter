#pragma once//一个标头只编译一次
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#ifndef  CAMERA_H
//#define  CAMERA_H
class Camera
{
public:
	Camera(glm::vec3 _position,glm::vec3 _target,glm::vec3 _worldup);
	Camera(glm::vec3 _position, float _pitch, float _yaw, glm::vec3 _worldup);
	glm::vec3 Position;
	glm::vec3 Forword;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	float Pitch;
	float Yaw;
	float speedX = 1.0f;
	float speedY = 1.0f;
	float speedZ;
	//~Camera();
	glm::mat4 getViewMat();
	void ProcessMouseMovement(float deltaX, float deltaY);
	void UpdateCameraPos();
private:
	void UpdateCameraVectors();
};
//#endif

