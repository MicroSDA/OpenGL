#ifndef  CAMERA_H
#define  CAMERA_H
#include <SFML\Graphics.hpp>
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <Windows.h>
class Camera
{
public:
	Camera(const glm::vec3 & pos, float fov, float aspect, float zNear, float zFar);
	~Camera();
     glm::mat4 GetViewProjection() const;
	 void MoveXYZ(GLfloat x,GLfloat y,GLfloat z);
	 void MoveForward(float amt);
	 void MoveRight(float amt);
	 void MoveLeft(float amt);
	 void RotateY(float angle);
	 void Pitch(float angle);
	 void setPosition(const glm::vec3 & pos);
	 void newInit(const glm::vec3 & pos, float fov, float aspect, float zNear, float zFar);
	 void forResize(float aspect);
	 glm::vec3 getPosition();
	 void Update(sf::RenderWindow &window, float speed);
	 void SetSensitivity(float sensitivity);
	 float &GetReferencePositionX();
	 float &GetReferencePositionZ();
	 float &GetReferencePositionY();
	 
private:
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;

	float fov;
	float zfar;
	float znear;

	float x;
	float y;
	float z;


	glm::vec2 Mouse_poss;
	float angleX = 0, angleY = 0;
	int xt = 0;
	int yt = 0;
	float m_sensitivity = 1;


};
#endif // CAMERA_H
