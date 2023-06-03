#pragma once
#include "Particle.h"

class ParticleGenerator 
{
public:
	static std::vector<Particle> explosion(const GenericAnimator& animator, sf::Vector2f location, float speed, unsigned count, float duration, float randomDurationOffset = 0.5f);
};