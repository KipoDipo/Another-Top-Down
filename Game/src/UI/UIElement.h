#pragma once
#include <SFML/Graphics.hpp>

class UIElement : public sf::Drawable
{
public:
	virtual void update() = 0;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
};