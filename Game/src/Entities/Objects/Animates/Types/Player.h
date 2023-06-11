#pragma once
#include "../Animate.h"
#include <Animation/Types/RandomAnimator.h>

class Enemy;
class Solid;
class Attack;
enum class Orientation;

class Player : public Animate
{
public:
	Player();
	Player(const Player& other);
	Player& operator=(const Player& other) = delete;
	Player(sf::Vector2f position, float speed, const AnimateAnimator& animations, const RandomAnimator& deathParticlesAnimator, const SingleAnimator& atkAnimations, Level* level);
	
	// Inherited via Animate
	virtual void update() override;	

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void copy(const Player& player);

	void checkInterractions(Enemy& enemy);

	// Inherited via Animate
	void movement(Orientation orientation) override;
	
	std::unique_ptr<Attack> attack;
};