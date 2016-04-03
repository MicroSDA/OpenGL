#include "Transform.h"





Transform::Transform(const glm::vec3 &pos, const glm::vec3 &rotate, const glm::vec3 &scale)
{
	m_pos = pos;
	m_scale = scale;
	m_rotate=rotate;
}

Transform::~Transform()
{
}

 glm::mat4 Transform::GetModel() const 
{

	glm::mat4 posMatrix = glm::translate(m_pos);
	glm::mat4 scaleMatrix = glm::scale(m_scale);

	glm::mat4 rotateXMatrix = glm::rotate(m_rotate.x, glm::vec3(1.0, 0.0, 0.0));
	glm::mat4 rotateYMatrix = glm::rotate(m_rotate.y, glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 rotateZMatrix = glm::rotate(m_rotate.z, glm::vec3(0.0, 0.0, 1.0));

	glm::mat4 rotateMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;

	glm::mat4 forR = posMatrix * rotateMatrix * scaleMatrix;
	
	return forR;
}


 glm::vec3 &Transform::GetPos()
{
	return m_pos;
}

 glm::vec3 &Transform::GetRotate()
{
	return m_rotate;
}

 glm::vec3 &Transform::GetScale()
{
	return m_scale;
}



void Transform::SetPos(glm::vec3 & pos)
{
	m_pos = pos;
}

 void Transform::SetRotate(glm::vec3 & rotate)
{
	m_rotate = rotate;
}

 void Transform::SetScale(glm::vec3 & scale)
{
	m_scale = scale;
}

 glm::mat4 Transform::GetMVP(const Camera & camera) const
 {
	 glm::mat4 VP = camera.GetViewProjection();
	 glm::mat4 M = GetModel();

	 return VP * M;//camera.GetViewProjection() * GetModel();
 }
