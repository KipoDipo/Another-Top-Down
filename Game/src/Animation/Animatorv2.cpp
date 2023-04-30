#include "Animatorv2.h"
#include "../Utilities/Paths.h"
#include "../Utilities/ConsoleColors.h"
#include <fstream>

//#define NO_ANIM

Animation Animatorv2::load(const std::string& path, float delay)
{
	std::vector<sf::Texture>* frames = new std::vector<sf::Texture>();

	sf::Texture buffer;
	std::ifstream checkFile;
	for (size_t i = 0;; i++)
	{
		std::string fullPath = Paths::textures + path + std::to_string(i) + ".png";
		checkFile.open(fullPath);
		if (!checkFile)
		{
			if (i == 0)
			{
				std::string lastResortPath = Paths::textures + path + ".png";
				checkFile.open(lastResortPath);
				if (!checkFile)
				{
					printf("%s couldn't load %s (%s)\n", ConsoleColors::redFlag, path.c_str(), lastResortPath.c_str());
					delete frames;
					return Animation::getNone();
				}
				buffer.loadFromFile(lastResortPath);
				frames->push_back(buffer);
				printf("%s loaded single %s (%s)\n", ConsoleColors::greenFlag, path.c_str(), lastResortPath.c_str());
				break;
			}
			else
			{
				printf("%s loaded animation %s (%s%sX.png) [%d frames]\n", ConsoleColors::greenFlag, path.c_str(), Paths::textures, path.c_str(), i);
				break;
			}
		}
		checkFile.close();
		buffer.loadFromFile(fullPath);
		frames->push_back(buffer);
#ifdef NO_ANIM
		printf("%s loaded animation %s (%s%s0.png) [NO_ANIM]\n", ConsoleColors::greenFlag, path.c_str(), Paths::textures, path.c_str());
		break;
#endif
	}
	return Animation(frames, delay);
}

Animatorv2::Animatorv2()
	: none(Animation::getNone()), current(&none)
{
}

void Animatorv2::add(const std::string& path, float delay)
{
	animations[path] = load(path, delay);
}

void Animatorv2::set(const std::string& path)
{
	Animation* ref;
	if (animations.count(path) != 0)	// if the animation exists
		ref = &animations[path];		// point 'ref' to that animation
	else								// otherwise
		ref = &none;					// point 'ref' to 'none'

	if (current == ref)
		return;

	ref->setPosition(current->getPosition());
	current = ref;
	current->reset();
}

void Animatorv2::update()
{
	current->update();
}
