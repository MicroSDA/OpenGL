#ifndef MESH_H
#define MESH_H

#include <SFML\Graphics.hpp>
#include <GL\glew.h>
#include <iostream>
#include <string>
#include <vector>


#include "obj_loader.h"
#include "shader.h"
#include "Textur.h"


class Mesh
{
public:
	Mesh(const std::string& fileName);
    ~Mesh();
	void Draw();
	void SetShader(Shader &shader);
	void SetPosition(GLfloat x, GLfloat y, GLfloat z);
	void Move(GLfloat x, GLfloat y, GLfloat z);
	void SetScale(GLfloat x);
	void SetRotaited(GLfloat x, GLfloat y, GLfloat z);
	void AtachCamera( Camera &camera);
	sf::Vector3f GetPosition();
	sf::Vector3f GetScale();
	sf::Vector3f GetRotaited();
	void loadTextureFromFile(const std::string &filename);
private:
	enum MeshBufferPositions
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB
	};
	void operator=(const Mesh& mesh) {}
	Mesh(const Mesh& mesh){}
	static const unsigned int NUM_BUFFERS = 4;
	void InitMesh(const IndexedModel& model);

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_numIndices;
	Shader *shader = NULL;
	Camera *camera = NULL;
	Transform transform;
	Textur texture;
	
};
#endif // MESH_H