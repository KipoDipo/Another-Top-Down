#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation();
	Animation(std::shared_ptr<std::vector<sf::Texture>> frames, float fps);
	
	void update();
	void reset();
	
	void setFPS(float fps);

	unsigned getCurrentFrame() const;
	size_t getLength() const;

	static Animation& getNone();

	const sf::Texture& getTexture() const;

private:
	std::shared_ptr<std::vector<sf::Texture>> frames;
	float switchTime;
	unsigned currentFrame;
	sf::Clock clock;

	static Animation noneAnimationGenerator();
	static Animation noneAnimation;
};