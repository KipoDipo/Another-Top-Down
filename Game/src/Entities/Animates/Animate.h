#pragma once
#include "../Entity.h"

enum class Orientation;

class Animate : public Entity
{
public:
	Animate();
	Animate(sf::Vector2f position, const Animation& sprite, float speed = 0);
	
	virtual void update() override = 0;
	void kill();
	
	bool getIsAlive() const;
	int getHealth() const;
	std::string getName() const;
	sf::Vector2f getDirection();
	float getSpeed();
	const std::vector<Entity*>& getCollidablesList() const;

	void addHealth(int toAdd);
	void subHealth(int toSubtract);
	void setHealth(int health);
	void setName(const std::string& name);
	void setDirection(sf::Vector2f direction);
	void setSpeed(float speed);

	
	void resolveCollisions(const Entity* entity, Orientation orientation);

	void addCollidable(Entity* entity);
	void clearCollidables();

protected:
	virtual void movement(Orientation orientation) = 0;

private:
	bool isAlive = true;
	int health;
	float speed;
	sf::Vector2f dir;
	std::string name = "NONE";

	std::vector<Entity*> collidablesList;
};