#pragma once
#include <glm/glm.hpp>
#include <Gengine/SpriteBatch.h>
class Bullet
{
private:
	float _speed;
	glm::vec2 _direction;
	glm::vec2 _position;
	int _lifeTime;

public:
	Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime);
	~Bullet();	
	void draw(Gengine::SpriteBatch& spriteBatch);
	//Returns true when out of life
	bool update();
};

