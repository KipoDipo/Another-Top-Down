#pragma once
#include "Animation.h"

class AnimationCollection
{
public:
	AnimationCollection() = default;

	const Animation& get(const std::string& name) const;
	const Animation& get(int id) const;

	void add(const std::string& fileName, float switchTime, const std::string name);
	void add(const std::string& fileName, float switchTime);
	void add(const std::string& fileName, float switchTime, int id);

private:
	static Animation load(const std::string& name, float switchTime);
	struct Dictionary
	{
		int id;
		std::string name;
		Animation animation;

		Dictionary()
			: name(), animation(), id(-1)
		{
		}
		Dictionary(std::string name, Animation animation, int id = -1)
			: name(name), animation(animation), id(id)
		{
		}
	};

	std::vector<Dictionary> entries;
};