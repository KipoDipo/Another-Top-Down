#pragma once
#include "../Animate.h"
#include "../../../../Animation/Types/GenericAnimator.h"

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
	Player(sf::Vector2f position, float speed, const AnimateAnimator& animations, const GenericAnimator& atkAnimations);
	
	void addEnemy(std::shared_ptr<Enemy> enemy);

	void clearEnemies();

	// Inherited via Animate
	virtual void update() override;	

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void copy(const Player& player);

	void checkInterractions(std::shared_ptr<Enemy> enemy);

	// Inherited via Animate
	void movement(Orientation orientation) override;
	
	std::unique_ptr<Attack> attack;
	std::vector<std::shared_ptr<Enemy>> enemies;
};