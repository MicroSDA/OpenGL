#include "Camera.h"


Camera::Camera(const glm::vec3 & pos, float fov, float aspect, float zNear, float zFar)
{
	ShowCursor(false);
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

void Camera::MoveXYZ(GLfloat x, GLfloat y, GLfloat z)
{
	pos.x = pos.x + x;
	pos.y = pos.y + y;
	pos.z = pos.z + z;
}

void Camera::MoveForward(float amt)
{
	pos+= forward * amt;
	//pos.z += forward.z * amt;
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

void Camera::Update(sf::RenderWindow & window, float speed)
{
	ShowCursor(false);
	Mouse_poss.x = sf::Mouse::getPosition(window).x;
	Mouse_poss.y = sf::Mouse::getPosition(window).y;

	xt = window.getSize().x / 2;
	yt = window.getSize().y / 2;

	angleX += (xt - Mouse_poss.x) / m_sensitivity /speed; // Ч чувствительность 
	angleY += (yt - Mouse_poss.y) / m_sensitivity /speed;


	if (angleY<-89.0) { angleY = -89.0; }
	if (angleY>89.0) { angleY = 89.0; }

	sf::Mouse::setPosition(sf::Vector2i(xt, yt), window);

	Pitch(angleY / 10);
	RotateY(angleX / 10);
	angleY = 0.0;
	angleX = 0.0;



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		MoveForward(0.1*speed);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		MoveForward(-0.1*speed);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		MoveLeft(0.1*speed);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		MoveRight(0.1*speed);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		MoveXYZ(0, 0.5*speed, 0);
	}
}

void Camera::SetSensitivity(float sensitivity)
{
	m_sensitivity = sensitivity;
}

float &Camera::GetReferencePositionX()
{
	return x= pos.x;
}

float & Camera::GetReferencePositionZ()
{
	return y = pos.y;
}

float & Camera::GetReferencePositionY()
{
	return (z = pos.z);
}
