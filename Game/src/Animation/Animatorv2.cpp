#include "Animatorv2.h"
#include "../Utilities/Paths.h"
#include "../Utilities/ConsoleColors.h"
#include <fstream>

//#define NO_ANIM

Animatorv2::Animatorv2()
	: none(Animation::getNone()), current(&none)
{
}

Animatorv2::Animatorv2(const Animatorv2& other)
	: none(Animation::getNone()), current(&none), animations(other.animations)
{
	for (size_t i = 0; i < other.animations.size(); i++)
		if (other.current == &other.animations[i])
		{
			current = &animations[i];
			break;
		}

	if (current == &none)
		printf("%s something has gone terribly wrong when using the copy ctor of Animatorv2...\n", ConsoleColors::redFlag);
}

Animatorv2& Animatorv2::operator=(const Animatorv2& other)
{
	for (size_t i = 0; i < other.animations.size(); i++)
		if (other.current == &other.animations[i])
		{
			current = &animations[i];
			break;
		}

	if (current == &none)
		printf("%s something has gone terribly wrong when using the operator= of Animatorv2...\n", ConsoleColors::redFlag);
	return *this;
}

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

void Animatorv2::add(const std::string& path, float delay)
{
	animations.push_back(load(path, delay));
	if (current == &none)
		current = &animations[animations.size() - 1];
}

void Animatorv2::set(size_t index)
{
	Animation* ref = index < animations.size() ? &animations[index] : &none;

	ref->setPosition(current->getPosition());
	current = ref;
	current->reset();
}

Animation& Animatorv2::get()
{
	return *current;
}

const Animation& Animatorv2::get() const
{
	return *current;
}

void Animatorv2::update()
{
	current->update();
}

void Animatorv2::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*current, states);
}
