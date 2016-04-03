#include "Camera.h"


Camera::Camera(const glm::vec3 & pos, float fov, float aspect, float zNear, float zFar)
{
	this->pos = pos;
	this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->projection = glm::perspective(fov, aspect, zNear, zFar);

	this->fov = fov;
	this->zfar = zFar;
	this->znear = zNear;
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetViewProjection() const
{	
  return projection * glm::lookAt(pos, pos + forward, up);
}

void Camera::MoveForward(float amt)
{
	pos += forward * amt;
}

void Camera::MoveRight(float amt)
{
	pos -= glm::cross(up, forward) * amt;

}

void Camera::MoveLeft(float amt)
{
	pos += glm::cross(up, forward) * amt;
}

void Camera::RotateY(float angle)
{
	static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

	glm::mat4 rotation = glm::rotate(angle, UP);
	forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
	up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
}

void Camera::Pitch(float angle)
{
	glm::vec3 right = glm::normalize(glm::cross(up, forward));
    forward = glm::vec3(glm::normalize(glm::rotate(-angle, right) * glm::vec4(forward, 0.0)));
	up = glm::normalize(glm::cross(forward, right));
}

void Camera::setPosition(const glm::vec3 & pos)
{
	this->pos = pos;
}

void Camera::newInit(const glm::vec3 & pos, float fov, float aspect, float zNear, float zFar)
{
	this->pos = pos;
	this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->projection = glm::perspective(fov, aspect, zNear, zFar);
}

void Camera::forResize(float aspect)
{
	this->projection = glm::perspective(fov, aspect, znear, zfar);
}

glm::vec3 Camera::getPosition()
{
	return pos;
}
