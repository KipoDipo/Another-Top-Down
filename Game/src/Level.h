#pragma once
#include <SFML/Graphics.hpp>

class Player;
class Enemy;
class Inanimate;
class Particle;
class SingleAnimator;
class AnimateAnimator;
class BinaryAnimator;
class RandomAnimator;

class Level : public sf::Drawable
{
public:
	Level();
	Level(const Level& other) = delete;
	Level& operator=(const Level& other) = delete;
	
	void setPlayer(sf::Vector2f position, float speed, const AnimateAnimator& animator, const RandomAnimator& deathParticlesAnimator, const SingleAnimator& atkAnimator);
	void addHostile(sf::Vector2f position, float speed, const AnimateAnimator& animator, const RandomAnimator& deathParticlesAnimator);
	void addSolid(sf::Vector2f position, const BinaryAnimator& animator);
	void addGround(sf::Vector2f position, const BinaryAnimator& animator);
	void addDecoration(sf::Vector2f position, const BinaryAnimator& animator);
	void addParticles(const std::vector<Particle>& particles);

	const static Player& getPlayer();
	const std::vector<std::unique_ptr<Enemy>>& getHostiles() const;
	const std::vector<std::unique_ptr<Inanimate>>& getSolids() const;
	const std::vector<std::unique_ptr<Inanimate>>& getGrounds() const;
	const std::vector<std::unique_ptr<Inanimate>>& getDecorations() const;
	const std::vector<std::unique_ptr<Particle>>& getParticles() const;
	
	void create();
	void update();
	
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	static std::unique_ptr<Player> player;
	std::vector<std::unique_ptr<Enemy>> hostiles;
	std::vector<std::unique_ptr<Inanimate>> solids;
	std::vector<std::unique_ptr<Inanimate>> grounds;
	std::vector<std::unique_ptr<Inanimate>> decorations;
	std::vector<std::unique_ptr<Particle>> particles;
};