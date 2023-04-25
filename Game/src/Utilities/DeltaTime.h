#pragma once
#include <SFML/System.hpp>

class DeltaTime
{
public:
	static float get();
	static void reset();
	
private:
	static float deltaTime;
	static sf::Clock clock;
};

