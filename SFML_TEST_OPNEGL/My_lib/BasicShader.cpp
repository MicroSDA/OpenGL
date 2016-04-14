#include "BasicShader.h"



BasicShader::BasicShader()
{

}


BasicShader::~BasicShader()
{
}

void BasicShader::Update(const Transform & transform, const Camera & camera)
{
	glm::mat4 MVP = transform.GetMVP(camera);
	glm::mat4 Normal = transform.GetModel();
	glUniformMatrix4fv(m_uniforms[0], 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(m_uniforms[1], 1, GL_FALSE, &Normal[0][0]);
	glUniform3f(m_uniforms[2], m_light_pos.x, m_light_pos.y, m_light_pos.z);
	glUniform1f(m_uniforms[3], LightMinStr_U);
	glUniform1f(m_uniforms[4], LightMaxStr_U);
	
}

void BasicShader::SetMinLightStr(float str)
{
	LightMinStr_U = str;
}

void BasicShader::SetMaxLightStr(float str)
{
	LightMaxStr_U = str;
}

void BasicShader::SetLightPosition(GLfloat x, GLfloat y, GLfloat z)
{
	m_light_pos.x = x;
	m_light_pos.y = y;
	m_light_pos.z = z;
}

void BasicShader::Init()
{
	glBindAttribLocation(m_program, 0, "Position");
	glBindAttribLocation(m_program, 1, "TexCoord");
	glBindAttribLocation(m_program, 2, "Normal");
	

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Invalid shader program");

	m_uniforms.push_back(glGetUniformLocation(m_program, "MVP_U"));
	m_uniforms.push_back(glGetUniformLocation(m_program, "Normal_U"));
	m_uniforms.push_back(glGetUniformLocation(m_program, "LightDirection_U"));
	m_uniforms.push_back(glGetUniformLocation(m_program, "LightMinStr_U"));
	m_uniforms.push_back(glGetUniformLocation(m_program, "LightMaxStr_U"));

}
