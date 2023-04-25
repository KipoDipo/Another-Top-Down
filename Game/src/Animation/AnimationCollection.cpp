#include "AnimationCollection.h"
#include "../Utilities/Paths.h"
#include "../Utilities/ConsoleColors.h"
#include <fstream>


Animation AnimationCollection::load(const std::string& name, float switchTime)
{
	std::vector<sf::Texture> frames;

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
					return Animation::getNone();
				}

				buffer.loadFromFile(lastResortPath);
				frames.push_back(buffer);
				printf("%s loaded single %s (%s)\n", ConsoleColors::greenFlag, name.c_str(), lastResortPath.c_str());
				break;
			}
			else
			{
				printf("%s loaded animation %s (%s%sX.png)\n", ConsoleColors::greenFlag, name.c_str(), Paths::textures, name.c_str());
				break;
			}
		}
		checkFile.close();
		buffer.loadFromFile(fullPath);
		frames.push_back(buffer);
	}
	return Animation(frames, switchTime);
}


const Animation& AnimationCollection::get(const std::string& name) const
{
	for (size_t i = 0; i < entries.size(); i++)
		if (entries[i].name == name)
			return entries[i].animation;
	return Animation::getNone();
}

const Animation& AnimationCollection::get(int id) const
{
	for (size_t i = 0; i < entries.size(); i++)
		if (entries[i].id == id)
			return entries[i].animation;
	return Animation::getNone();
}

void AnimationCollection::add(const std::string& fileName, float switchTime, const std::string name)
{
	entries.push_back(Dictionary(name, load(fileName, switchTime)));
}

void AnimationCollection::add(const std::string& fileName, float switchTime)
{
	entries.push_back(Dictionary(fileName, load(fileName, switchTime)));
}

void AnimationCollection::add(const std::string& fileName, float switchTime, int id)
{
	entries.push_back(Dictionary(fileName, load(fileName, switchTime), id));
}
