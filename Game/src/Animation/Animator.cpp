#include "Animator.h"
#include <Utilities/Paths.h>
#include <Utilities/ConsoleColors.h>
#include <fstream>

//#define NO_ANIM

Animator::Animator()
	: isEmpty(true), animations({Animation::getNone()}), currentAnimation(0)
{
}

Animator::Animator(const std::string& path, float fps)
	: isEmpty(false), animations({ load(path, fps) }), currentAnimation(0)
{
}

Animator::Animator(const std::vector<Animation>& animations)
	: isEmpty(false), animations({}), currentAnimation(0)
{
	for (size_t i = 0; i < animations.size(); i++)
		add(animations[i]);
}

Animation Animator::load(const std::string& path, float fps, bool playOnce)
{
	std::shared_ptr<std::vector<sf::Texture>> frames = std::make_shared<std::vector<sf::Texture>>();

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
					return Animation::getNone();
				}
				buffer.loadFromFile(lastResortPath);
				frames->push_back(buffer);
				printf("%s loaded single %s (%s)\n", ConsoleColors::greenFlag, path.c_str(), lastResortPath.c_str());
				break;
			}
			else
			{
				printf("%s loaded animation %s (%s%sX.png) [%d frames]\n", ConsoleColors::greenFlag, path.c_str(), Paths::textures.c_str(), path.c_str(), i);
				break;
			}
		}
		checkFile.close();
		buffer.loadFromFile(fullPath);
		frames->push_back(buffer);
#ifdef NO_ANIM
		printf("%s loaded animation %s (%s%s0.png) [NO_ANIM]\n", ConsoleColors::greenFlag, path.c_str(), Paths::textures.c_str(), path.c_str());
		break;
#endif
	}
	return Animation(frames, fps, playOnce);
}

void Animator::add(const std::string& path, float fps, bool playOnce)
{
	if (isEmpty)
	{
		animations[0] = load(path, fps, playOnce);
		isEmpty = false;
		return;
	}

	animations.push_back(load(path, fps, playOnce));
}

void Animator::add(const Animation& animation)
{
	if (isEmpty)
	{
		animations[0] = animation;
		isEmpty = false;
		return;
	}

	animations.push_back(animation);
}

void Animator::set(unsigned index)
{
	if (index >= animations.size())
		throw std::out_of_range("Animator::set - index out of range");
	currentAnimation = index;
	animations[currentAnimation].reset();
}

Animation* Animator::operator->()
{
	return &animations[currentAnimation];
}

const Animation* Animator::operator->() const
{
	return &animations[currentAnimation];
}

const Animation& Animator::operator[](size_t index) const
{
	return animations[index];
}

Animation& Animator::operator[](size_t index)
{
	return animations[index];
}

size_t Animator::size() const
{
	return animations.size();;
}

void Animator::update()
{
	animations[currentAnimation].update();
}