#pragma once
#include "../Entity.h"
#include "../../Utilities/Utils.h"

class Solid;

class Animate : public Entity
{
public:
	Animate();
	Animate(sf::Vector2f position, sf::Texture* texture);

	void kill();
	bool getIsAlive() const;
	int getHealth() const;
	sf::String getName() const;
	sf::Vector2f getDirection();
	float getSpeed();

	void addHealth(int toAdd);
	void subHealth(int toSubtract);
	void setHealth(int health);
	void setName(sf::String name);
	void setDirection(sf::Vector2f direction);
	void setSpeed(float speed);

	void resolveCollisions(const Solid* solid, Orientation orientation);

	virtual void update() override = 0;
	virtual void movement(Orientation orientation = Orientation::None) = 0;

private:
	bool isAlive = true;
	int health;
	float speed;
	sf::Vector2f dir;
	sf::String name = "NONE";
};