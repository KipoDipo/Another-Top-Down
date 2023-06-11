#pragma once
#include "StateAnimator.h"

class BinaryAnimator : public StateAnimator
{
public:	
	BinaryAnimator() = default;

	BinaryAnimator(const std::string& single, float fps, bool playOnce = false)
		: BinaryAnimator(single, fps, single, fps, playOnce)
	{
	}

	BinaryAnimator(const std::string& active, float fps1, const std::string& inactive, float fps2, bool playOnce = false)
		: StateAnimator ({ 
			Animator::load(active,		fps1,	playOnce),
			Animator::load(inactive,	fps2,	playOnce) 
		})
	{
		setState(true);
	}

	BinaryAnimator(const Animation& active, const Animation& inactive)
		: StateAnimator({ active, inactive })
	{
		setState(true);
	}

	void setState(bool state)
	{
		this->state = state;
		StateAnimator::set(state ? 0 : 1);
	}
	bool getState() const
	{
		return state;
	}

private:
	bool state;
};