#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

struct Utils
{
	const static float root2;
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