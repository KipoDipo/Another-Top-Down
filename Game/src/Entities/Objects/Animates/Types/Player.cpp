#include <Animation/Animation.h>
#include <Utilities/All.h>
#include "Player.h"
#include "Enemy.h"
#include <Entities/Attacks/Types/SlashAttack.h>
#include <Level.h>

using namespace sf;

Player::Player()
	: Player(Vector2f(250, 250), 300, AnimateAnimator(), GenericAnimator(), GenericAnimator(), nullptr)
{
}

Player::Player(const Player& other)
	: Animate(other)
{
	copy(other);
}

Player::Player(sf::Vector2f position, float speed, const AnimateAnimator& animation, const GenericAnimator& deathParticlesAnimator, const GenericAnimator& atkAnimations, Level* level)
	: Animate(position, Vector2f(50,50), animation, deathParticlesAnimator, speed, level)
{
	setSpeed(speed);
	setName("Player");
	attack = std::make_unique<SlashAttack>(6.f, 10.f, 50.f, 100.f, atkAnimations);
}

void Player::addEnemy(std::shared_ptr<Enemy> enemy)
{
	enemies.push_back(enemy);
}

void Player::clearEnemies()
{
	enemies.clear();
}

void Player::update()
{
	AnimateAnimator::State state = AnimateAnimator::DOWN;

	movement(Orientation::Vertical);
	for (size_t i = 0; i < getCollidablesList().size(); i++)
		resolveCollisions(getCollidablesList()[i].get(), Orientation::Vertical);
	
	if (getDirection().y > 0)
		state = AnimateAnimator::DOWN;
	if (getDirection().y < 0)
		state = AnimateAnimator::UP;

	movement(Orientation::Horizontal);
	for (size_t i = 0; i < getCollidablesList().size(); i++)
		resolveCollisions(getCollidablesList()[i].get(), Orientation::Horizontal);

	if (getDirection().x > 0)
		state = AnimateAnimator::RIGHT;
	if (getDirection().x < 0)
		state = AnimateAnimator::LEFT;

	Animate::setAnimation(state);
	Animate::update();

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
	Animate::move(getDirection() * getSpeed() * DeltaTime::get());
}

void Player::checkInterractions(std::shared_ptr<Enemy> enemy)
{
	if (attack->getIsActive()
		&& enemy->collides(attack->getCollider()))
	{
		enemy->kill();
	}
}

void Player::draw(RenderTarget& target, RenderStates states) const
{
	Animate::draw(target, states);

	if (attack->getIsActive())
		attack->draw(target, states);
}

void Player::copy(const Player& player)
{
	enemies = player.enemies;
	attack = player.attack->clone();
}
