#include "Bullet.h"
#include <Gengine/ResourceManager.h>


Bullet::Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime)
{
	_position = pos;
	_direction = dir;
	_speed = speed;
	_lifeTime = lifeTime;
}


Bullet::~Bullet()
{
}

void Bullet::draw(Gengine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0, 0.0, 1.0, 1.0);
	static Gengine::GLTexture texture = Gengine::ResourceManager::getTexture("C:/Users/josep_000/Documents/Visual Studio 2017/Projects/openGlLaeranWithSDL/Textures/PlanetProctorSpeedNumber.png");
	Gengine::Colour color;
	color.a = 255; color.r = 255; color.g = 255; color.b = 255;
	glm::vec4 posNsize = glm::vec4(_position.x, _position.y, 30, 30);
	spriteBatch.draw(posNsize, uv, texture.id, 0.0f, color);
}
bool Bullet::update()
{
	_position += _direction * _speed;
	_lifeTime--;
	if (_lifeTime == 0)
		return true;
	return false;
}
