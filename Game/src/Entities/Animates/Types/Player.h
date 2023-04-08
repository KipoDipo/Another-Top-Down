#pragma once
#include "../Animate.h"

class Enemy;
class Solid;
class Attack;

class Player : public Animate
{
public:
	Player();
	Player(sf::Vector2f position, float speed);
	~Player();
	
	void addEnemy(Enemy* enemy);
	void addEnemies(std::vector<Enemy>* enemies);

	void addSolid(Solid* solid);
	void addSolids(std::vector<Solid>* solids);
	
	// Inherited via Animate
	virtual void update() override;	

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	void movement(Orientation orientation = Orientation::None) override;
	
	std::vector<Enemy*> enemiesAwareOf;
	std::vector<Solid*> solids;
	Attack* attack;
	void checkInterractions(Enemy* enemy);
};