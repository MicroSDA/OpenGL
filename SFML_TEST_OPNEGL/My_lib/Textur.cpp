#include "Textur.h"



Textur::Textur()
{
}

void Textur::loadFromFile(const std::string & filename)
{
	image.loadFromFile(filename.c_str());
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	
}


Textur::~Textur()
{
	glDeleteTextures(1, &m_texture);
}

void Textur::Bind()
{
	
	glBindTexture(GL_TEXTURE_2D, m_texture);
	
}

void Textur::Unbind()
{
	
	glBindTexture(GL_TEXTURE_2D, 0);
}
