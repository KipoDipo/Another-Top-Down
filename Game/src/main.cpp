#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Entities/Types/Player.h"
#include "Entities/Types/Enemy.h"

using namespace sf;

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "Title");
	window.setVerticalSyncEnabled(true);
	Player player;
	//Enemy enemy(Vector2f(30, 30));
	std::vector<Enemy> ens;
	ens.push_back(Enemy(Vector2f(30, 30)));
	ens.push_back(Enemy(Vector2f(80, 100)));
	ens.push_back(Enemy(Vector2f(140, 60)));
	Vector2f smoothCamera = player.getPosition();
	while (window.isOpen())
	{
		/* Update */
		player.update(ens);

		
		/* Draw & Display */

		window.clear();
		
		smoothCamera += (player.getPosition() - smoothCamera) / 15.f;
		View smoothView(smoothCamera, Vector2f(500, 500));
		window.setView(smoothView);
		
		for (size_t i = 0; i < ens.size(); i++)
			window.draw(ens[i]);
		
		window.draw(player);

		window.display();

		/* Dispatch Events */
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
}