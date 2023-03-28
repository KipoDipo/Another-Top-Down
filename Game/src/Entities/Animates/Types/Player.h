#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../Animate.h"

class Enemy;
class Solid;
class SlashAttack;

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
	void movement() override;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	std::vector<Enemy*> enemiesAwareOf;
	std::vector<Solid*> solids;
	SlashAttack* slashAttack;
	
	void checkInterractions(Enemy* enemy);
	
	float speed;

};