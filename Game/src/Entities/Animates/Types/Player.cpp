#include "Player.h"
#include "Enemy.h"
#include "../../Inanimates/Solid.h"
#include "../../../Utilities/Textures.h"
#include "../../../Utilities/Utils.h"
#include "../../../Attacks/Types/SlashAttack.h"

using namespace sf;

Player::Player()
	: Player(Vector2f(250, 250), 5)
{
}

Player::Player(Vector2f position, float speed)
	: Animate(position, &Textures::player), speed(speed)
{
	setName("Player");
	slashAttack = new SlashAttack(10, 10, 50, 100);
}

Player::~Player()
{
	delete slashAttack;
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
		checkCollisions(solids[i], Orientation::Horizontal);
	
	movement(Orientation::Vertical);
	for (size_t i = 0; i < solids.size(); i++)
		checkCollisions(solids[i], Orientation::Vertical);


	slashAttack->update(getCenter());
	for (size_t i = 0; i < enemiesAwareOf.size(); i++)
		checkInterractions(enemiesAwareOf[i]);
}

void Player::movement(Orientation orientation)
{
	using namespace sf;
	dir = { 0, 0 };
	if (orientation == Orientation::Horizontal || orientation == Orientation::None)
	{
		if (Keyboard::isKeyPressed(Keyboard::A))
			dir += {-1, 0};
		if (Keyboard::isKeyPressed(Keyboard::D))
			dir += {1, 0};
		if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::S));
			dir /= Utils::root2;
	}
	if (orientation == Orientation::Vertical || orientation == Orientation::None)
	{
		if (Keyboard::isKeyPressed(Keyboard::W))
			dir += {0, -1};
		if (Keyboard::isKeyPressed(Keyboard::S))
			dir += {0, 1};
		if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D));
			dir /= Utils::root2;
	}


	Entity::move(dir * speed);
}

void Player::checkInterractions(Enemy* enemy)
{
	if (slashAttack->getIsAttacking()
		&& enemy->collides(slashAttack->getAttackCollider()))
	{
		enemy->kill();
	}
}

void Player::checkCollisions(Solid* solid, Orientation orientation)
{
	if (collides(*solid))
	{
		if (orientation == Orientation::Horizontal)
		{
			if (dir.x < 0)
				Entity::setPosition(solid->getCollider().left + solid->getCollider().width, collider.top);
			if (dir.x > 0)
				Entity::setPosition(solid->getCollider().left - collider.width, collider.top);
		}
		else if (orientation == Orientation::Vertical)
		{
			if (dir.y < 0)
				Entity::setPosition(collider.left, solid->getCollider().top + solid->getCollider().height);
			if (dir.y > 0)
				Entity::setPosition(collider.left, solid->getCollider().top - collider.height);
		}
	}
}

void Player::draw(RenderTarget& target, RenderStates states) const
{
	Entity::draw(target, states);

	if (slashAttack->getIsAttacking())
		slashAttack->draw(target, states);
}