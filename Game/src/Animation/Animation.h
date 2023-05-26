#pragma once
#include <SFML/Graphics.hpp>

class Animation : public sf::Drawable
{
public:
	Animation();
	Animation(std::vector<sf::Texture>* frames, float fps);
	
	void update();
	void reset();
	
	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);
	void setOrigin(sf::Vector2f origin);
	void setOrigin(float x, float y);
	void move(sf::Vector2f dir);
	void move(float x, float y);
	
	void setFPS(float fps);

	unsigned getCurrentFrame() const;

	sf::Vector2u getSize() const;
	sf::Vector2f getPosition() const;


	static Animation& getNone();

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
private:
	std::shared_ptr<std::vector<sf::Texture>> frames;
	sf::Sprite sprite;
	float switchTime;
	unsigned currentFrame;
	sf::Clock clock;

	static Animation noneAnimationGenerator();
	static Animation noneAnimation;
};