#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 _position, glm::vec3 _target, glm::vec3 _worldup)//���λ��/Ŀ������/����up
{
	Position = _position;
	Forword = glm::normalize(_target  -  _position);//ת�ɵ�λ����
	Right = glm::normalize(glm::cross(Forword, _worldup));//��ˣ��нǲ�һ����90��
	Up = glm::normalize(glm::cross(Forword, Right));//���
	WorldUp = _worldup;
	//glm::mat4 view = glm::mat4(1.0f);
	//view = getViewMat();

}

Camera::Camera(glm::vec3 _position, float _pitch, float _yaw, glm::vec3 _worldup) {
	Pitch = _pitch;
	Yaw = _yaw;
	Position = _position;
	WorldUp = _worldup;
	Forword.x = glm::cos(_pitch)*glm::sin(_yaw);
	Forword.y = glm::sin(_pitch);
	Forword.z = glm::cos(_pitch) * glm::cos(_yaw);
	Right = glm::normalize(glm::cross(Forword, _worldup));
	Up = glm::normalize(glm::cross(Forword, Right));
}

void Camera::UpdateCameraVectors() {//��������ͷλ��
	Forword.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forword.y = glm::sin(Pitch);
	Forword.z = glm::cos(Pitch)*glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forword, WorldUp));
	Up = glm::normalize(glm::cross(Forword, Right));
}

glm::mat4  Camera::getViewMat() {
	return glm::lookAt(Position, Position + Forword, WorldUp);
	//���λ�ã�Ŀ��λ�ã�����Up
}

void Camera::UpdateCameraPos() {//���������ƶ������ǰ��/����
	Position += Forword * speedZ * 0.01f;
}

void  Camera::ProcessMouseMovement(float deltaX, float deltaY) {
	Pitch += deltaY*0.0005f;
	Yaw += deltaX*0.0005f;
	UpdateCameraVectors();
}
//Camera::~Camera()
//{
//}
