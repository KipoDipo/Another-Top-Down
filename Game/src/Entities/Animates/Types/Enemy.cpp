#include "Enemy.h"
#include "../../../Utilities/Textures.h"

Enemy::Enemy()
	: Enemy(sf::Vector2f(0,0))
{
}

Enemy::Enemy(sf::Vector2f position)
	: Animate(position, &Textures::enemy)
{
}

void Enemy::movement(Orientation orientation)
{
}

void Enemy::update()
{
}
