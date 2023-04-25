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

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	std::vector<sf::Texture> frames;
	sf::Sprite sprite;
	float switchTime;
	size_t currentFrame;
	sf::Clock clock;
};

class Animations
{
public:
	Animations() = default;
	
	const Animation& get(const std::string& name) const;
	const Animation& get(int id) const;
	static const Animation& getNone();

	void add(const std::string& fileName, float switchTime, const std::string name);
	void add(const std::string& fileName, float switchTime);
	void add(const std::string& fileName, float switchTime, int id);

private:
	static Animation load(const std::string& name, float switchTime);
	struct Dictionary
	{
		int id;
		std::string name;
		Animation animation;

		Dictionary()
			: name(), animation(), id(-1)
		{	
		}
		Dictionary(std::string name, Animation animation, int id = -1)
			: name(name), animation(animation), id(id)
		{
		}
	};
	
	std::vector<Dictionary> entries;
	static Animation noneAnimation;
	static Animation noneAnimationGenerator();
};