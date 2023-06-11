#pragma once
#include "StateAnimator.h"

class SingleAnimator : public StateAnimator
{
public:
	SingleAnimator() = default;

	SingleAnimator(const std::string& path, float fps, bool playOnce = false)
		: StateAnimator(Animator::load(path, fps, playOnce))
	{
	}

	SingleAnimator(const Animation& animation)
		: StateAnimator(animation)
	{
	}
};