#include "Health.h"
#include <Utilities/DeltaTime.h>
#include <Entities/Objects/Animates/Types/Player.h>

Health::Health(sf::Vector2f position, const BinarySmartAnimator& healthBar, const SingleAnimator& healthBarBackground)
	: healthBar(healthBar), healthBarBackground(healthBarBackground), player(nullptr)
{
	this->healthBar.getSprite().setPosition(position);
	this->healthBarBackground.getSprite().setPosition(position);
	this->healthBar.set(false);
}

void Health::setPlayer(const Player& player)
{
	this->player = &player;
}


void Health::update()
{
	if (healthBar.getState() == false && player->getHealth() == player->getMaxHealth())
		healthBar.play();

	healthBar.getSprite().setTextureRect(sf::IntRect(
		0, 0, 
		(int)(healthBar.getSprite().getTexture()->getSize().x * (player->getHealth() / (float)player->getMaxHealth())),
		healthBar.getSprite().getTexture()->getSize().y
	));
	
	healthBar.update();
	healthBarBackground.update();

}

void Health::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(healthBarBackground, states);
	target.draw(healthBar, states);
}
