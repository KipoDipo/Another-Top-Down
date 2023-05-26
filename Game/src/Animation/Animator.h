#pragma once
#include  "Animation.h"

class Animator : public sf::Drawable
{
public:
	Animation& get();
	const Animation& get() const;
	
	void update();

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
	Animator();
	void add(const std::string& path, float fps);
	void set(unsigned frame);

private:
	static Animation load(const std::string& path, float fps);
	
	bool valid;
	unsigned currentFrame;

	std::vector<Animation> animations;
	Animation none;
};