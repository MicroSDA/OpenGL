#ifndef PLAYER_H
#define PALYER_H

#include <SFML\Graphics.hpp>
#include <GL\glew.h>
#include <iostream>
#include <string>
#include <vector>

#include "Mesh.h"
#include "Terrain.h"
class Player {

public:
	Player();
	~Player();
	void SetPosition(GLfloat x, GLfloat y, GLfloat z);
	void Move(GLfloat x, GLfloat y, GLfloat z);
	void SetRotaited(GLfloat angleX, GLfloat angleY, GLfloat angleZ);
	void SetScale(GLfloat size);
	void SetModel(Mesh &mesh);
	void SetSpeed(GLfloat speed);
	void SetName(const std::string &name);
	void AtachCamera(Camera &camera);
	void AtachTerrain(Terrain &terrain);
	glm::vec3 GetPosition();
	glm::vec3 GetRotaited();
	GLfloat GetScale();
	GLfloat GetSpeed();
	std::string GetName();

	void Draw();
	void Update(float time);
private:
	Transform m_transform;
	Mesh *m_mesh = NULL;
	Camera *m_camera = NULL;
	Terrain *m_terrain = NULL;
	GLfloat m_speed = 0.1f;
	std::string m_name;

	void KeyboardUpdate(float time);
	void Colission(float time);
}; 

#endif // PLAYER_H