#ifndef TRANSFORM_H
#define TRANSFORM_H



#include "Camera.h"


class Transform
{
public:
	Transform(const glm::vec3 & pos = glm::vec3(), const glm::vec3 & rotate = glm::vec3(), const glm::vec3 & scale = glm::vec3(1.0f, 1.0f, 1.0f));
	~Transform();

     glm::mat4 GetModel() const;

	 glm::vec3 &GetPos();
	 glm::vec3 &GetRotate();
	 glm::vec3 &GetScale();

	 void SetPos(glm::vec3 &pos);
	 void SetRotate(glm::vec3 &rotate);
	 void SetScale(glm::vec3 &scale);
	 glm::mat4 GetMVP(const Camera& camera) const;

	 void SetModel(glm::mat4 model);

private:

	glm::vec3 m_pos;
	glm::vec3 m_rotate;
	glm::vec3 m_scale;
	glm::mat4 m_matrix_t;
};

#endif // TRANSFORM_H