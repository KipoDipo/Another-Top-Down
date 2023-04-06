#include "Textures.h"

std::vector<Textures::Pair> Textures::pairs;

sf::Texture Textures::none = load("none");

sf::Texture* Textures::get(sf::String name)
{
	for (size_t i = 0; i < pairs.size(); i++)
		if (pairs[i].name == name)
			return &(pairs[i].texture);
	return &none;
}
void Textures::add(sf::String fileName)
{
	pairs.push_back(Pair(fileName, load(fileName)));
}

sf::Texture Textures::load(std::string name)
{
	sf::Texture temp;
	if (!temp.loadFromFile("res/" + name + ".png"))
	{
		return none;
		//sf::RenderTexture texture;
		//texture.create(50, 50);
		//texture.clear(sf::Color::Yellow);
		//texture.display();
		//temp = sf::Texture(texture.getTexture());
	}
	return temp;
}