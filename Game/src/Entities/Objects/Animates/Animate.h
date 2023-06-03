#pragma once
#include <Entities/Entity.h>
#include <Animation/Types/AnimateAnimator.h>
#include <Animation/Types/GenericAnimator.h>

enum class Orientation;

class Animate : public Entity
{
public:
	Animate();
	Animate(sf::Vector2f position, sf::Vector2f size, const AnimateAnimator& animation, const GenericAnimator& deathParticlesAnimator, float speed, Level* level);
	
	// Inherited via Entity
	virtual void update() override;
	virtual void move(sf::Vector2f position) override;
	virtual void move(float x, float y) override;

	virtual void kill();
	
	bool getIsAlive() const;
	int getHealth() const;
	std::string getName() const;
	sf::Vector2f getDirection() const;
	float getSpeed() const;
	const GenericAnimator& getDeathParticlesAnimator() const;
	const std::vector<std::shared_ptr<Entity>>& getCollidablesList() const;

	void addHealth(int toAdd);
	void subHealth(int toSubtract);
	void setHealth(int health);
	void setName(const std::string& name);
	void setDirection(sf::Vector2f direction);
	void setSpeed(float speed);

	void setAnimation(AnimateAnimator::State state);

	void resolveCollisions(const Entity* entity, Orientation orientation);

	void addCollidable(std::shared_ptr<Entity> entity);
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
	GenericAnimator deathParticlesAnimator;

	std::vector<std::shared_ptr<Entity>> collidablesList;
};