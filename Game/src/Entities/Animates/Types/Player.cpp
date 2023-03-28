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
	movement();
	slashAttack->update(collider);
	for (size_t i = 0; i < enemiesAwareOf.size(); i++)
		checkInterractions(enemiesAwareOf[i]);
	for (size_t i = 0; i < solids.size(); i++)
		checkCollisions(solids[i]);
}

void Player::movement()
{
	using namespace sf;
	Vector2f dir;

	if (Keyboard::isKeyPressed(Keyboard::W))
		dir += {0, -1};
	if (Keyboard::isKeyPressed(Keyboard::S))
		dir += {0, 1};
	if (Keyboard::isKeyPressed(Keyboard::A))
		dir += {-1, 0};
	if (Keyboard::isKeyPressed(Keyboard::D))
		dir += {1, 0};

	if (dir != Vector2f(0, 0))
		dir /= Utils::root2;

	Entity::move(dir * speed);
}

void Player::checkInterractions(Enemy* enemy)
{
	if (slashAttack->getIsAttacking() 
		&& slashAttack->getAttackCollider().intersects(enemy->getCollider()))
	{
		printf("hit\n");
		enemy->kill();
	}
}

void Player::checkCollisions(Solid* solid)
{
	if (collider.intersects(solid->getCollider()))
	{
		Vector2f overlap(
			collider.left + collider.width - solid->getCollider().left - solid->getCollider().width ,
			collider.top  + collider.height - solid->getCollider().top - solid->getCollider().height 
		);
		Vector2f mtv(0, 0); // minimum translation vector
		if (fabsf(overlap.x) > fabsf(overlap.y))
		{
			if (overlap.x > 0)
				mtv.x = collider.width - overlap.x;
			else
				mtv.x = -collider.width - overlap.x;
		}
		else
		{
			if (overlap.y > 0)
				mtv.y = collider.height - overlap.y;
			else
				mtv.y = -collider.height - overlap.y;
		}
		move(mtv);
	}
}

void Player::draw(RenderTarget& target, RenderStates states) const
{
	Entity::draw(target, states);
	
	if (slashAttack->getIsAttacking())
		slashAttack->draw(target, states);
}