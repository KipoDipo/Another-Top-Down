#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Level.h"

class Game
{
public:
	static void Start(unsigned width, unsigned height, const std::string& title);
	
private:
	static void Init();

	static void Update();
	static void Draw();

	static std::vector<std::unique_ptr<Level>> levels;
	static sf::RenderWindow window;
};