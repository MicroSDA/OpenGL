#include "RenderObject.h"

RenderObject::RenderObject()
{
}

RenderObject::~RenderObject()
{
}

void RenderObject::SetMesh(Mesh & mesh)
{
	m_mesh = &mesh;
	m_mesh->SetTransform(m_transform);
}

void RenderObject::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	m_transform.SetPos(glm::vec3(x, y, z));
}

void RenderObject::Draw()
{
	m_mesh->Draw();
}
