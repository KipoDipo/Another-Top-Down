#include "ParticleGenerator.h"
#include <Utilities/Utils.h>

std::vector<Particle> ParticleGenerator::explosion(const GenericAnimator& animator, sf::Vector2f location, float speed, unsigned count, float duration, float randomDurationOffset)
{
	std::vector<Particle> vec;
	vec.reserve(count);

	for (unsigned i = 0; i < count; i++)
	{
		// 628 === 6.28 * 100 === 2*pi*100
		float randAngle = Utils::random(628) / 100.f;
		sf::Vector2f direction = sf::Vector2f(cosf(randAngle), sinf(randAngle));

		float spdOffset = ((Utils::random(75) / 100.f) * speed);
		float durOffset = (Utils::random((int)(randomDurationOffset * 100)) / 100.f) * duration;
		Particle particle(animator, location, direction, speed - spdOffset, duration - durOffset);
		vec.push_back(particle);
	}
	return vec;
}