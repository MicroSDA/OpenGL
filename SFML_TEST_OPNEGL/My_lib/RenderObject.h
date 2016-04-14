#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "Mesh.h"
#include "Transform.h"

class RenderObject
{
public:
	RenderObject();
	~RenderObject();
	void SetMesh(Mesh &mesh);
	void SetPosition(GLfloat x, GLfloat y, GLfloat z);
	void Draw();
private:
	Mesh *m_mesh;
	Transform m_transform;
};



#endif // RENDEROBJECT_H