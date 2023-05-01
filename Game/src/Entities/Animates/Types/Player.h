#pragma once
#include "../Animate.h"

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
	Player(sf::Vector2f position, float speed, const AnimateAnimation& animations, const Animatorv2& atkAnimations);
	~Player();
	
	void addEnemy(Enemy* enemy);
	void addEnemies(std::vector<Enemy>* enemies);
	void clearEnemies();

	// Inherited via Animate
	virtual void update() override;	

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void copy(const Player& player);
	void free();

	void checkInterractions(Enemy* enemy);

	// Inherited via Animate
	void movement(Orientation orientation) override;
	
	Attack* attack;
	std::vector<Enemy*> enemies;
};