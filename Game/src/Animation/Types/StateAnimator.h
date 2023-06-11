#pragma once
#include "../Animator.h"
#include <Utilities/Utils.h>

class StateAnimator : public sf::Drawable, public Animator
{
public:
	StateAnimator()
	{
		updateTexture();
	}

	StateAnimator(const std::string& path, float fps)
		: Animator(path, fps)
	{
		updateTexture();
	}

	StateAnimator(const Animation& animation)
	{
		Animator::add(animation);
		updateTexture();
	}

	StateAnimator(const std::vector<Animation>& animations)
	{
		for (size_t i = 0; i < animations.size(); i++)
			Animator::add(animations[i]);
		updateTexture();
	}

	sf::Sprite& getSprite() { return sprite; }
	const sf::Sprite& getSprite() const { return sprite; }

	void update()
	{
		Animator::update();
		updateTexture();
	}

	virtual void set(unsigned state) override
	{
		Animator::set(state);
		updateTexture();
	}

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(sprite, states);
	}

private:
	void updateTexture()
	{
		sprite.setTexture(Animator::operator->()->getTexture());
	}

	sf::Sprite sprite;
};