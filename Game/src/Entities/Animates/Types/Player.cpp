#include "../../../Utilities/All.h"
#include "Player.h"
#include "Enemy.h"
#include "../../Inanimates/Types/Solid.h"
#include "../../../Attacks/Types/SlashAttack.h"

using namespace sf;

Player::Player()
	: Player(Vector2f(250, 250), 5)
{
}

Player::Player(Vector2f position, float speed)
	: Animate(position, Textures::get("player"))
{
	setSpeed(speed);
	setName("Player");
	attack = new SlashAttack(6.f, 10, 50, 100);
}

Player::~Player()
{
	delete attack;
}

void Player::addEnemy(Enemy* enemy)
{
	enemiesAwareOf.push_back(enemy);
}
void Player::addEnemies(std::vector<Enemy>* enemies)
{
	for (size_t i = 0; i < enemies->size(); i++)
		addEnemy(&(*enemies)[i]);
}

void Player::addSolid(Solid* solid)
{
	solids.push_back(solid);
}
void Player::addSolids(std::vector<Solid>* solids)
{
	for (size_t i = 0; i < solids->size(); i++)
		addSolid(&(*solids)[i]);
}

void Player::update()
{
	movement(Orientation::Horizontal);
	for (size_t i = 0; i < solids.size(); i++)
		resolveCollisions(solids[i], Orientation::Horizontal);

	movement(Orientation::Vertical);
	for (size_t i = 0; i < solids.size(); i++)
		resolveCollisions(solids[i], Orientation::Vertical);

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
	for (size_t i = 0; i < enemiesAwareOf.size(); i++)
		checkInterractions(enemiesAwareOf[i]);
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