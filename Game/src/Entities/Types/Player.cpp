#include "Player.h"
#include "Enemy.h"
#include "../../Utilities/Textures.h"
#include "../../Utilities/Utils.h"

Player::Player()
	: Player(sf::Vector2f(250, 250), 5)
{
}

Player::Player(sf::Vector2f position, float speed)
	: slashAttack(10, 10, 50, 100), speed(speed)
{
	sprite.setTexture(Textures::player);
	sprite.setPosition(position);
	collider = sf::FloatRect(position.x, position.y, (float)sprite.getTexture()->getSize().x, (float)sprite.getTexture()->getSize().y);
}

void Player::update(Enemy& enemy)
{
	move();
	slashAttack.update(collider);
	checkInterractions(enemy);
}

void Player::update(std::vector<Enemy>& enemies)
{
	move();
	slashAttack.update(collider);
	for (size_t i = 0; i < enemies.size(); i++)
		checkInterractions(enemies[i]);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Entity::draw(target, states);
	
	if (slashAttack.getIsAttacking())
		slashAttack.draw(target, states);
}

void Player::move()
{
	using namespace sf;
	sf::Vector2f dir;

	if (Keyboard::isKeyPressed(Keyboard::W))
		dir += {0, -1};
	if (Keyboard::isKeyPressed(Keyboard::S))
		dir += {0, 1};
	if (Keyboard::isKeyPressed(Keyboard::A))
		dir += {-1, 0};
	if (Keyboard::isKeyPressed(Keyboard::D))
		dir += {1, 0};

	if (dir != sf::Vector2f(0, 0))
		dir /= Utils::root2;

	Entity::move(dir * speed);
}

void Player::checkInterractions(Enemy& enemy)
{
	if (slashAttack.getIsAttacking() 
		&& slashAttack.getAttackCollider().intersects(enemy.getCollider()))
	{
		printf("hit\n");
		enemy.kill();
	}
}
