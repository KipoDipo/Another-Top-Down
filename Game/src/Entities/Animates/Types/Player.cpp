#include "../../../Animation/Animation.h"
#include "../../../Utilities/All.h"
#include "Player.h"
#include "Enemy.h"
#include "../../Inanimates/Types/Solid.h"
#include "../../../Attacks/Types/SlashAttack.h"

using namespace sf;

Player::Player()
	: Player(Vector2f(250, 250), 300)
{
}

Player::Player(const Player& other)
	: Animate(other)
{
	copy(other);
}

Player::Player(Vector2f position, float speed)
	: Player(position, speed, AnimationCollection::getNone(), AnimationCollection::getNone())
{
}

Player::Player(sf::Vector2f position, float speed, const Animator& animations, const Animator& atkAnimations)
	: Animate(position, animations)
{
	setSpeed(speed);
	setName("Player");
	attack = new SlashAttack(6.f, 10, 50, 100, atkAnimations);
}

Player::~Player()
{
	free();
}

void Player::addEnemy(Enemy* enemy)
{
	enemies.push_back(enemy);
}
void Player::addEnemies(std::vector<Enemy>* enemies)
{
	for (size_t i = 0; i < enemies->size(); i++)
		addEnemy(&(*enemies)[i]);
}

void Player::clearEnemies()
{
	enemies.clear();
}

void Player::update()
{
	Entity::update();
	
	movement(Orientation::Horizontal);
	for (size_t i = 0; i < getCollidablesList().size(); i++)
		resolveCollisions(getCollidablesList()[i], Orientation::Horizontal);

	movement(Orientation::Vertical);
	for (size_t i = 0; i < getCollidablesList().size(); i++)
		resolveCollisions(getCollidablesList()[i], Orientation::Vertical);

	if (!attack->getIsActive())
	{
		Vector2f atkDir;
		if (Keyboard::isKeyPressed(Keyboard::Up))
			atkDir = { 0, -1 };
		if (Keyboard::isKeyPressed(Keyboard::Down))
			atkDir = { 0, 1 };
		if (Keyboard::isKeyPressed(Keyboard::Left))
			atkDir = { -1, 0 };
		if (Keyboard::isKeyPressed(Keyboard::Right))
			atkDir = { 1, 0 };

		if (atkDir != Vector2f(0, 0))
			attack->start(atkDir);
	}

	attack->update(getCenter());
	for (size_t i = 0; i < enemies.size(); i++)
		checkInterractions(enemies[i]);
}

void Player::movement(Orientation orientation)
{
	using namespace sf;
	setDirection({ 0, 0 });
	Vector2f direction = getDirection();
	switch (orientation)
	{
	case Orientation::Horizontal:
		if (Keyboard::isKeyPressed(Keyboard::A))
			direction += Vector2f(-1, 0);
		if (Keyboard::isKeyPressed(Keyboard::D))
			direction += Vector2f(1, 0);
		if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::S))
			direction /= Utils::root2;
		break;
	case Orientation::Vertical:
		if (Keyboard::isKeyPressed(Keyboard::W))
			direction += Vector2f(0, -1);
		if (Keyboard::isKeyPressed(Keyboard::S))
			direction += Vector2f(0, 1);
		if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D))
			direction /= Utils::root2;
		break;
	}

	setDirection(direction);
	Entity::move(getDirection() * getSpeed() * DeltaTime::get());
}

void Player::checkInterractions(Enemy* enemy)
{
	if (attack->getIsActive()
		&& enemy->collides(attack->getCollider()))
	{
		enemy->kill();
	}
}

void Player::draw(RenderTarget& target, RenderStates states) const
{
	Entity::draw(target, states);

	if (attack->getIsActive())
		attack->draw(target, states);
}

void Player::copy(const Player& player)
{
	enemies = player.enemies;
	attack = player.attack->clone();
}

void Player::free()
{
	delete attack;
}
