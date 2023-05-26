#pragma once
#include "../../Entity.h"
#include "../../../Animation/Types/AnimateAnimator.h"

enum class Orientation;

class Animate : public Entity
{
public:
	Animate();
	Animate(sf::Vector2f position, sf::Vector2f size, const AnimateAnimator& animation, float speed = 0);
	
	virtual void update() override;

	virtual void move(sf::Vector2f position);
	virtual void move(float x, float y);

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

	void setAnimation(AnimateAnimator::State state);

	void resolveCollisions(const Entity* entity, Orientation orientation);

	void addCollidable(Entity* entity);
	void clearCollidables();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
	virtual void movement(Orientation orientation) = 0;

private:
	bool isAlive = true;
	int health;
	float speed;
	sf::Vector2f dir;
	std::string name = "NONE";
	AnimateAnimator animator;
	std::vector<Entity*> collidablesList;
};