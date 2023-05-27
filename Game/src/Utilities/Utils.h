#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Utils
{

public:
	const static float root2;

	static sf::Vector2f normalized(sf::Vector2f vector);
	static sf::Vector2f roundedBySubdivions(sf::Vector2f vector, int subDivisions);
	static void printVector(sf::Vector2f vector, std::string caption = "Vector2f");
	static int random(int min, int max);
	static int random(int max);
};

enum class Orientation
{
	Horizontal,
	Vertical
};