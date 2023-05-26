#include "Inanimate.h"

//#define COLLIDER_DEBUG

Inanimate::Inanimate()
{
}

Inanimate::Inanimate(sf::Vector2f position)
	: Entity(position, sf::Vector2f(50,50))
{
	animator.get().setPosition(position);
}

Inanimate::Inanimate(sf::Vector2f position, const InanimateAnimator& animation)
	: Entity(position, sf::Vector2f(50, 50)), animator(animation)
{
	animator.get().setPosition(position);
}

void Inanimate::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(animator, states);

#ifdef COLLIDER_DEBUG
	Entity::draw(target, states);
#endif
}

void Inanimate::update()
{
	animator.update();
}
