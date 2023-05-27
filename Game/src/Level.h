#pragma once
#include "Entities/All.h"
#include <SFML/Graphics.hpp>

class Level : public sf::Drawable
{
public:
	Level();
	Level(const Level& other);
	Level& operator=(const Level& other);
	
	void setPlayer(sf::Vector2f position, float speed, const AnimateAnimator& animator, const GenericAnimator& atkAnimator);
	
	void addHostile(sf::Vector2f position, float speed, const AnimateAnimator& animator);
	void addSolid(sf::Vector2f position, const InanimateAnimator& animator);
	void addGround(sf::Vector2f position, const InanimateAnimator& animator);
	void addDecoration(sf::Vector2f position, const InanimateAnimator& animator);
	void addParticles(const std::vector<Particle>& particles);

	void create();

	void update();

	const Player& getPlayer() const;
	
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void copy(const Level& other);

	std::unique_ptr<Player> player;
	std::vector<std::shared_ptr<Enemy>> hostiles;
	std::vector<std::shared_ptr<Inanimate>> solids;
	std::vector<std::unique_ptr<Inanimate>> grounds;
	std::vector<std::unique_ptr<Inanimate>> decorations;
	std::vector<std::unique_ptr<Particle>> particles;
};