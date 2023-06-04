#pragma once
#include <SFML/Graphics.hpp>
#include <Particles/Particle.h>

class Player;
class Enemy;
class Inanimate;
class GenericAnimator;
class AnimateAnimator;
class InanimateAnimator;

class Level : public sf::Drawable
{
public:
	Level();
	Level(const Level& other);
	Level& operator=(const Level& other);
	
	void setPlayer(sf::Vector2f position, float speed, const AnimateAnimator& animator, const GenericAnimator& deathParticlesAnimator, const GenericAnimator& atkAnimator);
	void addHostile(sf::Vector2f position, float speed, const AnimateAnimator& animator, const GenericAnimator& deathParticlesAnimator);
	void addSolid(sf::Vector2f position, const InanimateAnimator& animator);
	void addGround(sf::Vector2f position, const InanimateAnimator& animator);
	void addDecoration(sf::Vector2f position, const InanimateAnimator& animator);
	void addParticles(const std::vector<Particle>& particles);

	const Player& getPlayer() const;
	const std::vector<std::shared_ptr<Enemy>>& getHostiles() const;
	const std::vector<std::shared_ptr<Inanimate>>& getSolids() const;
	const std::vector<std::shared_ptr<Inanimate>>& getGrounds() const;
	const std::vector<std::unique_ptr<Inanimate>>& getDecorations() const;
	const std::vector<std::unique_ptr<Particle>>& getParticles() const;
	
	void create();
	void update();
	
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void copy(const Level& other);

	std::unique_ptr<Player> player;
	std::vector<std::shared_ptr<Enemy>> hostiles;
	std::vector<std::shared_ptr<Inanimate>> solids;
	std::vector<std::shared_ptr<Inanimate>> grounds;
	std::vector<std::unique_ptr<Inanimate>> decorations;
	std::vector<std::unique_ptr<Particle>> particles;
};