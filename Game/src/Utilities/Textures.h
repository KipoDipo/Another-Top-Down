#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

struct Textures
{
	static sf::Texture load(std::string name);

	static sf::Texture player;
	static sf::Texture enemy;
	static sf::Texture defaultSolid;
	static sf::Texture ball;
};