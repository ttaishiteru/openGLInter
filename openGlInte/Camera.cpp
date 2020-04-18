#include "Camera.h"



Camera::Camera(glm::vec3 _position, glm::vec3 target, glm::vec3 worlfup)
{
	Position = _position;
	Forword = glm::normalize(target  -  _position);
	Right = glm::normalize(glm::cross(Forword, worlfup));//²æ³Ë
	Up = glm::normalize(glm::cross(Forword, Right));//²æ³Ë
	WorldUp = worlfup;
	

}

glm::mat4  Camera::getViewMat() {
	return glm::lookAt(Position, Position + Forword, WorldUp);
}

//Camera::~Camera()
//{
//}
