#pragma once
#include <UI/UIElement.h>

class FPSCounter : public UIElement
{
public:
	FPSCounter(const std::string& pathToFont, sf::Vector2f position = {5, 10});

	virtual void update() override;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::Font font;
	sf::Text fps;
	sf::Clock clock;

	float sumFps = 0;
	int frames = 1;
};