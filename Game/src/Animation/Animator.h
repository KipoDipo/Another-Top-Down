#pragma once
#include  "Animation.h"

class Animator
{
public:
	//using path_fps = std::pair<std::string, float>;

	Animator();
	Animator(const std::string& path, float fps);
	Animator(const std::vector<Animation>& animations);

	virtual ~Animator() = default;

	Animation* operator->();
	const Animation* operator->() const;

	const Animation& operator[](size_t index) const;
	Animation& operator[](size_t index);

	size_t size() const;
	
	virtual void update();

	static Animation load(const std::string& path, float fps, bool playOnce = false);
protected:
	void add(const std::string& path, float fps, bool playOnce = true);
	void add(const Animation& animation);
	virtual void set(unsigned index);

private:
	std::vector<Animation> animations;
	unsigned currentAnimation;
	
	bool isEmpty;
};