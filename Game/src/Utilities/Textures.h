#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Textures
{
	static sf::Texture load(std::string name);
	struct Pair
	{
		int id;
		sf::String name;
		sf::Texture texture;

		Pair(sf::String name, sf::Texture texture, int id = -1)
			: name(name), texture(texture), id(id)
		{
		}
	};
	static sf::Texture noneTexture;
	static sf::Texture noneTextureGenerator();
	static std::vector<Pair> pairs;
public:
	
	static sf::Texture* get(sf::String name);
	static sf::Texture* get(int id);
	static void add(sf::String fileName);
	static void add(sf::String fileName, int id);
};