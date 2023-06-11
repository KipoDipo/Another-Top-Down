#include "Level.h"
#include "Utilities/Utils.h"
#include "Entities/All.h"
#include <Particles/Particle.h>

std::unique_ptr<Player> Level::player(nullptr);

Level::Level()
	: hostiles(), solids(), grounds()
{
	//solids.reserve(2048);
	//grounds.reserve(2048);
	//decorations.reserve(2048);
	//hostiles.reserve(2048);
}

void Level::setPlayer(sf::Vector2f position, float speed, const AnimateAnimator& animator, const RandomAnimator& deathParticlesAnimator, const SingleAnimator& atkAnimator)
{
	player = std::make_unique<Player>(position, speed, animator, deathParticlesAnimator, atkAnimator, this);
}

void Level::addHostile(sf::Vector2f position, float speed, const AnimateAnimator& animations, const RandomAnimator& deathParticlesAnimator)
{
	hostiles.push_back(std::make_unique<Enemy>(position, speed, animations, deathParticlesAnimator, this));
}

void Level::addSolid(sf::Vector2f position, const BinaryAnimator& animations)
{
	solids.push_back(std::make_unique<Inanimate>(position, animations));
}

void Level::addGround(sf::Vector2f position, const BinaryAnimator& animations)
{
	grounds.push_back(std::make_unique<Inanimate>(position, animations));
}

void Level::addDecoration(sf::Vector2f position, const BinaryAnimator& animations)
{
	decorations.push_back(std::make_unique<Inanimate>(position, animations));
}

void Level::addParticles(const std::vector<Particle>& particles)
{
	for (size_t i = 0; i < particles.size(); i++)
		this->particles.push_back(std::make_unique<Particle>(particles[i]));
}

void Level::create()
{
	for (size_t i = 0; i < hostiles.size(); i++)
		hostiles[i]->setTarget(player.get());
}

void Level::update()
{
	player->update();
	for (size_t i = 0; i < hostiles.size(); i++)
		hostiles[i]->update();
	for (size_t i = 0; i < grounds.size(); i++)
		grounds[i]->update();
	for (size_t i = 0; i < solids.size(); i++)
		solids[i]->update();
	for (size_t i = 0; i < decorations.size(); i++)
		decorations[i]->update();
	for (size_t i = 0; i < particles.size(); i++)
	{
		particles[i]->update();
		if (!particles[i]->isActive())
		{
			particles.erase(particles.begin() + i);
			i--;
		}
	}
}

const Player& Level::getPlayer()
{
	return *player;
}

const std::vector<std::unique_ptr<Enemy>>& Level::getHostiles() const
{
	return hostiles;
}

const std::vector<std::unique_ptr<Inanimate>>& Level::getSolids() const
{
	return solids;
}

const std::vector<std::unique_ptr<Inanimate>>& Level::getGrounds() const
{
	return grounds;
}

const std::vector<std::unique_ptr<Inanimate>>& Level::getDecorations() const
{
	return decorations;
}

const std::vector<std::unique_ptr<Particle>>& Level::getParticles() const
{
	return particles;
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (size_t i = 0; i < grounds.size(); i++)
		target.draw(*grounds[i], states);
	for (size_t i = 0; i < solids.size(); i++)
		target.draw(*solids[i], states);
	for (size_t i = 0; i < hostiles.size(); i++)
		target.draw(*hostiles[i], states);
	
	target.draw(*player, states);
	
	for (size_t i = 0; i < decorations.size(); i++)
		target.draw(*decorations[i], states);
	for (size_t i = 0; i < particles.size(); i++)
		target.draw(*particles[i], states);
}