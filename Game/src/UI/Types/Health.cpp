#include "Health.h"
#include <Utilities/DeltaTime.h>
#include <Entities/Objects/Animates/Types/Player.h>

Health::Health(sf::Vector2f position, const BinaryAnimator& healthBar, const BinaryAnimator& healthBarBackground)
	: healthBar(healthBar), healthBarBackground(healthBarBackground), player(nullptr)
{
	this->healthBar.getSprite().setPosition(position);
	this->healthBarBackground.getSprite().setPosition(position);
	this->healthBar.setState(false);
	this->healthBarBackground.setState(false);
}

void Health::setPlayer(const Player& player)
{
	this->player = &player;
}


void Health::update()
{
	healthBar.getSprite().setTextureRect(sf::IntRect(
		0, 0, 
		(int)(healthBar.getSprite().getTexture()->getSize().x * (player->getHealth() / (float)player->getMaxHealth())),
		healthBar.getSprite().getTexture()->getSize().y
	));
	healthBar.update();
	healthBarBackground.update();

	if (!activeAnim && clock.getElapsedTime().asSeconds() > 2 + randomDelay)
	{
		healthBar.setState(true);
		healthBarBackground.setState(true);
		randomDelay = Utils::random(3);
		activeAnim = true;
	}
	else if (healthBar->hasFinished())
	{
		activeAnim = false;
		healthBar.setState(false);
		clock.restart();
	}
}

void Health::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(healthBarBackground, states);
	target.draw(healthBar, states);
}
