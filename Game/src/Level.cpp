#include "Level.h"
#include "Utilities/Utils.h"
#include "Entities/All.h"

Level::Level()
	: player(nullptr), hostiles(), solids(), grounds()
{
	solids.reserve(2048);
	grounds.reserve(2048);
	decorations.reserve(2048);
	hostiles.reserve(2048);
}

Level::Level(const Level& other)
{
	copy(other);
}

Level& Level::operator=(const Level& other)
{
	if (this != &other)
	{
		copy(other);
	}
	return *this;
}

void Level::setPlayer(sf::Vector2f position, float speed, const AnimateAnimator& animator, const GenericAnimator& deathParticlesAnimator, const GenericAnimator& atkAnimator)
{
	player = std::make_unique<Player>(position, speed, animator, deathParticlesAnimator, atkAnimator, this);
}

void Level::addHostile(sf::Vector2f position, float speed, const AnimateAnimator& animations, const GenericAnimator& deathParticlesAnimator)
{
	hostiles.push_back(std::make_shared<Enemy>(position, speed, animations, deathParticlesAnimator, this));
}

void Level::addSolid(sf::Vector2f position, const InanimateAnimator& animations)
{
	solids.push_back(std::make_shared<Inanimate>(position, animations));
}

void Level::addGround(sf::Vector2f position, const InanimateAnimator& animations)
{
	grounds.push_back(std::make_unique<Inanimate>(position, animations));
}

void Level::addDecoration(sf::Vector2f position, const InanimateAnimator& animations)
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
	player->clearCollidables();
	player->clearEnemies();
	for (size_t i = 0; i < hostiles.size(); i++)
	{
		hostiles[i]->clearCollidables();
		player->addEnemy(hostiles[i]);
		hostiles[i]->setTarget(player.get());
	}
	for (size_t i = 0; i < solids.size(); i++)
	{
		player->addCollidable(solids[i]);
		for (size_t j = 0; j < hostiles.size(); j++)
			hostiles[j]->addCollidable(solids[i]);
	}
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

const Player& Level::getPlayer() const
{
	return *player;
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

void Level::copy(const Level& other)
{
	player = std::make_unique<Player>(*other.player);
	hostiles.reserve(other.hostiles.size());
	solids.reserve(other.solids.size());
	grounds.reserve(other.grounds.size());
	decorations.reserve(other.decorations.size());
	
	for (size_t i = 0; i < other.hostiles.size(); i++)
		hostiles.push_back(std::make_shared<Enemy>(*other.hostiles[i]));

	for (size_t i = 0; i < other.solids.size(); i++)
		solids.push_back(std::make_shared<Inanimate>(*other.solids[i]));

	for (size_t i = 0; i < other.grounds.size(); i++)
		grounds.push_back(std::make_unique<Inanimate>(*other.grounds[i]));

	for (size_t i = 0; i < other.decorations.size(); i++)
		decorations.push_back(std::make_unique<Inanimate>(*other.decorations[i]));
}