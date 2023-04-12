#pragma once
#include <SFML/Graphics.hpp>

class Entity : public virtual sf::Drawable
{
public:
	Entity();
	Entity(sf::Vector2f position, sf::Texture* texture);
	virtual ~Entity();

	void move(sf::Vector2f position);
	void move(float x, float y);
	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);

	sf::Vector2f getPosition() const;
	sf::Vector2f getCenter() const;
	const sf::FloatRect& getCollider() const;

	bool collides(const Entity& entity);
	bool collides(const sf::FloatRect& rect);

	virtual void update();

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
protected:
	sf::Sprite sprite;
	sf::FloatRect collider;
};