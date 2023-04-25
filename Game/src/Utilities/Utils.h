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

	//const static std::string getPathToAnims();
	
//private:
	const static char* pathToTextures;
	const static char* pathToFonts;

	const static char* greenFlag;
	const static char* yellowFlag;
	const static char* redFlag;
};

enum class Orientation
{
	Horizontal,
	Vertical
};