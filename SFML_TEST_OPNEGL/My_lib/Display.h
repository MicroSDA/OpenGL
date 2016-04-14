#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <iostream>
#include <GL\glew.h>
#include <SFML\Graphics.hpp>




class Display
{
public:
	Display(const std::string &title, float w, float h);
	~Display();
	void Update();
	void Clear(GLfloat r = 0.0f, GLfloat g = 0.0f, GLfloat b = 0.0f, GLfloat a = 1.0f);
    sf::RenderWindow *GetHandle();
    sf::RenderWindow &GetReference();
	void Resize();
private:
	sf::RenderWindow window;
	sf::ContextSettings settings;
};
#endif // DISPLAY_H
