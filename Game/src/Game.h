#pragma once
#include <SFML/Window.hpp>
#include <Level.h>
#include <UI/UI.h>

class Game
{
public:
	static void Start(unsigned width, unsigned height, const std::string& title);
	
private:
	static void Init();

	static void Update();
	static void Draw();

	static std::vector<std::shared_ptr<Level>> levels;
	static size_t currentLevel;

	static UI ui;

	static sf::RenderWindow window;
};