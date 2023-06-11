#include "Particle.h"
#include <Utilities/DeltaTime.h>

Particle::Particle()
	: duration(0), speed(0), direction({ 0,0 }), isDone(true)
{
}

Particle::Particle(const SingleAnimator& animator, sf::Vector2f location, sf::Vector2f direction, float speed, float duration)
	: animator(animator), direction(direction), speed(speed), duration(duration), isDone(false)
{
	this->animator.getSprite().setPosition(location);
	this->animator.getSprite().setOrigin((sf::Vector2f)this->animator.getSprite().getTexture()->getSize() / 2.f);
}

bool Particle::isActive() const
{
	return !isDone;
}

void Particle::update()
{
	if (isDone)
		return;

	animator.update();
	animator.getSprite().move(direction * speed * DeltaTime::get());

	if (clock.getElapsedTime().asSeconds() > duration)
		isDone = true;
}

void Particle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (isDone)
		return;

	target.draw(animator, states);
}

