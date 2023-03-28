#pragma once
#include "../Entity.h"

class Animate : public Entity
{
public:
	Animate();
	Animate(sf::Vector2f position, sf::Texture* texture);

	void kill();
	bool getIsAlive() const;
	int getHealth() const;
	sf::String getName() const;

	void addHealth(int toAdd);
	void subHealth(int toSubtract);
	void setHealth(int health);
	void setName(sf::String name);

	virtual void update() override = 0;
	virtual void movement() = 0;


private:
	sf::String name = "NONE";
	bool isAlive = true;
	int health;
};