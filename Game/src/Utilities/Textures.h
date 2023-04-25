#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Textures
{
	static sf::Texture load(std::string name);
	struct Pair
	{
		int id;
		std::string name;
		sf::Texture texture;

		Pair(std::string name, sf::Texture texture, int id = -1)
			: name(name), texture(texture), id(id)
		{
		}
	};
	static sf::Texture noneTexture;
	static sf::Texture noneTextureGenerator();
	static std::vector<Pair> pairs;
public:
	
	static sf::Texture* get(std::string name);
	static sf::Texture* get(int id);
	static sf::Texture* getNone();

	static void add(std::string fileName);
	static void add(std::string fileName, int id);
};