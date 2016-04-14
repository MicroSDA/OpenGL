#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include "transform.h"
#include "Camera.h"
class Shader {

public:
	Shader();
	~Shader();
	void loadFromFile(const std::string &fileName);
	void Bind();
	void UnBind();
	virtual void Update();
protected:
	static const unsigned int NUM_SHADERS = 2;
	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);

	GLuint m_program;
	GLuint m_shaders [NUM_SHADERS];           // Vertex and Fragment Shader
	std::vector<GLuint> m_uniforms;
	virtual void Init()=0;
};
#endif // !SHADER_H