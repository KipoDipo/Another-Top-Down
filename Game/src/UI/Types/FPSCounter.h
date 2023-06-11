#pragma once
#include <SFML/Graphics.hpp>

class FPSCounter : public sf::Drawable
{
public:
	FPSCounter(const std::string& pathToFont, sf::Vector2f position = {5, 10});

	void update();

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::Font font;
	sf::Text fps;
	sf::Clock clock;

	float sumFps = 0;
	int frames = 1;
};