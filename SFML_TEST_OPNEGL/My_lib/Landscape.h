#ifndef LANDSCAPE_H
#define LANDSCAPE_H
#include <SFML\Graphics.hpp>
#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <vector>
#include <iostream>

#include "shader.h"
#include "Textur.h"
#include "obj_loader.h"
class Landscape
{
public:
	Landscape();
	~Landscape();
	bool LoadHeightMap(const std::string &filename);
	void Draw();
	void AtachCamera(Camera &camera);
	void loadTextureFromFile(const std::string &filename);
	void SetShader(Shader &shader);
	void SetScale(GLfloat x);
	void SetRotaited(GLfloat x, GLfloat y, GLfloat z);
	void LoadHeightMap_TEST(const std::string &filename);
private:
	IndexedModel m_landscape_i;

	sf::Image m_image;
	std::vector<glm::vec3> m_landscape;

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[4];

	GLuint num_vertex;
	Shader *shader = NULL;
	Camera *camera = NULL;
	Transform transform;
	Textur texture;

};
#endif // LANDSCAPE_H
