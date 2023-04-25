#include "Textures.h"
#include "Paths.h"

std::vector<Textures::Pair> Textures::pairs;

sf::Texture Textures::noneTexture(Textures::noneTextureGenerator());

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

sf::Texture* Textures::getNone()
{
	return &noneTexture;
}

sf::Texture* Textures::get(std::string name)
{
	for (size_t i = 0; i < pairs.size(); i++)
		if (pairs[i].name == name)
			return &(pairs[i].texture);
	printf("couldn't get texture with name: %s\n", name.c_str());
	return &noneTexture;
}

sf::Texture* Textures::get(int id)
{
	for (size_t i = 0; i < pairs.size(); i++)
		if (pairs[i].id == id)
			return &(pairs[i].texture);
	printf("couldn't get texture with ID: %d\n", id);
	return &noneTexture;
}

void Textures::add(std::string fileName)
{
	pairs.push_back(Pair(fileName, load(fileName)));
}

void Textures::add(std::string fileName, int id)
{
	pairs.push_back(Pair(fileName, load(fileName), id));
}

sf::Texture Textures::load(std::string name)
{
	sf::Texture temp;
	if (!temp.loadFromFile(Paths::textures + name + ".png"))
		return noneTexture;

	return temp;
}