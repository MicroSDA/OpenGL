#ifndef TERRAIN_H
#define TERRAIN_H

#include <SFML\Graphics.hpp>
#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <vector>
#include <iostream>

#include "BasicShader.h"
#include "Textur.h"
#include "obj_loader.h"

class Terrain
{
public:
	Terrain();
	~Terrain();

	void LoadFromFile(const std::string &filemane);
	void Init();
	
	void Draw();
	void SetShader(BasicShader &shader);
	void SetHeight(int height);
	void SetTexture(const std::string &filename);
	float GetHeightOnPoint(float x, float z);
	void AtachCamera(Camera &camera);
	void SetRotaited(GLfloat x, GLfloat y, GLfloat z);
	glm::vec2 GetSize();
	Transform GetTransfrom();
private:
	bool m_smooth = false;            // Smooth normals or not
	IndexedModel m_terrain;           // Terrain model vertexs, normals, texture coords.
	BasicShader *m_shader = NULL;     // Default transform, texture and lightning shader

	Camera *m_camera = NULL;          // Pointer for camera
	Textur  m_texture;                // Default Terrain texture
	sf::Image m_image;                // Image for texture
	///Vertexs Buffers/////////
	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[3];   // Vertex, texture and normals
	GLuint m_num_vertexs;             // Num of Vertexs
	Transform m_transform;            // Maxtrix of transformations

	int m_height = 1;                // This is height of terrain. Default = 1
	int m_image_size_x = 0;             // Size of image, horizontal and vertical
	int m_image_size_y = 0;

	float getHeight(int x, int z); // Get Hight of pixel on coords(bright)
	glm::vec3 getNormal(glm::vec3 a, glm::vec3 b, glm::vec3 c); // Get Normal of Vertex Point 
	float baryyCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 poss);
};
#endif // TERRAIN_H
