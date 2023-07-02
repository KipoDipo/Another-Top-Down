#pragma once
#include <SFML/Graphics.hpp>
#include <Animation/Types/BinarySmartAnimator.h>
#include <Animation/Types/SingleAnimator.h>

class Player;

class Health : public sf::Drawable
{
public:
	Health(sf::Vector2f position, const BinarySmartAnimator& healthBar, const SingleAnimator& healthBarBackground);

	void setPlayer(const Player& player);

	void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	BinarySmartAnimator healthBar;
	SingleAnimator healthBarBackground;

	const Player* player;
};