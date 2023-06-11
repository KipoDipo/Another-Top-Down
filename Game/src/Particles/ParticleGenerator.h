#pragma once
#include "Particle.h"
#include <Animation/Types/RandomAnimator.h>

class ParticleGenerator 
{
public:
	//static std::vector<Particle> explosion(const SingleAnimator& animator, sf::Vector2f location, float speed, unsigned count, float duration, float randomDurationOffset = 0.5f);
	static std::vector<Particle> explosion(const RandomAnimator& animator, sf::Vector2f location, float speed, unsigned count, float duration, float randomDurationOffset = 0.5f);
};