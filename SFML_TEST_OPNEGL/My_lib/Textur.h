#ifndef TEXTUR_H
#define TEXTUR_H

#include <SFML\Graphics.hpp>
#include <GL\glew.h>
#include <iostream>
class Textur
{
public:
	Textur();
	Textur(const std::string &filename, bool flipVeticaly = false, bool isSkaybox = false);
	void loadFromFile(const std::string &filename, bool flipVeticaly = false, bool isSkaybox = false);
	~Textur();
	void Bind();
	void Unbind();
private:
	sf::Image image;
	GLuint m_texture;
};
#endif // !TEXTUR_H
