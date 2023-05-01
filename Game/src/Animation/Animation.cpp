#include "../Utilities/Utils.h"
#include "Animation.h"
#include <fstream>

Animation::Animation()
	: frames(), sprite(), switchTime(), currentFrame(0), clock()
{
}

Animation::Animation(std::vector<sf::Texture>* frames, float switchTime)
	: frames(frames), switchTime(switchTime), currentFrame(0), clock()
{
	sprite = frames == nullptr ? Animation::getNone().sprite : sf::Sprite((*this->frames)[0]);
}

void Animation::update()
{
	if ((*frames).size() == 1)
		return;

	float elapsedTime = clock.getElapsedTime().asSeconds();
	
	if (elapsedTime > switchTime)
	{
		sprite.setTexture((*frames)[currentFrame]);
		currentFrame = (currentFrame + 1) % frames->size(); // from 0 to size
		clock.restart();
	}
}

void Animation::reset()
{
	clock.restart();
	currentFrame = 0;
	sprite.setTexture((*frames)[0]);
}

void Animation::setPosition(sf::Vector2f position)
{
	setPosition(position.x, position.y);
}

void Animation::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

void Animation::setOrigin(sf::Vector2f origin)
{
	setOrigin(origin.x, origin.y);
}

void Animation::setOrigin(float x, float y)
{
	sprite.setOrigin(x, y);
}

void Animation::move(sf::Vector2f dir)
{
	move(dir.x, dir.y);
}

void Animation::move(float x, float y)
{
	sprite.move(x, y);
}

void Animation::setSwitchTime(float switchTime)
{
	this->switchTime = switchTime;
}

size_t Animation::getCurrentFrame() const
{
	return currentFrame;
}

sf::Vector2u Animation::getSize() const
{
	return sprite.getTexture()->getSize();
}

sf::Vector2f Animation::getPosition() const
{
	return sprite.getPosition();
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

Animation Animation::noneAnimationGenerator()
{
	std::vector<sf::Texture>* noFrames = new std::vector<sf::Texture>();
	sf::Texture texture;
	texture.create(50, 50);
	sf::Image img = texture.copyToImage();

	sf::Color one = sf::Color(255, 200, 80);
	sf::Color two = sf::Color(255, 80, 100);

	for (size_t i = 0; i < 50; i++)
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