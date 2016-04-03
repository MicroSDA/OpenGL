#include <iostream>
//#include <SDL\SDL.h>
#include <ATB\AntTweakBar.h>
#include "My_lib\Mesh.h"
#include "My_lib\shader.h"
#include "My_lib\Display.h"
#include "My_lib\Debug_Panel.h"
#include "My_lib\Landscape.h"
#include <Windows.h>
//#ifdef main
 //  #undef main
//#endif // main



int main() {
	


	

	GLfloat color[] = { 0.48f, 0.6f, 1.0f};
	GLfloat pos[] = { 0.0f, 1.0f, 0.0f };
	GLfloat rot[] = { 0.0f, 0.0f, 0.0f };
	GLfloat scale = 1.0f;
	Display window("Window", 1500, 800);

	//Mesh mesh("./res/models/moun_more.obj");
	//Mesh mesh2("./res/models/Air.obj");
	Shader shaider("./res/shader/basicShader");
	Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), 70.0f, (float)window.GetReference().getSize().x / (float)window.GetReference().getSize().y, 0.1f, 600.0f);
	Debug_Panel debug(window.GetHandle()->getSize().x, window.GetHandle()->getSize().y, "DEBUG");
	sf::Image texture;
	//mesh.SetShader(shaider);
	//mesh.AtachCamera(camera);
	//mesh.loadTextureFromFile("./res/models/texture/texture.jpg");
	//mesh2.SetShader(shaider);
	//mesh2.AtachCamera(camera);
	//mesh2.loadTextureFromFile("./res/models/texture/ground_grass.jpg");
	
	debug.AddVarRW("Background color", TW_TYPE_COLOR3F, &color, " opened=true help='Background color'");
	debug.AddSeparator("D0", "label='------------'");
	debug.AddVarRW("Pos x", TW_TYPE_FLOAT, &pos[0], " label=' Pos x' step=0.01");
	debug.AddVarRW("Pos y", TW_TYPE_FLOAT, &pos[1], " label=' Pos y' step=0.01");
	debug.AddVarRW("Pos z", TW_TYPE_FLOAT, &pos[2], " label=' Pos z' step=0.01");
	debug.AddSeparator("D1", "label='------------'");
	debug.AddVarRW("Rotation x", TW_TYPE_FLOAT, &rot[0], " label=' Rotation  x'");
	debug.AddVarRW("Rotation y", TW_TYPE_FLOAT, &rot[1], " label=' Rotation  y'");
	debug.AddVarRW("Rotation z", TW_TYPE_FLOAT, &rot[2], " label=' Rotation  z'");
	debug.AddSeparator("D2", "label='------------'");
	debug.AddVarRW("Scale ", TW_TYPE_FLOAT, &scale, " label=' Scale' step=0.01 min=0.01");

	Landscape landscape;
	landscape.LoadHeightMap("./res/models/texture/heightmap_smoth.png");
	landscape.AtachCamera(camera);
	landscape.SetShader(shaider);
	landscape.loadTextureFromFile("./res/models/texture/grass_20.jpg");

	//landscape.SetScale(1.0f);
	landscape.SetRotaited(0, 0, 180);

	ShowCursor(false);

	POINT mousexy;
	float angleX=0, angleY=0;
	
	SetCursorPos(window.GetReference().getPosition().x + 750, window.GetReference().getPosition().y + 400);

	sf::Clock clock;
	float speed;
	while (window.GetHandle()->isOpen())
	{
		speed = clock.getElapsedTime().asSeconds()*55;
		clock.restart();
		std::cout << speed<<std::endl;
		sf::Event event;
		while (window.GetHandle()->pollEvent(event))
		{
			debug.Event(event, window.GetReference());
			if (event.type == sf::Event::Closed) {
				window.GetHandle()->close();
				return EXIT_SUCCESS;		
		    }

			if (event.type == sf::Event::Resized) {
				camera.forResize((float)window.GetReference().getSize().x / (float)window.GetReference().getSize().y);
				glViewport(0, 0, window.GetReference().getSize().x, window.GetReference().getSize().y);
				glLoadIdentity();
			}


		}

		

		if (window.GetReference().hasFocus()) {
			ShowCursor(false);

			GetCursorPos(&mousexy);
			int xt = window.GetReference().getPosition().x + window.GetReference().getSize().x / 2;
			int yt = window.GetReference().getPosition().y + window.GetReference().getSize().y / 2;

			angleX += (xt - mousexy.x) / 1; //4 Ч чувствительность 
			angleY += (yt - mousexy.y) / 1;

			if (angleY<-89.0) { angleY = -89.0; }
			if (angleY>89.0) { angleY = 89.0; }

			SetCursorPos(xt, yt);
		}
		else {
			ShowCursor(true);
		}
		

		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.GetHandle()->close();
			return EXIT_SUCCESS;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			camera.MoveForward(0.1*speed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			camera.MoveForward(-0.1*speed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			camera.MoveLeft(0.1*speed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			camera.MoveRight(0.1*speed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			camera.RotateY(0.1*speed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			camera.RotateY(-0.1*speed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			camera.Pitch(-0.1*speed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			camera.Pitch(0.1*speed);
		}

	
		camera.Pitch(angleY/10);
		camera.RotateY(angleX/10);
		angleY = 0.0;
		angleX = 0.0;
		window.Clear(color[0],color[1],color[2]);	

	


		//mesh.Draw();
		//mesh2.Draw();
		landscape.Draw();
		Debug_Panel::Draw();
		window.Update();	

		//mesh2.SetPosition(pos[0], pos[1], pos[2]);
		//mesh2.SetRotaited(rot[0], rot[1], rot[2]);
	//	mesh.SetScale(scale);

		
	}

	

	return EXIT_SUCCESS;
}