#include "AnimationCollection.h"
#include "../Utilities/Paths.h"
#include "../Utilities/ConsoleColors.h"
#include <fstream>


Animation AnimationCollection::load(const std::string& name, float switchTime)
{
	std::vector<sf::Texture>* frames = new std::vector<sf::Texture>();

	sf::Texture buffer;
	std::ifstream checkFile;
	for (size_t i = 0;; i++)
	{
		std::string fullPath = Paths::textures + name + std::to_string(i) + ".png";
		checkFile.open(fullPath);
		if (!checkFile)
		{
			if (i == 0)
			{
				std::string lastResortPath = Paths::textures + name + ".png";
				checkFile.open(lastResortPath);
				if (!checkFile)
				{
					printf("%s couldn't load %s (%s)\n", ConsoleColors::redFlag, name.c_str(), lastResortPath.c_str());
					delete frames;
					return Animation::getNone();
				}
				buffer.loadFromFile(lastResortPath);
				frames->push_back(buffer);
				printf("%s loaded single %s (%s)\n", ConsoleColors::greenFlag, name.c_str(), lastResortPath.c_str());
				break;
			}
			else
			{
				printf("%s loaded animation %s (%s%sX.png) [%d frames]\n", ConsoleColors::greenFlag, name.c_str(), Paths::textures, name.c_str(), i);
				break;
			}
		}
		checkFile.close();
		buffer.loadFromFile(fullPath);
		frames->push_back(buffer);
	}
	return Animation(frames, switchTime);
}

Animation& AnimationCollection::operator[](const std::string& name)
{
	for (size_t i = 0; i < entries.size(); i++)
		if (entries[i].name == name)
			return entries[i].animation;
	printf("%s couldn't get \"%s\"\n", ConsoleColors::yellowFlag, name.c_str());
	return Animation::getNone();
}
Animation& AnimationCollection::operator[](int index)
{
	return entries[index].animation;
}

const Animation& AnimationCollection::operator[](const std::string& name) const
{
	for (size_t i = 0; i < entries.size(); i++)
		if (entries[i].name == name)
			return entries[i].animation;
	printf("%s couldn't get \"%s\"\n", ConsoleColors::yellowFlag, name.c_str());
	return Animation::getNone();
}
const Animation& AnimationCollection::operator[](int index) const
{
	return entries[index].animation;
}

void AnimationCollection::move(sf::Vector2f position)
{
	for (size_t i = 0; i < entries.size(); i++)
		entries[i].animation.move(position);
}

void AnimationCollection::move(float x, float y)
{
	for (size_t i = 0; i < entries.size(); i++)
		entries[i].animation.move(x, y);
}

void AnimationCollection::setOrigin(sf::Vector2f origin)
{
	for (size_t i = 0; i < entries.size(); i++)
		entries[i].animation.setOrigin(origin);
}

void AnimationCollection::setOrigin(float x, float y)
{
	for (size_t i = 0; i < entries.size(); i++)
		entries[i].animation.move(x, y);
}

void AnimationCollection::setPosition(sf::Vector2f position)
{
	for (size_t i = 0; i < entries.size(); i++)
		entries[i].animation.setPosition(position);
}

void AnimationCollection::setPosition(float x, float y)
{
	for (size_t i = 0; i < entries.size(); i++)
		entries[i].animation.setPosition(x, y);
}

void AnimationCollection::add(const std::string& fileName, float switchTime, const std::string name)
{
	entries.push_back(Dictionary(name, load(fileName, switchTime)));
}

void AnimationCollection::add(const std::string& fileName, float switchTime)
{
	entries.push_back(Dictionary(fileName, load(fileName, switchTime)));
}

void AnimationCollection::add(const std::string& name, const Animation& animation)
{
	entries.push_back(Dictionary(name, animation));
}

size_t AnimationCollection::getSize() const
{
	return entries.size();
}

AnimationCollection AnimationCollection::noneAnimationCollection = noneAnimationCollectionGenerator();

AnimationCollection& AnimationCollection::getNone()
{
	return noneAnimationCollection;
}

AnimationCollection AnimationCollection::noneAnimationCollectionGenerator()
{
	AnimationCollection none;
	none.add("none", Animation::getNone());
	return none;
}
