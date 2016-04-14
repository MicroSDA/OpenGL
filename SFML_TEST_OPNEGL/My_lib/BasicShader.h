#ifndef BASICSHADER_H
#define BASICSHADER_H

#include "Shader.h"
class BasicShader:public Shader
{
public:
	BasicShader();
	~BasicShader();
	void Update(const Transform& transform, const Camera& camera);
	void SetMinLightStr(float str);
	void SetMaxLightStr(float str);
	void SetLightPosition(GLfloat x, GLfloat y, GLfloat z);
private:
	void Init();
	//Difufuse
	GLfloat LightMinStr_U = 0.2;
	GLfloat LightMaxStr_U = 1.0;
	//Specular
	float SHINE_DAMPER;
	float RFLECTIVITY;


	glm::vec3 m_light_pos = glm::vec3(0.0,-1.0,0.0);
};
#endif // BASICSHADER_H
