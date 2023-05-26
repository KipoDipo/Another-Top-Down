#pragma once
#include "../Animator.h"

class AnimateAnimator : public Animator
{
public:
	enum State 
	{
		DOWN,
		UP,
		LEFT,
		RIGHT,
		SLEEP
	};

	AnimateAnimator()
		: state(DOWN)
	{
	}

	AnimateAnimator(const std::string& single, float fps)
		: state(DOWN)
	{
		Animator::add(single, fps);
		Animator::set(0);
	}

	AnimateAnimator(const std::string& up, const std::string& down, const std::string& left, const std::string& right, const std::string& sleep, float fps)
		: state(DOWN)
	{
		Animator::add(down,		fps);
		Animator::add(up,		fps);
		Animator::add(left,		fps);
		Animator::add(right,	fps);
		Animator::add(sleep,	fps);

		Animator::set(0);
	}

	void setState(State state)
	{
		if (this->state == state)
			return;

		this->state = state;
		switch (state)
		{
		case AnimateAnimator::DOWN:
			Animator::set(0);
			break;
		case AnimateAnimator::UP:
			Animator::set(1);
			break;
		case AnimateAnimator::LEFT:
			Animator::set(2);
			break;
		case AnimateAnimator::RIGHT:
			Animator::set(3);
			break;
		case AnimateAnimator::SLEEP:
			Animator::set(4);
			break;
		default:
			break;
		}
	}

private:
	State state;
};