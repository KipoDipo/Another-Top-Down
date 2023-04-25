#include "../Utilities/Textures.h"
#include "../Utilities/Utils.h"
#include "Animation.h"
#include <fstream>

Animation::Animation()
	: frames(), sprite(), switchTime(), currentFrame(0), clock()
{
}

Animation::Animation(const Animation& other)
	: frames(other.frames), switchTime(other.switchTime), currentFrame(other.currentFrame), clock(other.clock)
{
	sprite.setPosition(other.sprite.getPosition());
	sprite.setOrigin(other.sprite.getOrigin());
	sprite.setRotation(other.sprite.getRotation());
	sprite.setColor(other.sprite.getColor());
	sprite.setScale(other.sprite.getScale());
	if (frames.size() > 0)
		sprite.setTexture(frames[0]);
}

Animation::Animation(const std::vector<sf::Texture>& frames, float switchTime)
	: frames(frames), sprite(frames[0]), switchTime(switchTime), currentFrame(0), clock()
{
}

void Animation::update()
{
	float elapsedTime = clock.getElapsedTime().asSeconds();
	
	if (elapsedTime > switchTime)
	{
		if (currentFrame >= frames.size())
			currentFrame = 0;
		sprite.setTexture(frames[currentFrame++]);
		clock.restart();
	}
}

void Animation::setPosition(sf::Vector2f position)
{
	setPosition(position.x, position.y);
}

void Animation::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

void Animation::setOrigin(sf::Vector2f position)
{
	setOrigin(position.x, position.y);
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

sf::Vector2u Animation::getSize() const
{
	return sprite.getTexture()->getSize();
}

sf::Vector2f Animation::getPosition() const
{
	return sf::Vector2f();
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

Animation Animation::noneAnimationGenerator()
{
	std::vector<sf::Texture> noFrames;
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

	noFrames.push_back(texture);
	return Animation(noFrames, 1.f);
}

Animation Animation::noneAnimation = Animation::noneAnimationGenerator();

const Animation& Animation::getNone()
{
	return noneAnimation;
}