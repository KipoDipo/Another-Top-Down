#include "Player.h"
#include "Enemy.h"
#include "../../Inanimates/Solid.h"
#include "../../../Utilities/Textures.h"
#include "../../../Utilities/Utils.h"
#include "../../../Attacks/Types/SlashAttack.h"

Player::Player()
	: Player(sf::Vector2f(250, 250), 5)
{
}

Player::Player(sf::Vector2f position, float speed)
	: speed(speed)
{
	setName("Player");
	slashAttack = new SlashAttack(10, 10, 50, 100);
	sprite.setTexture(Textures::player);
	sprite.setPosition(position);
	collider = sf::FloatRect(position.x, position.y, (float)sprite.getTexture()->getSize().x, (float)sprite.getTexture()->getSize().y);
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


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Entity::draw(target, states);
	
	if (slashAttack->getIsAttacking())
		slashAttack->draw(target, states);
}

void Player::movement()
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

void Player::update()
{
	movement();
	slashAttack->update(collider);
	for (size_t i = 0; i < enemiesAwareOf.size(); i++)
		checkInterractions(enemiesAwareOf[i]);
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
