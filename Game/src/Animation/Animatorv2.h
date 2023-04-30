#pragma once
#include  "Animation.h"

class Animatorv2
{
public:
	Animatorv2();
	Animatorv2(const Animatorv2& other);
	Animatorv2& operator=(const Animatorv2& other);

	void add(const std::string& path, float delay);
	void set(const std::string& path);
	void update();

private:
	Animation load(const std::string& path, float delay);
	
	Animation none;

	std::map<std::string, Animation> animations;
	Animation* current;
};