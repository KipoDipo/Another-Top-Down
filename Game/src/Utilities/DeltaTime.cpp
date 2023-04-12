#include "DeltaTime.h"

float DeltaTime::get()
{
	return deltaTime;
}

void DeltaTime::reset()
{
	deltaTime = clock.restart().asSeconds();
}

sf::Clock DeltaTime::clock;
float DeltaTime::deltaTime = 0;