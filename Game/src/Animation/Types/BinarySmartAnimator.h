#pragma once
#include "BinaryAnimator.h"

class BinarySmartAnimator : public BinaryAnimator
{
public:
	BinarySmartAnimator() = default;

	BinarySmartAnimator(const std::string& active, float fps1, const std::string& inactive, float fps2, bool playOnce = false)
		: BinaryAnimator(active, fps1, inactive, fps2, playOnce), 
		isPlaying(false)
	{
	}

	BinarySmartAnimator(const std::string& single, float fps, bool playOnce = false)
		: BinaryAnimator(single, fps, playOnce),
		isPlaying(false)
	{
	}

	BinarySmartAnimator(const Animation& active, const Animation& inactive)
		: BinaryAnimator(active, inactive),
		isPlaying(false)
	{
	}

	void play()
	{
		isPlaying = true;
		BinaryAnimator::set(true);
	}

	// Inherited via Animator
	virtual void update() override
	{
		BinaryAnimator::update();
		if (isPlaying && Animator::operator->()->hasFinished())
		{
			isPlaying = false;
			BinaryAnimator::set(false);
		}
	}

private:
	bool isPlaying;
};