#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../Animate.h"
#include "../../../Attacks/Types/SlashAttack.h"

class Enemy;

class Player : public Animate
{
public:
	Player();
	Player(sf::Vector2f position, float speed);
	
	void addEnemy(Enemy* enemy);
	
	void addEnemies(std::vector<Enemy>* enemies);
	
	// Inherited via Animate
	virtual void update() override;	
	void movement() override;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	std::vector<Enemy*> enemiesAwareOf;
	
	SlashAttack slashAttack;
	
	void checkInterractions(Enemy* enemy);
	
	float speed;

};