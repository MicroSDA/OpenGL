#ifndef DEBUG_PANEL_H
#define DEBUG_PANEL_H
#include "ATB\AntTweakBar.h"
#include <SFML\Graphics.hpp>
#include <iostream>
class Debug_Panel
{
public:
	Debug_Panel(float width, float heigth, const std::string &title);
	~Debug_Panel();
	static void Draw();
	void AddVarRW(const std::string &title,ETwType type, void *var, const std::string &def);
	void Event(sf::Event &s_event, sf::RenderWindow &window)const;
	void AddSeparator(const std::string &title, const std::string &def);
private:
	TwBar *bar;
	
};
#endif //  DEBUG_PANEL_H
