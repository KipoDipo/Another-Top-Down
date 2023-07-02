#pragma once
#include "StateAnimator.h"
#include "SingleAnimator.h"
#include <Utilities/Random.h>

class RandomAnimator : public StateAnimator
{
public:
	RandomAnimator() = default;

	RandomAnimator(const Animation& single)
		: StateAnimator(single)
	{
	}

	RandomAnimator(const std::vector<Animation>& animations)
		: StateAnimator(animations)
	{
	}

	const Animation& roll() const
	{
		return Animator::operator[](Random::next((int)Animator::size()));
	}
};