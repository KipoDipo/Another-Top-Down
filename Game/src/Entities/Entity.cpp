#include "Entity.h"

Entity::Entity()
	: Entity(sf::Vector2f(0, 0))
{
}

Entity::Entity(sf::Vector2f position)
{
	sprite.setPosition(position);
}

Entity::~Entity()
{
}

void Entity::move(sf::Vector2f position)
{
	move(position.x, position.y);
}

void Entity::move(float x, float y)
{
	sprite.move(x, y);
	collider.left += x;
	collider.top += y;
}

void Entity::setPosition(sf::Vector2f position)
{
	setPosition(position.x, position.y);
}

void Entity::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
	collider.left = x;
	collider.top = y;
}

sf::Vector2f Entity::getPosition() const
{
	return sprite.getPosition();
}

void Entity::kill()
{
	isAlive = false;
	setPosition(-100, -100);
}

const sf::FloatRect& Entity::getCollider() const
{
	return collider;
}

bool Entity::getIsAlive() const
{
	return isAlive;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);

	//for debug
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		sf::RectangleShape outline;
		outline.setPosition(collider.left, collider.top);
		outline.setSize(sf::Vector2f(collider.width, collider.height));
		outline.setFillColor(sf::Color::Transparent);
		outline.setOutlineColor(sf::Color::Red);
		outline.setOutlineThickness(2);
		target.draw(outline, states);
	}
}