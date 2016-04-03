#include "Display.h"



Display::Display(const std::string & title, float w, float h)
{
	settings.depthBits = 24;
	settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 0;
	window.create(sf::VideoMode(w, h),title, sf::Style::Default, settings);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(90.0f, 1.0f, 1.0f, 2000.0f);
	//glViewport(0, 0, w, h);
	glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glewInit();
}

Display::~Display()
{
}

void Display::Update()
{
 window.display();
 
}

void Display::Clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

sf::RenderWindow *Display::GetHandle()
{
	return &window;
}

sf::RenderWindow & Display::GetReference()
{
	return window;
}
