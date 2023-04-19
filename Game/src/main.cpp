#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Entities/All.h"
#include "Utilities/All.h"

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
	Textures::add("guide");

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Title");

	//window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(144);
	Player player(Vector2f(250, 250), 300);
	float zoom = 2.f;

	std::vector<Enemy> ens;
	ens.push_back(Enemy(Vector2f(180, 30) , rand() % 20 + 20));
	ens.push_back(Enemy(Vector2f(230, 100), rand() % 20 + 20));
	ens.push_back(Enemy(Vector2f(260, 60) , rand() % 20 + 20));



	std::vector<Solid> solids;
	solids.push_back(Solid(Vector2f(50, 0)));
	solids.push_back(Solid(Vector2f(50, 50)));
	solids.push_back(Solid(Vector2f(50, 100)));
	solids.push_back(Solid(Vector2f(50, 150)));

	solids.push_back(Solid(Vector2f(00, 200)));
	solids.push_back(Solid(Vector2f(-50, 200)));
	solids.push_back(Solid(Vector2f(-100, 200)));

	for (size_t i = 0; i < ens.size(); i++)
	{
		ens[i].setTarget(&player);
		for (size_t j = 0; j < solids.size(); j++)
			ens[i].addCollidable(&solids[j]);
	}
	
	std::vector<Ground> grounds;
	Ground guide(Vector2f(0, 0), Textures::get("guide"));
	for (int i = -3; i < 10; i++)
		for (int j = -3; j < 10; j++)
			grounds.push_back(Ground(Vector2f(j * 50, i * 50)));

	player.addEnemies(&ens);
	for (size_t i = 0; i < solids.size(); i++)
		player.addCollidable(&solids[i]);

	
	Vector2f smoothCamera = player.getCenter();
	DeltaTime::reset();
	// This is very cluttered, will refactor when I make a UI class
	Text text;
	Font font;
	font.loadFromFile("res\\fonts\\Pixeled.ttf");

	text.setFont(font);
	text.setFillColor(Color::White);
	text.setCharacterSize(25);
	text.setString("FPS: wait");

	Clock clock;

	float sumFps = 0;
	int frames = 0;

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
		
		for (size_t i = 0; i < ens.size(); i++)
			ens[i].update();
		
		
		/* Draw & Display */

		window.clear(Color(30, 20, 30));

		smoothCamera += ((player.getCenter() - smoothCamera) * 2.f) * DeltaTime::get();

		View smoothView(Utils::roundedBySubdivions(smoothCamera, (int)zoom), Vector2f(WIDTH / zoom, HEIGHT / zoom));

		window.setView(smoothView);

		for (size_t i = 0; i < grounds.size(); i++)
			window.draw(grounds[i]);

		for (size_t i = 0; i < solids.size(); i++)
			window.draw(solids[i]);

		for (size_t i = 0; i < ens.size(); i++)
			window.draw(ens[i]);

		window.draw(player);
		window.draw(guide); // just a debug guide showing where {0,0} is

		/* Draw UI(very beta) */
		window.setView(window.getDefaultView());
		{
			window.draw(text);
			if (clock.getElapsedTime().asSeconds() > 0.5f)
			{
				clock.restart();
				text.setString("FPS: " + std::to_string((int)(sumFps / frames)));
				frames = sumFps = 0;
			}
			else
			{
				sumFps += 1.f / DeltaTime::get();
				frames++;
			}
			text.setPosition(Vector2f(5, 10));
		}
		window.setView(smoothView);

		window.display();
		DeltaTime::reset();
	}
}