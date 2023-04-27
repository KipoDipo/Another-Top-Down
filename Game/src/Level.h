#pragma once
#include "Entities/All.h"
#include <SFML/Graphics.hpp>

class Level : public sf::Drawable
{
public:
	Level();
	Level(const Level& other);
	Level& operator=(const Level& other);
	~Level();
	
	void setPlayer(sf::Vector2f position, float speed);
	void setPlayer(sf::Vector2f position, float speed, const Animator& animations, const Animator& atkAnimations);
	
	void addHostile(sf::Vector2f position, float speed);
	void addHostile(sf::Vector2f position, float speed, const Animator& animations);
	void addSolid(sf::Vector2f position);
	void addSolid(sf::Vector2f position, const Animator& animations);
	void addGround(sf::Vector2f position);
	void addGround(sf::Vector2f position, const Animator& animations);
	void addDecoration(sf::Vector2f position);
	void addDecoration(sf::Vector2f position, const Animator& animations);

	void create();

	void update();

	const Player& getPlayer() const;
	
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void copy(const Level& other);
	void free();

	Player* player;
	std::vector<Enemy*> hostiles;
	std::vector<Solid*> solids;
	std::vector<NonSolid*> grounds;
	std::vector<NonSolid*> decorations;
};