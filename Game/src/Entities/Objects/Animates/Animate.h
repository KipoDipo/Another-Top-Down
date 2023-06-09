#pragma once
#include <Entities/Entity.h>
#include <Animation/Types/AnimateAnimator.h>
#include <Animation/Types/RandomAnimator.h>

class Animate : public Entity
{
public:
	Animate();
	Animate(sf::Vector2f position, sf::Vector2f size, const AnimateAnimator& animation, const RandomAnimator& deathParticlesAnimator, float speed, Level* level);
	
	// Inherited via Entity
	virtual void update() override;
	virtual void move(sf::Vector2f position, bool collides = true);
	virtual void move(float x, float y, bool collides = true);

	virtual void kill();
	
	bool getIsAlive() const;
	int getHealth() const;
	int getMaxHealth() const;
	std::string getName() const;
	float getSpeed() const;
	const RandomAnimator& getDeathParticlesAnimator() const;

	void addHealth(int toAdd);
	void subHealth(int toSubtract);
	void setHealth(int health);
	void setMaxHealth(int health);
	void setName(const std::string& name);
	void setSpeed(float speed);

	void setAnimation(AnimateAnimator::State state);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
	virtual void movement() = 0;

private:
	bool isAlive = true;
	int health;
	int maxHealth;
	float speed;
	std::string name = "NONE";
	AnimateAnimator animator;
	RandomAnimator deathParticlesAnimator;
};