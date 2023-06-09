#pragma once
#include "../Entity.h"
#include <Animation/Types/SingleAnimator.h>

class Attack : public Entity
{
public:
	Attack(float speed, float size, float distance, float range, const SingleAnimator& animations);
	virtual ~Attack();
	virtual std::unique_ptr<Attack> clone() const = 0;
	
	virtual void update(const sf::Vector2f& origin) = 0;

	void start(sf::Vector2f direction);
	void stop();

	bool getIsActive() const;
	float getProgress() const;
	float getSpeed() const;
	float getDistance() const;
	float getRange() const;
	sf::Vector2f getDirection() const;

	//Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	void setIsActive(bool state);
	void setProgress(float progress);
	void addProgress(float plusProgress);
	void setSpeed(float speed);
	void setDistance(float distance);
	void setRange(float range);
	void setDirection(sf::Vector2f direction);

	// Inherited via Entity
	virtual void setPosition(sf::Vector2f position) override;
	virtual void setPosition(float x, float y) override;

	void updateAnimation();

private:
	bool isActive;
	float progress; // 0.0 - 1.0
	float speed;
	float size;
	float distance;
	float range;
	sf::Vector2f direction;
	SingleAnimator animator;
};