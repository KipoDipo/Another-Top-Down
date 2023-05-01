#pragma once
#include "../Attack.h"

class SlashAttack : public Attack
{
public:
	SlashAttack(float speed, float size, float distance, float range, const Animatorv2& animations);
	
	// Inherited via Attack
	void update(const sf::Vector2f& origin) override;
	SlashAttack* clone() const override;
};