#pragma once
#include "../Attack.h"

class SlashAttack : public Attack
{
public:
	SlashAttack(int speed, float size, float distance, float range);
	
	// Inherited via Attack
	virtual void update(const sf::FloatRect& entityCollider) override;
	virtual void attackSequence(const sf::FloatRect& entityCollider) override;
};