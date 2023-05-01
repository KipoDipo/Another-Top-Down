#pragma once
#include <SFML/Graphics.hpp>
#include "../Entity.h"
#include "../../Animation/Types/InanimateAnimation.h"

class Inanimate : public Entity
{
public:
	Inanimate();
	Inanimate(sf::Vector2f position);
	Inanimate(sf::Vector2f position, const InanimateAnimation& animation);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// Inherited via Entity
	virtual void update() override;

private:
	InanimateAnimation animator;
};