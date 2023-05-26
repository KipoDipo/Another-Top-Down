#pragma once
#include "../Animator.h"

class GenericAnimator : public Animator
{
public:
	GenericAnimator()
	{
	}

	GenericAnimator(const std::string& path, float fps)
	{
		Animator::add(path, fps);
	}
};