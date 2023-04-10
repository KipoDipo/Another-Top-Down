#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Utils
{
public:
	const static float root2;
	static float getDeltaTime();
	static void resetDeltaTime();

private:
	static float deltaTime;
	static sf::Clock clock;
};

enum class Direction
{
	Up = 1,
	Right,
	Down,
	Left
};

enum class Orientation
{
	None = -1,
	Horizontal,
	Vertical
};