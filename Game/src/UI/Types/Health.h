#pragma once
#include <SFML/Graphics.hpp>
#include <Animation/Types/BinarySmartAnimator.h>
#include <Animation/Types/SingleAnimator.h>
#include <UI/UIElement.h>
#include <Entities/Objects/Animates/Animate.h>

class Player;

class Health : public UIElement
{
public:
	Health(sf::Vector2f position, const Animate& player, const BinarySmartAnimator& healthBar, const SingleAnimator& healthBarBackground);

	void setTarget(const Animate& target);

	virtual void update() override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	BinarySmartAnimator healthBar;
	SingleAnimator healthBarBackground;

	const Animate* target;
};