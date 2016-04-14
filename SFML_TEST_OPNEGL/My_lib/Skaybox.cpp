#include "Skaybox.h"

Skaybox::Skaybox()
{

}

Skaybox::~Skaybox()
{
}

void Skaybox::Draw()
{
	
	SetPos(camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);

	shader->Bind();
	shader->SetMinLightStr(1.0);
	shader->Update(m_transform, *camera);
	m_texture[0].Bind();
	glBindVertexArray(m_vertexArrayObject_f);
	glDrawArrays(GL_QUADS, 0, 4);
	m_texture[0].Unbind();

	m_texture[1].Bind();
	glBindVertexArray(m_vertexArrayObject_b);
	glDrawArrays(GL_QUADS, 0, 4);
	m_texture[1].Unbind();

	m_texture[2].Bind();
	glBindVertexArray(m_vertexArrayObject_l);
	glDrawArrays(GL_QUADS, 0, 4);
	m_texture[2].Unbind();

	m_texture[3].Bind();
	glBindVertexArray(m_vertexArrayObject_r);
	glDrawArrays(GL_QUADS, 0, 4);
	m_texture[3].Unbind();

	m_texture[4].Bind();
	glBindVertexArray(m_vertexArrayObject_bo);
	glDrawArrays(GL_QUADS, 0, 4);
	m_texture[4].Unbind();

	m_texture[5].Bind();
	glBindVertexArray(m_vertexArrayObject_t);
	glDrawArrays(GL_QUADS, 0, 4);
	m_texture[5].Unbind();
	shader->SetMinLightStr(0.2);
	shader->UnBind();
	
}

void Skaybox::SetShader(BasicShader & shader)
{
	this->shader = &shader;
}

void Skaybox::AtachCamera(Camera & camera)
{
	this->camera = &camera;
}

void Skaybox::SetFront(const std::string & fileneme)
{
	m_texture[0].loadFromFile(fileneme, true, true);

}

void Skaybox::SetBack(const std::string & fileneme)
{
	m_texture[1].loadFromFile(fileneme, true, true);
}

void Skaybox::SetLeft(const std::string & fileneme)
{
	m_texture[2].loadFromFile(fileneme, true, true);
}

void Skaybox::SetRight(const std::string & fileneme)
{
	m_texture[3].loadFromFile(fileneme, true, true);
}

void Skaybox::SetBotom(const std::string & fileneme)
{
	m_texture[4].loadFromFile(fileneme, true, true);
}

void Skaybox::SetTop(const std::string & fileneme)
{
	m_texture[5].loadFromFile(fileneme, true, true);
}

void Skaybox::SetSize(float size)
{
	m_size = size;
}

void Skaybox::SetPos(GLfloat x, GLfloat y, GLfloat z)
{
	m_transform.SetPos(glm::vec3(x, y, z));

}

void Skaybox::Init()
{
	m_box[0].positions.push_back(glm::vec3(-m_size, -m_size, -m_size));
	m_box[0].positions.push_back(glm::vec3(m_size, -m_size, -m_size));
	m_box[0].positions.push_back(glm::vec3(m_size, m_size, -m_size));
	m_box[0].positions.push_back(glm::vec3(-m_size, m_size, -m_size));

	m_box[0].texCoords.push_back(glm::vec2(0, 0));
	m_box[0].texCoords.push_back(glm::vec2(1, 0));
	m_box[0].texCoords.push_back(glm::vec2(1, 1));
	m_box[0].texCoords.push_back(glm::vec2(0, 1));



	m_box[1].positions.push_back(glm::vec3(m_size, -m_size, m_size));
	m_box[1].positions.push_back(glm::vec3(-m_size, -m_size, m_size));
	m_box[1].positions.push_back(glm::vec3(-m_size, m_size, m_size));
	m_box[1].positions.push_back(glm::vec3(m_size, m_size, m_size));

	m_box[1].texCoords.push_back(glm::vec2(0, 0));
	m_box[1].texCoords.push_back(glm::vec2(1, 0));
	m_box[1].texCoords.push_back(glm::vec2(1, 1));
	m_box[1].texCoords.push_back(glm::vec2(0, 1));




	m_box[2].positions.push_back(glm::vec3(-m_size, -m_size, m_size));
	m_box[2].positions.push_back(glm::vec3(-m_size, -m_size, -m_size));
	m_box[2].positions.push_back(glm::vec3(-m_size, m_size, -m_size));
	m_box[2].positions.push_back(glm::vec3(-m_size, m_size, m_size));

	m_box[2].texCoords.push_back(glm::vec2(0, 0));
	m_box[2].texCoords.push_back(glm::vec2(1, 0));
	m_box[2].texCoords.push_back(glm::vec2(1, 1));
	m_box[2].texCoords.push_back(glm::vec2(0, 1));



	m_box[3].positions.push_back(glm::vec3(m_size, -m_size, -m_size));
	m_box[3].positions.push_back(glm::vec3(m_size, -m_size, m_size));
	m_box[3].positions.push_back(glm::vec3(m_size, m_size, m_size));
	m_box[3].positions.push_back(glm::vec3(m_size, m_size, -m_size));

	m_box[3].texCoords.push_back(glm::vec2(0, 0));
	m_box[3].texCoords.push_back(glm::vec2(1, 0));
	m_box[3].texCoords.push_back(glm::vec2(1, 1));
	m_box[3].texCoords.push_back(glm::vec2(0, 1));




	m_box[4].positions.push_back(glm::vec3(-m_size, -m_size, m_size));
	m_box[4].positions.push_back(glm::vec3(m_size, -m_size, m_size));
	m_box[4].positions.push_back(glm::vec3(m_size, -m_size, -m_size));
	m_box[4].positions.push_back(glm::vec3(-m_size, -m_size, -m_size));

	m_box[4].texCoords.push_back(glm::vec2(0, 0));
	m_box[4].texCoords.push_back(glm::vec2(1, 0));
	m_box[4].texCoords.push_back(glm::vec2(1, 1));
	m_box[4].texCoords.push_back(glm::vec2(0, 1));



	m_box[5].positions.push_back(glm::vec3(-m_size, m_size, -m_size));
	m_box[5].positions.push_back(glm::vec3(m_size, m_size, -m_size));
	m_box[5].positions.push_back(glm::vec3(m_size, m_size, m_size));
	m_box[5].positions.push_back(glm::vec3(-m_size, m_size, m_size));

	m_box[5].texCoords.push_back(glm::vec2(0, 0));
	m_box[5].texCoords.push_back(glm::vec2(1, 0));
	m_box[5].texCoords.push_back(glm::vec2(1, 1));
	m_box[5].texCoords.push_back(glm::vec2(0, 1));






	glGenVertexArrays(1, &m_vertexArrayObject_f);
	glBindVertexArray(m_vertexArrayObject_f);

	glGenBuffers(2, m_vertexArrayBuffers_f);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers_f[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_box[0].positions[0]) * m_box[0].positions.size(), &m_box[0].positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers_f[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_box[0].texCoords[0]) * m_box[0].texCoords.size(), &m_box[0].texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
////////////////////////////////////////////////////////////////
	glGenVertexArrays(1, &m_vertexArrayObject_b);
	glBindVertexArray(m_vertexArrayObject_b);

	glGenBuffers(2, m_vertexArrayBuffers_b);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers_b[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_box[1].positions[0]) * m_box[1].positions.size(), &m_box[1].positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers_b[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_box[1].texCoords[0]) * m_box[1].texCoords.size(), &m_box[1].texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
//////////////////////////////////////////////////////////////
	glGenVertexArrays(1, &m_vertexArrayObject_l);
	glBindVertexArray(m_vertexArrayObject_l);

	glGenBuffers(2, m_vertexArrayBuffers_l);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers_l[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_box[2].positions[0]) * m_box[2].positions.size(), &m_box[2].positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers_l[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_box[2].texCoords[0]) * m_box[2].texCoords.size(), &m_box[2].texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
//////////////////////////////////////////////////////////////
	glGenVertexArrays(1, &m_vertexArrayObject_r);
	glBindVertexArray(m_vertexArrayObject_r);

	glGenBuffers(2, m_vertexArrayBuffers_r);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers_r[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_box[3].positions[0]) * m_box[3].positions.size(), &m_box[3].positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers_r[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_box[3].texCoords[0]) * m_box[3].texCoords.size(), &m_box[3].texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
	//////////////////////////////////////////////////////////////
	glGenVertexArrays(1, &m_vertexArrayObject_bo);
	glBindVertexArray(m_vertexArrayObject_bo);

	glGenBuffers(2, m_vertexArrayBuffers_bo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers_bo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_box[4].positions[0]) * m_box[4].positions.size(), &m_box[4].positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers_bo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_box[4].texCoords[0]) * m_box[4].texCoords.size(), &m_box[4].texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
	//////////////////////////////////////////////////////////////
	glGenVertexArrays(1, &m_vertexArrayObject_t);
	glBindVertexArray(m_vertexArrayObject_t);

	glGenBuffers(2, m_vertexArrayBuffers_t);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers_t[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_box[5].positions[0]) * m_box[5].positions.size(), &m_box[5].positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers_t[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_box[5].texCoords[0]) * m_box[5].texCoords.size(), &m_box[5].texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
	//////////////////////////////////////////////////////////////

}
