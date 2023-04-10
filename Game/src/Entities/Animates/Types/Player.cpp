#include "Player.h"
#include "Enemy.h"
#include "../../Inanimates/Types/Solid.h"
#include "../../../Utilities/Textures.h"
#include "../../../Utilities/Utils.h"
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


	attack->update(getCenter());
	for (size_t i = 0; i < enemiesAwareOf.size(); i++)
		checkInterractions(enemiesAwareOf[i]);
}

void Player::movement(Orientation orientation)
{
	using namespace sf;
	setDirection({ 0, 0 });
	if (orientation == Orientation::Horizontal || orientation == Orientation::None)
	{
		if (Keyboard::isKeyPressed(Keyboard::A))
			setDirection(getDirection() + Vector2f(-1, 0));
		if (Keyboard::isKeyPressed(Keyboard::D))
			setDirection(getDirection() + Vector2f(1, 0));
		if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::S))
			setDirection(getDirection() / Utils::root2);
	}
	if (orientation == Orientation::Vertical || orientation == Orientation::None)
	{
		if (Keyboard::isKeyPressed(Keyboard::W))
			setDirection(getDirection() + Vector2f(0, -1));
		if (Keyboard::isKeyPressed(Keyboard::S))
			setDirection(getDirection() + Vector2f(0, 1));
		if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D))
			setDirection(getDirection() / Utils::root2);
	}


	Entity::move(getDirection() * getSpeed() * Utils::getDeltaTime());
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