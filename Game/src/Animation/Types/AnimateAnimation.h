#pragma once
#include "../Animatorv2.h"

class AnimateAnimation : public Animatorv2
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

	AnimateAnimation(const std::string& single, float delay)
		: state(DOWN)
	{
		Animatorv2::add(single, delay);
		Animatorv2::set(0);
	}

	AnimateAnimation(const std::string& up, const std::string& down, const std::string& left, const std::string& right, const std::string& sleep, float delay)
		: state(DOWN)
	{
		Animatorv2::add(down,	 delay);
		Animatorv2::add(up,		 delay);
		Animatorv2::add(left,	 delay);
		Animatorv2::add(right,	 delay);
		Animatorv2::add(sleep,	 delay);

		Animatorv2::set(0);
	}

	void set(State state)
	{
		if (this->state == state)
			return;

		this->state = state;
		switch (state)
		{
		case AnimateAnimation::DOWN:
			Animatorv2::set(0);
			break;
		case AnimateAnimation::UP:
			Animatorv2::set(1);
			break;
		case AnimateAnimation::LEFT:
			Animatorv2::set(2);
			break;
		case AnimateAnimation::RIGHT:
			Animatorv2::set(3);
			break;
		case AnimateAnimation::SLEEP:
			Animatorv2::set(4);
			break;
		default:
			break;
		}
	}

private:
	void add(const std::string& path, float delay)
	{}
	void add(const std::string& path, float delay, const std::string& name) 
	{}
	void set(const std::string& path)
	{}

	State state;
};