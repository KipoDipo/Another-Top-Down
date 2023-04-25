#pragma once
#include <SFML/Graphics.hpp>
#include "../Animation/Animation.h"

class Attack : public virtual sf::Drawable
{
public:
	Attack(float speed, float size, float distance, float range, const Animation& sprite);
	virtual ~Attack();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual Attack* clone() const = 0;
	
	virtual void update(const sf::Vector2f& origin) = 0;

	void start(sf::Vector2f direction);
	void stop();

	bool getIsActive() const;
	float getProgress() const;
	float getSpeed() const;
	float getSize() const;
	float getDistance() const;
	float getRange() const;
	sf::Vector2f getDirection() const;
	const sf::FloatRect& getCollider() const;

protected:
	void setIsActive(bool state);
	void setProgress(float progress);
	void addProgress(float plusProgress);
	void setSpeed(float speed);
	void setSize(float size);
	void setDistance(float distance);
	void setRange(float range);
	void setDirection(sf::Vector2f direction);
	void setCollider(const sf::FloatRect& collider);
	void setSpritePosition(sf::Vector2f position);

private:
	bool isActive;
	float progress; // 0.0 - 1.0
	float speed;
	float size;
	float distance;
	float range;
	sf::Vector2f direction;
	sf::FloatRect collider;
	Animation sprite;
};