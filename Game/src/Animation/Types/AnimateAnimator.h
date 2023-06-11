#pragma once
#include "StateAnimator.h"

class AnimateAnimator : public StateAnimator
{
public:
	enum class State : unsigned
	{
		DOWN,
		UP,
		LEFT,
		RIGHT,
		SLEEP
	};

	AnimateAnimator()
		: state(State::DOWN)
	{
	}

	AnimateAnimator(const std::string& single, float fps)
		: AnimateAnimator(single, single, single, single, single, fps)
	{
	}

	AnimateAnimator(const std::string& up, const std::string& down, const std::string& left, const std::string& right, const std::string& sleep, float fps)
		: StateAnimator({
			Animator::load(down,	fps),
			Animator::load(up,		fps),
			Animator::load(left,	fps),
			Animator::load(right,	fps),
			Animator::load(sleep,	fps)
		})
	{
		set(State::DOWN);
	}

	void set(State state)
	{
		if (this->state == state)
			return;

		this->state = state;
		StateAnimator::set((unsigned)this->state);
	}

private:
	State state;
};