#include "UI.h"
#include <Utilities/DeltaTime.h>

using namespace sf;

UI::UI(const std::string& pathToFont, const BinarySmartAnimator& healthBarFull, const SingleAnimator& healthBarEmpty)
	: fpsCounter(pathToFont, {5, 60}),
	health (
		Vector2f{ 10, 10 }, 
		healthBarFull,
		healthBarEmpty
	)
{
}

void UI::setPlayer(const Player& player)
{
	health.setPlayer(player);
}

void UI::update()
{
	fpsCounter.update();
	health.update();
}

void UI::draw(RenderTarget& target, RenderStates states) const
{
	sf::View original = target.getView();
	target.setView(View(FloatRect(0, 0, original.getSize().x, original.getSize().y)));

	target.draw(fpsCounter, states);
	target.draw(health, states);

	target.setView(original);
}
