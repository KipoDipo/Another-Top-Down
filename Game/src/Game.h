#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Level.h"

class Game
{
public:
	static void Start(unsigned width, unsigned height, std::string title);
	
private:
	static void Init();

	static void Update();
	static void Draw();

	static std::vector<Level*> levels;
	static sf::RenderWindow window;
};