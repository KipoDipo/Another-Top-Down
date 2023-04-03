#pragma once
#include "../Attack.h"

class SlashAttack : public Attack
{
public:
	SlashAttack(int speed, float size, float distance, float range);
	
	// Inherited via Attack
	virtual void update(const sf::Vector2f& origin) override;
	virtual void attackSequence(const sf::Vector2f& origin) override;
};