#include "Enemy.h"
#include "../../../Utilities/Textures.h"

Enemy::Enemy(sf::Vector2f position)
{
	sprite.setTexture(Textures::enemy);
	sprite.setPosition(position);
	collider = sf::FloatRect(position.x, position.y, (float)sprite.getTexture()->getSize().x, (float)sprite.getTexture()->getSize().y);
}

Enemy::Enemy()
{
}

void Enemy::movement()
{
}

void Enemy::update()
{
}
