#pragma once
#include "../Animator.h"

class AnimateAnimation
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

	AnimateAnimation()
		: state(DOWN)
	{
	}

	AnimateAnimation(const std::string& down, const std::string& up, const std::string& left, const std::string& right, const std::string& sleep, float delay)
		: down(down), up(up), left(left), right(right), sleep(sleep), state(DOWN)
	{
		animator.add(up, delay);
		animator.add(down, delay);
		animator.add(left, delay);
		animator.add(right, delay);
		animator.add(sleep, delay);
	}

	void update()
	{
		animator.update();
	}

	const Animation& get() const
	{
		return animator.getAnimation();
	}

	void set(State state)
	{
		if (this->state == state)
			return;

		this->state = state;
		switch (state)
		{
		case AnimateAnimation::DOWN:
			animator.setAnimation(down);
			break;
		case AnimateAnimation::UP:
			animator.setAnimation(up);
			break;
		case AnimateAnimation::LEFT:
			animator.setAnimation(left);
			break;
		case AnimateAnimation::RIGHT:
			animator.setAnimation(right);
			break;
		case AnimateAnimation::SLEEP:
			animator.setAnimation(sleep);
			break;
		default:
			break;
		}
	}

private:
	State state;

	std::string down;
	std::string up;
	std::string left;
	std::string right;
	std::string sleep;

	Animator animator;
};