#include "Animator.h"
#include <Utilities/Paths.h>
#include <Utilities/ConsoleColors.h>
#include <fstream>

//#define NO_ANIM

Animator::Animator()
	: none(Animation::getNone()), sprite(none.getTexture()), currentAnimation(0)
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
	if (animations.size() == 1)
		sprite.setTexture(animations[0].getTexture());
}

void Animator::set(unsigned index)
{
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

sf::Sprite& Animator::getSprite()
{
	return sprite;
}

const sf::Sprite& Animator::getSprite() const
{
	return sprite;
}

void Animator::update()
{
	animations[currentAnimation].update();
	sprite.setTexture(animations[currentAnimation].getTexture());
}

void Animator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}
