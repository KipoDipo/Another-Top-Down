#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Entities/Animates/Types/Player.h"
#include "Entities/Animates/Types/Enemy.h"
#include "Entities/Inanimates/Solid.h"

using namespace sf;

const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 720;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Title");

	window.setVerticalSyncEnabled(true);
	Player player;

	std::vector<Enemy> ens;
	ens.push_back(Enemy(Vector2f(30, 30)));
	ens.push_back(Enemy(Vector2f(80, 100)));
	ens.push_back(Enemy(Vector2f(140, 60)));
	Vector2f smoothCamera = player.getCenter();

	std::vector<Solid> solids;
	solids.push_back(Solid(Vector2f(50, 50)));


	player.addEnemies(&ens);
	player.addSolids(&solids);
	
	while (window.isOpen())
	{
		/* Dispatch Events */

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		
		/* Update */

		player.update();
		


		/* Draw & Display */

		window.clear();

		smoothCamera += (player.getCenter() - smoothCamera) / 15.f;
		View smoothView(smoothCamera, Vector2f(WIDTH, HEIGHT));
		window.setView(smoothView);

		for (size_t i = 0; i < solids.size(); i++)
			window.draw(solids[i]);
		
		for (size_t i = 0; i < ens.size(); i++)
			window.draw(ens[i]);

		window.draw(player);
		
		window.display();
	}
}