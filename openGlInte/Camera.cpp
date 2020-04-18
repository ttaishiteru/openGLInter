#include "Camera.h"



Camera::Camera(glm::vec3 _position, glm::vec3 target, glm::vec3 worlfup)
{
	Position = _position;
	Forword = glm::normalize(target  -  _position);
	Right = glm::normalize(glm::cross(Forword, worlfup));//���
	Up = glm::normalize(glm::cross(Forword, Right));//���
	WorldUp = worlfup;
	

}

glm::mat4  Camera::getViewMat() {
	return glm::lookAt(Position, Position + Forword, WorldUp);
}

//Camera::~Camera()
//{
//}
