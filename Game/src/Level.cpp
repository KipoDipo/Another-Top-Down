#include "Level.h"

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
		free();
		copy(other);
	}
	return *this;
}

Level::~Level()
{
	free();
}

void Level::setPlayer(sf::Vector2f position, float speed)
{
	if (!player)
		player = new Player(position, speed);
	else
	{
		player->setPosition(position);
		player->setSpeed(speed);
	}
}

void Level::setPlayer(sf::Vector2f position, float speed, const Animation& sprite, const Animation& attackSprite)
{
	if (!player)
		player = new Player(position, speed, sprite, attackSprite);
	else
	{
		player->setPosition(position);
		player->setSpeed(speed);
		//TODO player->setSprite()
	}

}

void Level::addHostile(sf::Vector2f position, float speed)
{
	hostiles.push_back(new Enemy(position, speed));
}

void Level::addHostile(sf::Vector2f position, float speed, const Animation& sprite)
{
	hostiles.push_back(new Enemy(position, sprite, speed));
}

void Level::addSolid(sf::Vector2f position)
{
	solids.push_back(new Solid(position));
}

void Level::addSolid(sf::Vector2f position, const Animation& sprite)
{
	solids.push_back(new Solid(position, sprite));
}

void Level::addGround(sf::Vector2f position)
{
	grounds.push_back(new NonSolid(position));
}

void Level::addGround(sf::Vector2f position, const Animation& sprite)
{
	grounds.push_back(new NonSolid(position, sprite));
}

void Level::addDecoration(sf::Vector2f position)
{
	decorations.push_back(new NonSolid(position));
}

void Level::addDecoration(sf::Vector2f position, const Animation& sprite)
{
	decorations.push_back(new NonSolid(position, sprite));
}

void Level::create()
{
	player->clearCollidables();
	player->clearEnemies();
	for (size_t i = 0; i < hostiles.size(); i++)
	{
		hostiles[i]->clearCollidables();
		player->addEnemy(hostiles[i]);
		hostiles[i]->setTarget(player);
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
	for (size_t i = 0; i < solids.size(); i++)
		solids[i]->update();
	for (size_t i = 0; i < decorations.size(); i++)
		decorations[i]->update();
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
}

void Level::copy(const Level& other)
{
	player = new Player(*other.player);
	hostiles.reserve(other.hostiles.size());
	solids.reserve(other.solids.size());
	grounds.reserve(other.grounds.size());
	decorations.reserve(other.decorations.size());
	
	for (size_t i = 0; i < other.hostiles.size(); i++)
		hostiles.push_back(new Enemy(*other.hostiles[i]));
	for (size_t i = 0; i < other.solids.size(); i++)
		solids.push_back(new Solid(*other.solids[i]));
	for (size_t i = 0; i < other.grounds.size(); i++)
		grounds.push_back(new NonSolid(*other.grounds[i]));
	for (size_t i = 0; i < other.decorations.size(); i++)
		decorations.push_back(new NonSolid(*other.decorations[i]));
}

void Level::free()
{
	delete player;
	for (size_t i = 0; i < hostiles.size(); i++)
		delete hostiles[i];
	for (size_t i = 0; i < solids.size(); i++)
		delete solids[i];
	for (size_t i = 0; i < grounds.size(); i++)
		delete grounds[i];
	for (size_t i = 0; i < decorations.size(); i++)
		delete decorations[i];
}
