#include "Health.h"
#include <Utilities/DeltaTime.h>
#include <Entities/Objects/Animates/Types/Player.h>

Health::Health(sf::Vector2f position, const Animate& target, const BinarySmartAnimator& healthBar, const SingleAnimator& healthBarBackground)
	: healthBar(healthBar), healthBarBackground(healthBarBackground), target(&target)
{
	this->healthBar.getSprite().setPosition(position);
	this->healthBarBackground.getSprite().setPosition(position);
	this->healthBar.set(false);
}

void Health::setTarget(const Animate& target)
{
	this->target = &target;
}


void Health::update()
{
	if (healthBar.getState() == false && target->getHealth() == target->getMaxHealth())
		healthBar.play();

	healthBar.getSprite().setTextureRect(sf::IntRect(
		0, 0, 
		(int)(healthBar.getSprite().getTexture()->getSize().x * (target->getHealth() / (float)target->getMaxHealth())),
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
