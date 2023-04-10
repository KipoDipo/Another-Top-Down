#include "Utils.h"
#include <math.h>

using namespace sf;

const float Utils::root2 = sqrtf(2);

float Utils::getDeltaTime()
{
	return deltaTime;
}

void Utils::resetDeltaTime()
{
	deltaTime = clock.restart().asSeconds();
}

sf::Clock Utils::clock;
float Utils::deltaTime = 0;