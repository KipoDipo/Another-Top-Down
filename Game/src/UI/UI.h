#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Types/FPSCounter.h"
#include "Types/Health.h"

class UI : public sf::Drawable
{
public:
	UI(const std::string& font, const BinarySmartAnimator& healthBarFull, const SingleAnimator& healthBarEmpty);

	void setPlayer(const Player& player);
	
	void update();

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	FPSCounter fpsCounter;
	Health health;
};