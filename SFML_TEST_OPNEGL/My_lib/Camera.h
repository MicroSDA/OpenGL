#ifndef  CAMERA_H
#define  CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
	Camera(const glm::vec3 & pos, float fov, float aspect, float zNear, float zFar);
	~Camera();
     glm::mat4 GetViewProjection() const;
	 void MoveForward(float amt);
	 void MoveRight(float amt);
	 void MoveLeft(float amt);
	 void RotateY(float angle);
	 void Pitch(float angle);
	 void setPosition(const glm::vec3 & pos);
	 void newInit(const glm::vec3 & pos, float fov, float aspect, float zNear, float zFar);
	 void forResize(float aspect);
	 glm::vec3 getPosition();
private:
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;

	float fov;
	float zfar;
	float znear;

};
#endif // CAMERA_H
