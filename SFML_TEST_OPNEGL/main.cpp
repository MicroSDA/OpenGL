#include <iostream>
#include <ATB\AntTweakBar.h>
#include "My_lib\Display.h"
#include "My_lib\Debug_Panel.h"
#include "My_lib\Skaybox.h"
#include "My_lib\Terrain.h"
#include "My_lib\Shader.h"
#include "My_lib\BasicShader.h"
#include "My_lib\Player.h"
#include "My_lib\Mesh.h"
#include <Windows.h>
#include <vld.h>

#include "My_lib\RenderObject.h"
//#ifdef main
 //  #undef main
//#endif // main


int main() {
	

		
	Display window("Window", 1500, 800);
	Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), 70.0f, (float)window.GetReference().getSize().x / (float)window.GetReference().getSize().y, 0.1f, 1800.0f);
	
	
	BasicShader terrain_shader;
	terrain_shader.loadFromFile("./res/shader/BasicShader");
	BasicShader skaybox_shader;
	skaybox_shader.loadFromFile("./res/shader/BasicShader");
	BasicShader grass_shader;
	grass_shader.loadFromFile("./res/shader/BasicShader");
	grass_shader.SetMinLightStr(0.7);
	grass_shader.SetMaxLightStr(1.0);
	BasicShader model_shader; 
	model_shader.loadFromFile("./res/shader/BasicShader");


	Skaybox skaybox;
	skaybox.SetShader(skaybox_shader);
	skaybox.AtachCamera(camera);
	skaybox.SetBack("./res/skybox2/skybox_back.bmp");
	skaybox.SetFront("./res/skybox2/skybox_front.bmp");
	skaybox.SetLeft("./res/skybox2/skybox_left.bmp");
	skaybox.SetRight("./res/skybox2/skybox_right.bmp");
	skaybox.SetBotom("./res/skybox2/skybox_bottom.bmp");
	skaybox.SetTop("./res/skybox2/skybox_top.bmp");
	skaybox.SetSize(1000);
	skaybox.Init();

	Terrain terrain;
	terrain.LoadFromFile("./res/height_maps/TestMap.png");
	terrain.SetTexture("./res/texture/grass_m.jpg");
	terrain.SetShader(terrain_shader);
	terrain.AtachCamera(camera);
	terrain.SetHeight(25);
	terrain.Init();

	
	Mesh Grass[100];
	Mesh Tree[25];
	for (int i = 0; i < 100; i++) {

		Grass[i].LoadMesh("./res/models/Grass pack/Grass_02.obj");
		Grass[i].SetShader(grass_shader);
		Grass[i].AtachCamera(camera);
		int x = 0 + rand() % (int)terrain.GetSize().x ;
		int y = 0 + rand() % (int)terrain.GetSize().y ;

		Grass[i].SetPosition(x,terrain.GetHeightOnPoint(x,y)-0.4,y);
	}

	for (int i = 0; i < 25; i++) {
		Tree[i].LoadMesh("./res/models/Tree/Tree.obj");
		Tree[i].SetShader(model_shader);
		Tree[i].AtachCamera(camera);
		int x = 0 + rand() % (int)terrain.GetSize().x;
		int y = 0 + rand() % (int)terrain.GetSize().y;

		Tree[i].SetPosition(x, terrain.GetHeightOnPoint(x, y) - 0.4, y);
	}
	
	sf::Clock clock;
	float speed;

	camera.setPosition(glm::vec3(terrain.GetSize().x / 2, 8, terrain.GetSize().y / 2-3));

	

	while (window.GetHandle()->isOpen())
	{
		speed = clock.getElapsedTime().asSeconds()*70;
		clock.restart();
		sf::Event event;
		while (window.GetHandle()->pollEvent(event))
		{
			//debug.Event(event, window.GetReference());
			if (event.type == sf::Event::Closed) {
				window.GetHandle()->close();
				return EXIT_SUCCESS;		
		    }

			if (event.type == sf::Event::Resized) {
				camera.forResize((float)window.GetReference().getSize().x / (float)window.GetReference().getSize().y);
				window.Resize();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.GetHandle()->close();
				return EXIT_SUCCESS;
				
			}

		}

		if (window.GetReference().hasFocus() && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
			camera.Update(window.GetReference(),speed);
		}
		else {
			ShowCursor(true);
		}
		
	//	camera.setPosition(glm::vec3(camera.getPosition().x, terrain.GetHeightOnPoint(camera.getPosition().x, camera.getPosition().z)+3,camera.getPosition().z));
		window.Clear();
		skaybox.Draw();
	
		terrain.Draw();
		for (int i = 0; i < 100 ; i++) {
			Grass[i].Draw();
		}

		for (int i = 0; i < 25; i++) {
			Tree[i].Draw();
		}
		window.Update();	
	}

	return EXIT_SUCCESS;
}