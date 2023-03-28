#include "Entity.h"

using namespace sf;

Entity::Entity()
	: Entity(Vector2f(0, 0))
{
}

Entity::Entity(Vector2f position)
{
	sprite.setPosition(position);
}

Entity::~Entity()
{
}

void Entity::move(Vector2f position)
{
	move(position.x, position.y);
}

void Entity::move(float x, float y)
{
	sprite.move(x, y);
	collider.left += x;
	collider.top += y;
}

void Entity::setPosition(Vector2f position)
{
	setPosition(position.x, position.y);
}

void Entity::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
	collider.left = x;
	collider.top = y;
}

Vector2f Entity::getPosition() const
{
	return sprite.getPosition();
}

const FloatRect& Entity::getCollider() const
{
	return collider;
}

void Entity::update()
{
}

Vector2f Entity::getCenter() const
{
	return Vector2f(collider.left, collider.top) + Vector2f(collider.width, collider.height) / 2.f;
}

void Entity::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(sprite, states);

	//for debugging
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		RectangleShape outline;
		outline.setPosition(collider.left, collider.top);
		outline.setSize(Vector2f(collider.width, collider.height));
		outline.setFillColor(Color::Transparent);
		outline.setOutlineColor(Color::Red);
		outline.setOutlineThickness(2);
		target.draw(outline, states);
	}
}