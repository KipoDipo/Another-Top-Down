#pragma once
#include "../Animator.h"

class GenericAnimator : public Animator
{
public:
	GenericAnimator()
		: playOnce(false)
	{
	}

	GenericAnimator(const std::string& path, float fps, bool playOnce = false)
		: playOnce(playOnce)
	{
		Animator::add(path, fps);
	}

	// Inherited via Animator
	virtual void update() override
	{
		if (playOnce && Animator::operator->()->getCurrentFrame() + 1 == Animator::operator->()->getLength())
			return;
		
		Animator::update();
	}
private:
	bool playOnce;
};