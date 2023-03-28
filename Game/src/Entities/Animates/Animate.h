#pragma once
#include <SFML/System.hpp>
#include "../Entity.h"

class Animate : public Entity
{
public:
	void kill();
	bool getIsAlive() const;
	int getHealth() const;
	
	void addHealth(int toAdd);
	void subHealth(int toSubtract);
	void setHealth(int health);

	virtual void update() override = 0;
	virtual void movement() = 0;
private:
	sf::String name;
	bool isAlive = true;
	int health;
};

