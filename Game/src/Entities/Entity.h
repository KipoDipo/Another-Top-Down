#pragma once
#include <SFML/Graphics.hpp>

class Entity : public virtual sf::Drawable
{
public:
	Entity();
	Entity(sf::Vector2f position);
	virtual ~Entity();

	void move(sf::Vector2f position);
	void move(float x, float y);
	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);
	sf::Vector2f getPosition() const;
	void kill();
	const sf::FloatRect& getCollider() const;
	bool getIsAlive() const;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
protected:
	bool isAlive = true;
	sf::Sprite sprite;
	sf::FloatRect collider;
};