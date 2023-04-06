#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Entities/Animates/Types/Player.h"
#include "Entities/Animates/Types/Enemy.h"
#include "Entities/Inanimates/Types/Solid.h"
#include "Entities/Inanimates/Types/Ground.h"

using namespace sf;

const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 720;

int main()
{
	Textures::add("player");
	Textures::add("enemy");
	Textures::add("ball");
	Textures::add("defaultGround");
	Textures::add("defaultSolid");

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Title");

	window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(60);
	Player player(Vector2f(250,250), 5);
	float zoom = 2;

	std::vector<Enemy> ens;
	ens.push_back(Enemy(Vector2f(180, 30)));
	ens.push_back(Enemy(Vector2f(230, 100)));
	ens.push_back(Enemy(Vector2f(260, 60)));
	Vector2f smoothCamera = player.getCenter();

	std::vector<Solid> solids;
	solids.push_back(Solid(Vector2f(50, 0)));
	solids.push_back(Solid(Vector2f(50, 50)));
	solids.push_back(Solid(Vector2f(50, 100)));
	solids.push_back(Solid(Vector2f(50, 150)));
	
	solids.push_back(Solid(Vector2f(00, 200)));
	solids.push_back(Solid(Vector2f(-50, 200)));
	solids.push_back(Solid(Vector2f(-100, 200)));

	std::vector<Ground> grounds;
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			grounds.push_back(Ground(Vector2f(i * 50, j * 50)));
		}
	}

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

		window.clear(Color(20,20,20));

		smoothCamera += (player.getCenter() - smoothCamera) / 15.f;
		
		if (fabsf(smoothCamera.x - player.getCenter().x) < 0.3f)
			smoothCamera.x = player.getCenter().x;
		if (fabsf(smoothCamera.y - player.getCenter().y) < 0.3f)
			smoothCamera.y = player.getCenter().y;

		View smoothView(smoothCamera, Vector2f(WIDTH / zoom, HEIGHT / zoom));
		window.setView(smoothView);

		for (size_t i = 0; i < grounds.size(); i++)
			window.draw(grounds[i]);

		for (size_t i = 0; i < solids.size(); i++)
			window.draw(solids[i]);

		for (size_t i = 0; i < ens.size(); i++)
			window.draw(ens[i]);

		window.draw(player);
		
		window.display();
	}
}