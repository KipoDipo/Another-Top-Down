#pragma once
#include "StateAnimator.h"
#include "SingleAnimator.h"
#include <Utilities/Utils.h>

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
		return Animator::operator[](Utils::random((int)Animator::size()));
	}
};