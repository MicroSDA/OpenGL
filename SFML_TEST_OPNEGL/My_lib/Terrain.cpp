#include "Terrain.h"

Terrain::Terrain()
{
}


Terrain::~Terrain()
{
}

void Terrain::LoadFromFile(const std::string & filemane)
{
	if (!m_image.loadFromFile(filemane.c_str())) {
		std::cerr << "Image "<<filemane.c_str()<<" not found or not load\n";
	}

	m_image_size_x = m_image.getSize().x;
	m_image_size_y = m_image.getSize().y;
}

void Terrain::Init()
{
	if (m_shader == NULL) 
		std::cerr << "Shader is nor set !\n";
	
	if (m_camera == NULL) 
		std::cerr << "Camera is not atach !\n";
	

	glm::vec3 normal;
	for (int x = 0; x < m_image_size_y-1; x++) {
		for (int z = 0; z < m_image_size_x-1; z++) {

			

			//First Triangle
			///V1
			m_terrain.positions.push_back(glm::vec3(x, getHeight(x, z), z));
			///V2
			m_terrain.positions.push_back(glm::vec3(x, getHeight(x, z + 1), z + 1));
			///V3
			m_terrain.positions.push_back(glm::vec3(x + 1, getHeight(x + 1, z), z));
			
			///Normals
			normal = getNormal(glm::vec3(x, getHeight(x, z), z), glm::vec3(x, getHeight(x, z + 1), z + 1), glm::vec3(x + 1, getHeight(x + 1, z), z));
			
			m_terrain.normals.push_back(normal);
			m_terrain.normals.push_back(normal);
			m_terrain.normals.push_back(normal);

			///Texture Coords
			m_terrain.texCoords.push_back(glm::vec2(x, z));
			m_terrain.texCoords.push_back(glm::vec2(x, z + 1));
			m_terrain.texCoords.push_back(glm::vec2(x + 1, z));

			//Second Triangle
			///V1
			m_terrain.positions.push_back(glm::vec3(x + 1, getHeight(x + 1, z), z));
			///V2
			m_terrain.positions.push_back(glm::vec3(x, getHeight(x, z + 1), z + 1));	
			///V3
			m_terrain.positions.push_back(glm::vec3(x + 1, getHeight(x + 1, z+1), z+1));
			
			///Normals
			normal = getNormal(glm::vec3(x + 1, getHeight(x + 1, z), z), glm::vec3(x, getHeight(x, z + 1), z + 1), glm::vec3(x + 1, getHeight(x + 1, z + 1), z + 1));

			m_terrain.normals.push_back(normal);
			m_terrain.normals.push_back(normal);
			m_terrain.normals.push_back(normal);

			///Texture Coords
			m_terrain.texCoords.push_back(glm::vec2(x + 1, z));
			m_terrain.texCoords.push_back(glm::vec2(x, z + 1));
			m_terrain.texCoords.push_back(glm::vec2(x + 1, z + 1));
		}

	
	}


	//Gen Buffers and Bind
	m_num_vertexs = m_terrain.positions.size(); // Count of vertex	
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);
	//Vertexs
	glGenBuffers(3, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_terrain.positions[0]) * m_terrain.positions.size(), &m_terrain.positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//Texture coords
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_terrain.texCoords[0]) * m_terrain.texCoords.size(), &m_terrain.texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//Normal
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_terrain.normals[0]) * m_terrain.normals.size(), &m_terrain.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, 0, 0);
	glBindVertexArray(0);

	//Clear

	std::vector<glm::vec3>().swap(m_terrain.positions);
	std::vector<glm::vec3>().swap(m_terrain.normals);
	std::vector<glm::vec2>().swap(m_terrain.texCoords);

	m_terrain.positions.clear();
	m_terrain.normals.clear();
	m_terrain.texCoords.clear();
}

void Terrain::SetHeight(int height)
{
	m_height = height;
}

void Terrain::Draw()
{

	//Shader need unbind 

	m_texture.Bind();
	m_shader->Bind();
	m_shader->Update(m_transform, *m_camera);
	
	glBindVertexArray(m_vertexArrayObject);        // Bind VBO
	glDrawArrays(GL_TRIANGLES, 0, m_num_vertexs);  // Draw Buffer without index of vertexs											   //Unbind Texture Shaider and Mesh 									  
	glBindVertexArray(0);

	m_shader->UnBind();
	m_texture.Unbind();
	
	
	
}

void Terrain::SetShader(BasicShader & shader)
{
	m_shader = &shader;
}

void Terrain::SetTexture(const std::string & filename)
{
	m_texture.loadFromFile(filename.c_str());
}

float Terrain::GetHeightOnPoint(float x, float z)
{
	float terrainX = x;
	float terrainZ = z;

	int gridSquareSize = 1;

	int gridX = (int)floor(terrainX);
	int gridZ = (int)floor(terrainZ);
	
	
	///If out of range
	if (gridX >= m_image_size_x - 1 || gridZ >= m_image_size_y - 1 || gridX < 0 || gridZ < 0) {
		return 0.f;
	}

	
	//float xCoords = (terrainX - (int)gridSquareSize) / gridSquareSize;
	//float zCoords = (terrainZ - (int)gridSquareSize) / gridSquareSize;
	
	float xCoords = terrainX - (int)terrainX/gridSquareSize;
	float zCoords = terrainZ - (int)terrainZ/gridSquareSize;
	float answer;

	if (xCoords <= (1 - zCoords)) {

		answer = baryyCentric(glm::vec3(0, getHeight(gridX, gridZ), 0),
			glm::vec3(1, getHeight(gridX + 1, gridZ), 0),
			glm::vec3(0, getHeight(gridX, gridZ + 1), 1),
			glm::vec2(xCoords,zCoords));

	}
	else {
		answer = baryyCentric(glm::vec3(1, getHeight(gridX + 1, gridZ), 0),
			glm::vec3(1, getHeight(gridX + 1, gridZ + 1), 1),
			glm::vec3(0, getHeight(gridX, gridZ + 1), 1),
			glm::vec2(xCoords, zCoords));
	}

	return answer;
}

void Terrain::AtachCamera(Camera & camera)
{
	m_camera = &camera;
}

void Terrain::SetRotaited(GLfloat x, GLfloat y, GLfloat z)
{
	m_transform.SetRotate(glm::vec3(x, y, z));
}

glm::vec2 Terrain::GetSize()
{
	return glm::vec2(m_image_size_x, m_image_size_y);
}

Transform Terrain::GetTransfrom()
{
	return m_transform;
}

float Terrain::getHeight(int x, int z)
{
	if (x < 0 || x >= m_image_size_x || z < 0 || z >= m_image_size_y) {
		return 0.0f;
	}

	float height = (m_image.getPixel(x, z).r +m_image.getPixel(x, z).g + m_image.getPixel(x, z).b) /3; // Calculate average in three color 

	return height / m_height;

}

glm::vec3 Terrain::getNormal(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	glm::vec3 p;
	glm::vec3 q;
	glm::vec3 n;

	p = b-a;
	q = c-a;
	n = glm::cross(p, q);
	n = glm::normalize(n);

	return n;
}

float Terrain::baryyCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 poss)
{
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (poss.x - p3.x) + (p3.x - p2.x) * (poss.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (poss.x - p3.x) + (p1.x - p3.x) * (poss.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 *p1.y + l2 *p2.y + l3 *p3.y;
}
