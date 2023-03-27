#include "Textures.h"

sf::Texture Textures::load(std::string name)
{
	sf::Texture temp;
	if (!temp.loadFromFile("res/" + name + ".png"))
	{
		sf::RenderTexture texture;
		texture.create(50, 50);
		texture.clear(sf::Color::Yellow);
		texture.display();
		temp = sf::Texture(texture.getTexture());
	}
	return temp;
}

sf::Texture Textures::player = load("player");
sf::Texture Textures::enemy = load("enemy");