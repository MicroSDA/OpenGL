#include "Debug_Panel.h"


Debug_Panel::Debug_Panel(float width, float heigth, const std::string &title)
{
	TwInit(TW_OPENGL, NULL);
	TwWindowSize(width, heigth);
	bar = TwNewBar(title.c_str());
	TwDefine(" GLOBAL help='Information.\n' "); // Message added to the help bar.
}

Debug_Panel::~Debug_Panel()
{
}

void  Debug_Panel::Draw()
{
	TwDraw();
}

void Debug_Panel::AddVarRW(const std::string & title, ETwType type, void *var, const std::string & def)
{
	TwAddVarRW(bar, title.c_str(), type, var, def.c_str());
}

void Debug_Panel::Event(sf::Event & s_event, sf::RenderWindow &window) const
{
	TwEventSFML(&s_event,3, 0); // Assume SFML version 1.6 here
	TwMouseMotion(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

	if (s_event.type == sf::Event::MouseButtonPressed) {
		if (s_event.mouseButton.button == sf::Mouse::Left) {
			TwMouseButton(TW_MOUSE_PRESSED, TW_MOUSE_LEFT);
		}

		if (s_event.mouseButton.button == sf::Mouse::Right) {
			TwMouseButton(TW_MOUSE_PRESSED, TW_MOUSE_RIGHT);
		}
	}

	if (s_event.type == sf::Event::MouseButtonReleased) {
		if (s_event.key.code == sf::Mouse::Left) {
			TwMouseButton(TW_MOUSE_RELEASED, TW_MOUSE_LEFT);
		}

		if (s_event.key.code == sf::Mouse::Right) {
			TwMouseButton(TW_MOUSE_RELEASED, TW_MOUSE_RIGHT);
		}
	}
}

void Debug_Panel::AddSeparator(const std::string & title, const std::string & def)
{
	TwAddSeparator(bar, title.c_str(), def.c_str());
}
