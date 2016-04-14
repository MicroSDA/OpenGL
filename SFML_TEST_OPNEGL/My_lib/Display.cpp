#include "Display.h"



Display::Display(const std::string & title, float w, float h)
{
	settings.depthBits = 24;
	//settings.stencilBits = 8;
   // settings.antialiasingLevel = 4;
	//settings.majorVersion = 3;
	//settings.minorVersion = 0;
	window.create(sf::VideoMode(w, h),title, sf::Style::Default, settings);
	//glShadeModel(GL_SMOOTH);    // Включить сглаживание
	glClearDepth(1.0f);        // Установка буфера глубины
	glEnable(GL_DEPTH_TEST);   // Включить буфер глубины
	//glDepthFunc(GL_LEQUAL);    // Тип теста глубины
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Улучшенные вычисления перспективы
	glDepthMask(GL_TRUE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(90.0f, 1.0f, 1.0f, 2000.0f);
	//glViewport(0, 0, w, h);
	glFrontFace(GL_BACK);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

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

void Display::Resize()
{
	glViewport(0, 0, window.getSize().x, window.getSize().y);
	glLoadIdentity();
}
