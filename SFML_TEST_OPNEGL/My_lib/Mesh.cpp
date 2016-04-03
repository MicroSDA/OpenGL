#include "Mesh.h"



Mesh::Mesh(const std::string & fileName)
{
	InitMesh(OBJModel(fileName).ToIndexedModel());
}

Mesh::~Mesh()
{
	glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::InitMesh(const IndexedModel & model)
{
	m_numIndices = model.indices.size();

	
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.positions[0]) * model.positions.size(), &model.positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.texCoords[0]) * model.texCoords.size(), &model.texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model.indices[0]) * model.indices.size(), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

}

void Mesh::Draw()
{
	texture.Bind();
	shader->Bind();
	shader->Update(transform,*camera);
	//glColor3f(1, 1, 1);
	glBindVertexArray(m_vertexArrayObject);
	glDrawElementsBaseVertex(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0, 0);
	glBindVertexArray(0);
	shader->UnBind();
	texture.Unbind();
	
}

void Mesh::SetShader(Shader & shader)
{
	this->shader = &shader;
}

void Mesh::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	transform.SetPos(glm::vec3(x,y,z));

}

void Mesh::Move(GLfloat x, GLfloat y, GLfloat z)
{
	transform.SetPos(glm::vec3(transform.GetPos().x + x,
		transform.GetPos().y = transform.GetPos().y + y,
		transform.GetPos().z = transform.GetPos().y + z));
}

void Mesh::SetScale(GLfloat x)
{
	
	transform.SetScale(glm::vec3(x, x, x));
}

void Mesh::SetRotaited(GLfloat x, GLfloat y, GLfloat z)
{
	transform.GetRotate().x = x;
	transform.GetRotate().y = y;
	transform.GetRotate().z = z;
}

void Mesh::AtachCamera( Camera & camera)
{
	this->camera = &camera;
}

sf::Vector3f Mesh::GetPosition()
{
	return sf::Vector3f(transform.GetPos().x, transform.GetPos().y, transform.GetPos().z);
}

sf::Vector3f Mesh::GetScale()
{
	return sf::Vector3f(transform.GetScale().x, transform.GetScale().y, transform.GetScale().z);
}

sf::Vector3f Mesh::GetRotaited()
{
	return sf::Vector3f(transform.GetRotate().x, transform.GetRotate().y, transform.GetRotate().z);
}

void Mesh::loadTextureFromFile(const std::string &filename)
{
	texture.loadFromFile(filename);
}

