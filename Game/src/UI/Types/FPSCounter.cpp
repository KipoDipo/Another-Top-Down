#include "FPSCounter.h"
#include <Utilities/DeltaTime.h>

FPSCounter::FPSCounter(const std::string& pathToFont, sf::Vector2f position)
{
	font.loadFromFile(pathToFont);
	fps.setFont(font);
	fps.setFillColor(sf::Color::White);
	fps.setCharacterSize(15);
	fps.setPosition(position);	
	const_cast<sf::Texture&>(font.getTexture(15)).setSmooth(false); // hack
}

void FPSCounter::update()
{
	if (clock.getElapsedTime().asSeconds() > 0.5f)
	{
		clock.restart();
		fps.setString("FPS: " + std::to_string((int)(sumFps / frames)));
		sumFps = 0;
		frames = 0;
	}
	else
	{
		sumFps += 1.f / DeltaTime::get();
		frames++;
	}
}

void FPSCounter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(fps);
}
