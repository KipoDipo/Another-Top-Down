#include "Textures.h"

std::vector<Textures::Pair> Textures::pairs;

sf::Texture Textures::noneTexture = Textures::noneTextureGenerator();

sf::Texture Textures::noneTextureGenerator()
{
	sf::Texture texture;
	texture.create(50, 50);
	sf::Image img = texture.copyToImage();
	
	sf::Color one = sf::Color(255, 200, 80);
	sf::Color two = sf::Color(255, 80, 100);
	
	for (size_t i = 0; i < 50; i++)
	{
		if (i != 0 && i % 25 == 0)
			std::swap(one, two);
		
		for (size_t j = 0; j < 50; j++)
		{
			if (j < 25)
				img.setPixel(j, i, one);
			else
				img.setPixel(j, i, two);
		}
	}
	
	texture.update(img);
	return texture;
}

sf::Texture* Textures::get(sf::String name)
{
	for (size_t i = 0; i < pairs.size(); i++)
		if (pairs[i].name == name)
			return &(pairs[i].texture);
	return &noneTexture;
}

sf::Texture* Textures::get(int id)
{
	for (size_t i = 0; i < pairs.size(); i++)
		if (pairs[i].id == id)
			return &(pairs[i].texture);
	return &noneTexture;
}

void Textures::add(sf::String fileName)
{
	pairs.push_back(Pair(fileName, load(fileName)));
}

void Textures::add(sf::String fileName, int id)
{
	pairs.push_back(Pair(fileName, load(fileName), id));
}

sf::Texture Textures::load(std::string name)
{
	sf::Texture temp;
	if (!temp.loadFromFile("res/" + name + ".png"))
	{
		return noneTexture;
	}
	return temp;
}