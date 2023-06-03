#pragma once
#include  "Animation.h"

class Animator : public sf::Drawable
{
public:
	Animation* operator->();
	const Animation* operator->() const;
	
	sf::Sprite& getSprite();
	const sf::Sprite& getSprite() const;

	virtual void update();

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
	Animator();
	void add(const std::string& path, float fps);
	void set(unsigned index);

private:
	static Animation load(const std::string& path, float fps);
	
	unsigned currentIndex;

	std::vector<Animation> animations;
	Animation none;

	sf::Sprite sprite;
};