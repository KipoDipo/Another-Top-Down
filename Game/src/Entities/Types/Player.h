#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../Entity.h"
#include "../../Attacks/Types/SlashAttack.h"

class Enemy;

class Player : public Entity
{
public:
	Player();
	Player(sf::Vector2f position, float speed);
	void update(Enemy& enemy);
	void update(std::vector<Enemy>& enemies);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	SlashAttack slashAttack;
	
	void move();
	void checkInterractions(Enemy& enemy);
	
	float speed;
};