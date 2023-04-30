#pragma once
#include "Animation.h"

class AnimationCollection
{
public:
	AnimationCollection() = default;

	Animation& operator[](const std::string& name);
	const Animation& operator[](const std::string& name) const;
	Animation& operator[](size_t index);
	const Animation& operator[](size_t index) const;

	void move(sf::Vector2f position);
	void move(float x, float y);
	void setOrigin(sf::Vector2f position);
	void setOrigin(float x, float y);
	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);

	void add(const std::string& fileName, float switchTime, const std::string name);
	void add(const std::string& fileName, float switchTime);

	void add(const std::string& name, const Animation& animation);

	size_t getSize() const;

	static AnimationCollection& getNone();
	static AnimationCollection noneAnimationCollectionGenerator();
	static AnimationCollection noneAnimationCollection;

private:
	static Animation load(const std::string& name, float switchTime);
	struct Dictionary
	{
		std::string name;
		Animation animation;

		Dictionary()
			: name(), animation()
		{
		}
		Dictionary(const std::string& name, const Animation& animation, int id = -1)
			: name(name), animation(animation)
		{
		}
	};

	std::vector<Dictionary> entries;
};