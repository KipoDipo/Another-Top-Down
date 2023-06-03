#pragma once
#include <Animation/Types/GenericAnimator.h>

class Particle : public sf::Drawable
{
public:
	Particle();
	Particle(const GenericAnimator& animator, sf::Vector2f location, sf::Vector2f direction, float speed, float duration);
	bool isActive() const;

	void update();

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	bool isDone;
	
	float duration;
	float speed;
	sf::Vector2f direction;
	GenericAnimator animator;

	sf::Clock clock;
};