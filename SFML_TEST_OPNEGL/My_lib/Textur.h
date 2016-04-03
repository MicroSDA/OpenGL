#ifndef TEXTUR_H
#define TEXTUR_H

#include <SFML\Graphics.hpp>
#include <GL\glew.h>
class Textur
{
public:
	Textur();
	void loadFromFile(const std::string &filename);
	~Textur();
	void Bind();
	void Unbind();
private:
	sf::Image image;
	GLuint m_texture;
};
#endif // !TEXTUR_H
