#include "Animator.h"
#include "../Utilities/Paths.h"
#include "../Utilities/ConsoleColors.h"
#include <fstream>

//#define NO_ANIM

Animator::Animator()
	: none(Animation::getNone()), currentFrame(0)
{
}

Animation Animator::load(const std::string& path, float fps)
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
	return Animation(frames, fps);
}

void Animator::add(const std::string& path, float fps)
{
	animations.push_back(load(path, fps));
}

void Animator::set(unsigned frame)
{
	Animation& ref = (frame < animations.size()) 
		? animations[frame] : none;

	ref.setPosition(animations[currentFrame].getPosition());
	currentFrame = frame;
	animations[currentFrame].reset();
}

Animation& Animator::get()
{
	if (animations.size() == 0)
		return none;

	return animations[currentFrame];
}

const Animation& Animator::get() const
{
	if (animations.size() == 0)
		return none;

	return animations[currentFrame];
}

void Animator::update()
{
	animations[currentFrame].update();
}

void Animator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(animations[currentFrame], states);
}
