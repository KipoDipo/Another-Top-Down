#pragma once
#include <SFML/Graphics.hpp>
#include <Animation/Types/BinaryAnimator.h>

class Player;

class Health : public sf::Drawable
{
public:
	Health(sf::Vector2f position, const BinaryAnimator& healthBar, const BinaryAnimator& healthBarBackground);

	void setPlayer(const Player& player);

	void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	BinaryAnimator healthBar;
	BinaryAnimator healthBarBackground;

	bool activeAnim = false;
	sf::Clock clock;
	int randomDelay = 0;

	const Player* player;
};