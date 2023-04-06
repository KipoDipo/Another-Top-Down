#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

class Textures
{
	static sf::Texture load(std::string name);
	struct Pair
	{
		sf::String name;
		sf::Texture texture;

		Pair(sf::String name, sf::Texture texture)
			: name(name), texture(texture)
		{
		}
	};
	static sf::Texture none;
	static std::vector<Pair> pairs;

public:
	
	static sf::Texture* get(sf::String name);
	static void add(sf::String fileName);
};