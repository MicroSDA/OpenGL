#ifndef SKAYBOX_H
#define SKAYBOX_H
#include <SFML\Graphics.hpp>
#include <GL\glew.h>
#include <iostream>
#include <string>
#include <vector>

#include "BasicShader.h"
#include "Textur.h"
#include "obj_loader.h"
class Skaybox
{
public:
	Skaybox();
	~Skaybox();
	void Draw();
	void SetShader(BasicShader & shader);
    void AtachCamera(Camera &camera);
	void SetFront(const std::string &fileneme);
	void SetBack(const std::string &fileneme);
	void SetLeft(const std::string &fileneme);
	void SetRight(const std::string &fileneme);
	void SetBotom(const std::string &fileneme);
	void SetTop(const std::string &fileneme);
	void SetSize(float size = 10);
	void SetPos(GLfloat x,GLfloat y,GLfloat z);
	void Init();
private:
	
	Textur m_texture[6];
	Transform m_transform;
	BasicShader *shader = NULL;
	Camera *camera = NULL;

	IndexedModel m_box[6];
	float m_size=100;


	GLuint m_vertexArrayObject_f;
	GLuint m_vertexArrayBuffers_f[2];

	GLuint m_vertexArrayObject_b;
	GLuint m_vertexArrayBuffers_b[2];

	GLuint m_vertexArrayObject_l;
	GLuint m_vertexArrayBuffers_l[2];

	GLuint m_vertexArrayObject_r;
	GLuint m_vertexArrayBuffers_r[2];

	GLuint m_vertexArrayObject_bo;
	GLuint m_vertexArrayBuffers_bo[2];

	GLuint m_vertexArrayObject_t;
	GLuint m_vertexArrayBuffers_t[2];

	
};
#endif // SKAYBOX_H
