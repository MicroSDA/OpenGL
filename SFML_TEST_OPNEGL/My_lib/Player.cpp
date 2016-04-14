#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	m_mesh->SetPosition(x, y, z);
}

void Player::Move(GLfloat x, GLfloat y, GLfloat z)
{
	m_mesh->SetPosition(m_mesh->GetPosition().x + x, m_mesh->GetPosition().y + y, m_mesh->GetPosition().z + z);
}

void Player::SetRotaited(GLfloat angleX, GLfloat angleY, GLfloat angleZ)
{
	m_mesh->SetRotation(angleX, angleY, angleZ);
}

void Player::SetScale(GLfloat size)
{
	m_mesh->SetScale(size);
}

void Player::SetModel(Mesh & mesh)
{
	m_mesh = &mesh;
}

void Player::SetSpeed(GLfloat speed)
{
	m_speed = speed;
}

void Player::SetName(const std::string & name)
{
	m_name = name;
}

void Player::AtachCamera(Camera & camera)
{
	m_camera = &camera;
}

void Player::AtachTerrain(Terrain & terrain)
{
	m_terrain = &terrain;
}

glm::vec3 Player::GetPosition()
{
	return glm::vec3(m_mesh->GetPosition().x, m_mesh->GetPosition().y, m_mesh->GetPosition().z);
}

glm::vec3 Player::GetRotaited()
{
	return glm::vec3(m_mesh->GetRotation().x, m_mesh->GetRotation().y, m_mesh->GetRotation().z);
}

GLfloat Player::GetScale()
{
	return m_mesh->GetScale();
}

GLfloat Player::GetSpeed()
{
	return m_speed;
}

std::string Player::GetName()
{
	return m_name;
}

void Player::Draw()
{
	m_mesh->Draw();
}

void Player::Update(float time)
{
	KeyboardUpdate(time);
	Colission(time);
}

void Player::KeyboardUpdate(float time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		Move(m_speed*time, 0, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		Move(-m_speed*time, 0, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		Move(0, 0, -m_speed*time);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		Move(0, 0, m_speed*time);
	}
}

void Player::Colission(float time)
{
	SetPosition(GetPosition().x, m_terrain->GetHeightOnPoint(GetPosition().x, GetPosition().z)+1, GetPosition().z);
	//m_mesh->SetMatix(m_camera->GetViewProjection());
}
