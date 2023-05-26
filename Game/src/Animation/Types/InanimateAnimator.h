#pragma once
#include "../Animator.h"

class InanimateAnimator : public Animator
{
public:
	enum State
	{
		INACTIVE,
		ACTIVE
	};

	InanimateAnimator()
		: state(INACTIVE)
	{
	}

	InanimateAnimator(const std::string& single, float fps)
		: state(INACTIVE)
	{
		Animator::add(single, fps);
		Animator::set(0);
	}
	
	InanimateAnimator(const std::string& inactive, const std::string& active, float fps)
		: state(INACTIVE)
	{
		Animator::add(inactive, fps);
		Animator::add(active, fps);

		Animator::set(0);
	}

	void setState(State state)
	{
		if (this->state == state)
			return;

		this->state = state;
		switch (state)
		{
		case InanimateAnimator::INACTIVE:
			Animator::set(0);
			break;
		case InanimateAnimator::ACTIVE:
			Animator::set(1);
			break;
		default:
			break;
		}
	}

private:
	State state;
};