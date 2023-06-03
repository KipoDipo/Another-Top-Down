#include "Entity.h"
#include <Utilities/Utils.h>
#include <Level.h>

using namespace sf;

Entity::Entity()
	: Entity(Vector2f(0, 0), Vector2f(50, 50))
{
}

Entity::Entity(Vector2f position, Vector2f size, Level* level) /* Consider - Maybe custom collider? */
	: level(level)
{
	collider = FloatRect(
		position.x, 
		position.y, 
		size.x, 
		size.y
	);
}

Entity::~Entity()
{
}


void Entity::move(Vector2f direction)
{
	move(direction.x, direction.y);
}

void Entity::move(float x, float y)
{
	collider.left += x;
	collider.top += y;
}

void Entity::setPosition(Vector2f position)
{
	setPosition(position.x, position.y);
}

void Entity::setPosition(float x, float y)
{
	collider.left = x;
	collider.top = y;
}

Vector2f Entity::getPosition() const
{
	return Vector2f(collider.left, collider.top);
}

const sf::FloatRect& Entity::getCollider() const
{
	return collider;
}

Level& Entity::getLevel()
{
	return *level;
}

bool Entity::collides(const Entity& entity) const
{
	return collider.intersects(entity.collider);
}

bool Entity::collides(const FloatRect& rect) const
{
	return collider.intersects(rect);
}

void Entity::update()
{
}

Vector2f Entity::getCenter() const
{
	return Vector2f(collider.left, collider.top) + Vector2f(collider.width, collider.height) / 2.f;
}

const sf::Vector2f Entity::getSize() const
{
	return sf::Vector2f(collider.width, collider.height);
}

bool alwaysOn = false;
void Entity::draw(RenderTarget& target, RenderStates states) const
{
	//for debugging
	if (Keyboard::isKeyPressed(Keyboard::Tilde))
		alwaysOn = true;

	if (Keyboard::isKeyPressed(Keyboard::Tilde) && Keyboard::isKeyPressed(Keyboard::LShift))
		alwaysOn = false;

	if (Keyboard::isKeyPressed(Keyboard::Escape) || alwaysOn)
	{
		RectangleShape outline;
		outline.setPosition(collider.left, collider.top);
		outline.setSize(Vector2f(collider.width, collider.height));
		outline.setFillColor(Color::Transparent);
		outline.setOutlineColor(Color::Green);
		outline.setOutlineThickness(-1);
		target.draw(outline, states);
	}
}