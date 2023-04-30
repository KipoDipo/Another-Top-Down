#include "Entity.h"
#include "../Utilities/Utils.h"

using namespace sf;

Entity::Entity()
	: Entity(Vector2f(0, 0), AnimationCollection::getNone())
{
}

Entity::Entity(Vector2f position, const Animator& animationCollection) /* Consider - Maybe custom collider? */
	: animator(animationCollection)

{
	animator.setPosition(position);
	
	collider = FloatRect(
		position.x, 
		position.y, 
		(float)animator.getAnimation().getSize().x, 
		(float)animator.getAnimation().getSize().y
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
	animator.move(x, y);
	collider.left += x;
	collider.top += y;
}

void Entity::setPosition(Vector2f position)
{
	setPosition(position.x, position.y);
}

void Entity::setPosition(float x, float y)
{
	animator.setPosition(x, y);
	collider.left = x;
	collider.top = y;
}

Vector2f Entity::getPosition() const
{
	return animator.getAnimation().getPosition();
}

const sf::FloatRect& Entity::getCollider() const
{
	return collider;
}

bool Entity::collides(const Entity& entity)
{
	return collider.intersects(entity.collider);
}

bool Entity::collides(const FloatRect& rect)
{
	return collider.intersects(rect);
}

void Entity::setAnimation(const std::string name)
{
	animator.setAnimation(name);
}

void Entity::update()
{
	animator.update();
}

Vector2f Entity::getCenter() const
{
	return Vector2f(collider.left, collider.top) + Vector2f(collider.width, collider.height) / 2.f;
}

void Entity::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(animator.getAnimation(), states);

	//for debugging
	static bool alwaysOn = false;
	if (Keyboard::isKeyPressed(Keyboard::Tilde))
		alwaysOn = true;

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