#pragma once
#include "../Animatorv2.h"

class InanimateAnimation : public Animatorv2
{
public:
	enum State
	{
		INACTIVE,
		ACTIVE
	};

	InanimateAnimation()
		: state(INACTIVE)
	{
	}

	InanimateAnimation(const std::string& single, float delay)
		: state(INACTIVE)
	{
		Animatorv2::add(single, delay);
		Animatorv2::set(0);
	}
	
	InanimateAnimation(const std::string& inactive, const std::string& active, float delay)
		: state(INACTIVE)
	{
		Animatorv2::add(inactive, delay);
		Animatorv2::add(active, delay);

		Animatorv2::set(0);
	}

	void set(State state)
	{
		if (this->state == state)
			return;

		this->state = state;
		switch (state)
		{
		case InanimateAnimation::INACTIVE:
			Animatorv2::set(0);
			break;
		case InanimateAnimation::ACTIVE:
			Animatorv2::set(1);
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