#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation();
	Animation(std::shared_ptr<std::vector<sf::Texture>> frames, float fps, bool playOnce = false);
	
	void update();
	void reset();
	
	void setFPS(float fps);

	unsigned getCurrentFrame() const;
	size_t getLength() const;
	bool hasFinished() const;

	static Animation& getNone();

	const sf::Texture& getTexture() const;

private:
	std::shared_ptr<std::vector<sf::Texture>> frames;
	float switchTime;
	unsigned currentFrame;
	sf::Clock clock;

	bool playOnce;
	bool isDone;


	static Animation noneAnimationGenerator();
	static Animation noneAnimation;
};