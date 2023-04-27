#include "Animator.h"
#include "../Utilities/ConsoleColors.h"

Animator::Animator()
	: currentAnimation(&Animation::getNone())
{
}

Animator::Animator(const Animator& other)
	: animations(other.animations), currentAnimation(nullptr)
{
	for (size_t i = 0; i < other.animations.getSize(); i++)
		if (other.currentAnimation == &other.animations[i])
		{
			currentAnimation = &animations[i];
			break;
		}
	if (currentAnimation == nullptr)
		printf("%s something has gone terribly wrong when using the copy ctor of Animator...", ConsoleColors::redFlag);
}

const Animator& Animator::operator=(const Animator& other)
{
	animations = other.animations;
	currentAnimation = nullptr;
	for (size_t i = 0; i < other.animations.getSize(); i++)
		if (other.currentAnimation == &other.animations[i])
		{
			currentAnimation = &animations[i];
			break;
		}
	if (currentAnimation == nullptr)
		printf("%s something has gone terribly wrong when using the operator= of Animator...", ConsoleColors::redFlag);
}

Animator::Animator(const std::string& defaultAnimationName)
	: currentAnimation(&Animation::getNone()), defaultAnimationName(defaultAnimationName)
{
}

Animator::Animator(const AnimationCollection& animations)
	: animations(animations), currentAnimation(&this->animations[0])
{
}

Animator::Animator(const AnimationCollection& animations, const std::string& defaultAnimationName)
	: animations(animations), currentAnimation(&this->animations[defaultAnimationName])
{
}

void Animator::setAnimation(const std::string& name)
{
	animations[name].setPosition(currentAnimation->getPosition());
	currentAnimation = &animations[name];
	currentAnimation->reset();
}

void Animator::move(sf::Vector2f position)
{
	currentAnimation->move(position);
}

void Animator::move(float x, float y)
{
	currentAnimation->move(x, y);
}

void Animator::setOrigin(sf::Vector2f origin)
{
	animations.setOrigin(origin);
}

void Animator::setOrigin(float x, float y)
{
	animations.setOrigin(x, y);
}

void Animator::setPosition(sf::Vector2f position)
{
	currentAnimation->setPosition(position);
}

void Animator::setPosition(float x, float y)
{
	currentAnimation->setPosition(x, y);
}

void Animator::add(const std::string& fileName, float switchTime, const std::string& name)
{
	animations.add(fileName, switchTime, name);
	currentAnimation = defaultAnimationName == "" ? &animations[0] : &animations[defaultAnimationName];
}

void Animator::add(const std::string& fileName, float switchTime)
{
	animations.add(fileName, switchTime);
	currentAnimation = defaultAnimationName == "" ? &animations[0] : &animations[defaultAnimationName];
}

const Animation& Animator::getAnimation() const
{
	return *currentAnimation;
}

void Animator::update()
{
	currentAnimation->update();
}
