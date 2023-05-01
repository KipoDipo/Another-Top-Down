#pragma once
#include  "Animation.h"

class Animatorv2 : public sf::Drawable
{
public:
	Animatorv2();
	Animatorv2(const Animatorv2& other);
	Animatorv2& operator=(const Animatorv2& other);

	Animation& get();
	const Animation& get() const;
	
	void update();

	void add(const std::string& path, float delay);
	void set(size_t index);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	static Animation load(const std::string& path, float delay);
	
	Animation none;

	std::vector<Animation> animations;
	Animation* current;

};