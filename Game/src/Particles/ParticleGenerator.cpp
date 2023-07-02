#include "ParticleGenerator.h"
#include <Utilities/Random.h>

//std::vector<Particle> ParticleGenerator::explosion(const SingleAnimator& animator, sf::Vector2f location, float speed, unsigned count, float duration, float randomDurationOffset)
//{
//	return explosion(RandomAnimator({ animator }), location, speed, count, duration, randomDurationOffset);
//}

std::vector<Particle> ParticleGenerator::explosion(const RandomAnimator& animator, sf::Vector2f location, float speed, unsigned count, float duration, float randomDurationOffset)
{
	std::vector<Particle> vec;
	vec.reserve(count);

	for (unsigned i = 0; i < count; i++)
	{
		// 628 === 6.28 * 100 === 2*pi*100
		float randAngle = Random::next(628) / 100.f;
		sf::Vector2f direction = sf::Vector2f(cosf(randAngle), sinf(randAngle));

		float spdOffset = ((Random::next(75) / 100.f) * speed);
		float durOffset = (Random::next((int)(randomDurationOffset * 100)) / 100.f) * duration;
		Particle particle(SingleAnimator(animator.roll()), location, direction, speed - spdOffset, duration - durOffset);
		vec.push_back(particle);
	}
	return vec;
}
