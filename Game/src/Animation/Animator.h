#pragma once
#include "AnimationCollection.h"

class Animator
{
public:
	Animator();
	Animator(const Animator& other);
	const Animator& operator=(const Animator& other);
	
	Animator(const std::string& defaultAnimationName);
	Animator(const AnimationCollection& animations);
	Animator(const AnimationCollection& animations, const std::string& defaultAnimationName);
	
	void setAnimation(const std::string& name);

	void move(sf::Vector2f position);
	void move(float x, float y);
	void setOrigin(sf::Vector2f origin);
	void setOrigin(float x, float y);
	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);

	void add(const std::string& fileName, float switchTime, const std::string& name);
	void add(const std::string& fileName, float switchTime);
	
	const Animation& getAnimation() const;
	
	void update();

private:
	AnimationCollection animations;
	Animation* currentAnimation;
	std::string defaultAnimationName;
};
