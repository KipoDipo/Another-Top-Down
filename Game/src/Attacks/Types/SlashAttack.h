#pragma once
#include "../Attack.h"

class SlashAttack : public Attack
{
public:
	SlashAttack(float speed, float size, float distance, float range);
	
	// Inherited via Attack
	virtual void update(const sf::Vector2f& origin) override;
};