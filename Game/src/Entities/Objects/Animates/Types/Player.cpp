#include "Player.h"
#include "Enemy.h"
#include <Animation/Animation.h>
#include <Utilities/All.h>
#include <Entities/Attacks/Types/SlashAttack.h>
#include <Entities/Objects/Inanimates/Inanimate.h>
#include <Level.h>

using namespace sf;

Player::Player()
	: Player(Vector2f(250, 250), 300, AnimateAnimator(), RandomAnimator(), SingleAnimator(), nullptr)
{
}

Player::Player(const Player& other)
	: Animate(other)
{
	copy(other);
}

Player::Player(sf::Vector2f position, float speed, const AnimateAnimator& animation, const RandomAnimator& deathParticlesAnimator, const SingleAnimator& atkAnimations, Level* level)
	: Animate(position, Vector2f(50, 50), animation, deathParticlesAnimator, speed, level)
{
	setSpeed(speed);
	setName("Player");
	setHealth(100);
	setMaxHealth(100);
	attack = std::make_unique<SlashAttack>(6.f, 10.f, 50.f, 100.f, atkAnimations);
}

void Player::update()
{
	AnimateAnimator::State state = AnimateAnimator::State::DOWN;

	movement(Orientation::Vertical);
	for (size_t i = 0; i < getLevel().getSolids().size(); i++)
		resolveCollisions(*getLevel().getSolids()[i], Orientation::Vertical);

	if (getDirection().y > 0)
		state = AnimateAnimator::State::DOWN;
	else if (getDirection().y < 0)
		state = AnimateAnimator::State::UP;

	movement(Orientation::Horizontal);
	for (size_t i = 0; i < getLevel().getSolids().size(); i++)
		resolveCollisions(*getLevel().getSolids()[i], Orientation::Horizontal);

	if (getDirection().x > 0)
		state = AnimateAnimator::State::RIGHT;
	else if (getDirection().x < 0)
		state = AnimateAnimator::State::LEFT;

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
	for (size_t i = 0; i < getLevel().getHostiles().size(); i++)
		checkInterractions(*getLevel().getHostiles()[i]);
}

void Player::movement(Orientation orientation)
{
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

void Player::checkInterractions(Enemy& enemy)
{
	if (attack->getIsActive()
		&& enemy.getIsAlive()
		&& enemy.collides(attack->getCollider()))
	{
		enemy.kill();
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
	attack = player.attack->clone();
}
