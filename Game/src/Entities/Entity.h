#pragma once
#include <SFML/Graphics.hpp>
#include <Level.h>

class Entity : public virtual sf::Drawable
{
public:
	Entity();
	Entity(sf::Vector2f position, sf::Vector2f size, Level* level = nullptr);
	virtual ~Entity() = default;

	virtual void move(sf::Vector2f position);
	virtual void move(float x, float y);
	virtual void setPosition(sf::Vector2f position);
	virtual void setPosition(float x, float y);

	sf::Vector2f getPosition() const;
	sf::Vector2f getCenter() const;
	sf::Vector2f getSize() const;
	const sf::FloatRect& getCollider() const;
	Level& getLevel();

	bool collides(const Entity& entity) const;
	bool collides(const sf::FloatRect& rect) const;

	virtual void update();

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::FloatRect collider;
	Level* level;
};