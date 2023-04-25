#pragma once
#include <SFML/Graphics.hpp>

class Animation : public sf::Drawable
{
public:
	Animation();
	Animation(const Animation& other);
	Animation(const std::vector<sf::Texture>& frames, float switchTime);
	
	void update();
	
	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);
	void setOrigin(sf::Vector2f position);
	void setOrigin(float x, float y);
	void move(sf::Vector2f dir);
	void move(float x, float y);
	
	void setSwitchTime(float switchTime);

	sf::Vector2u getSize() const;
	sf::Vector2f getPosition() const;

	static const Animation& getNone();

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	std::vector<sf::Texture> frames;
	sf::Sprite sprite;
	float switchTime;
	size_t currentFrame;
	sf::Clock clock;

	static Animation noneAnimation;
	static Animation noneAnimationGenerator();
};