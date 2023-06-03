#include "Animation.h"
#include <fstream>

Animation::Animation()
	: frames(), switchTime(), currentFrame(0), clock()
{
}

Animation::Animation(std::shared_ptr<std::vector<sf::Texture>> frames, float fps)
	: frames(frames), switchTime(1.f / fps), currentFrame(0), clock()
{
}

void Animation::update()
{
	if ((*frames).size() == 1)
		return;

	float elapsedTime = clock.getElapsedTime().asSeconds();
	
	if (elapsedTime > switchTime)
	{
		currentFrame = (currentFrame + 1) % frames->size(); // from 0 to size
		clock.restart();
	}
}

void Animation::reset()
{
	clock.restart();
	currentFrame = 0;
}

void Animation::setFPS(float fps)
{
	this->switchTime = 1.f / fps;
}

unsigned Animation::getCurrentFrame() const
{
	return currentFrame;
}

size_t Animation::getLength() const
{
	return frames->size();
}

const sf::Texture& Animation::getTexture() const
{
	return (*frames)[currentFrame];
}

Animation Animation::noneAnimationGenerator()
{
	std::shared_ptr<std::vector<sf::Texture>> noFrames = std::make_shared<std::vector<sf::Texture>>();
	sf::Texture texture;
	texture.create(50, 50);
	sf::Image img = texture.copyToImage();

	sf::Color one = sf::Color(255, 200, 80);
	sf::Color two = sf::Color(255, 80, 100);

	for (unsigned i = 0; i < 50; i++)
	{
		if (i != 0 && i % 25 == 0)
			std::swap(one, two);

		for (size_t j = 0; j < 50; j++)
		{
			if (j < 25)
				img.setPixel(j, i, one);
			else
				img.setPixel(j, i, two);
		}
	}

	texture.update(img);

	noFrames->push_back(texture);
	return Animation(noFrames, 1.f);
}

Animation Animation::noneAnimation = Animation::noneAnimationGenerator();

Animation& Animation::getNone()
{
	return noneAnimation;
}

