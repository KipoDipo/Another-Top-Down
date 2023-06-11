#include "UI.h"
#include <Utilities/DeltaTime.h>

using namespace sf;

UI::UI(const std::string& pathToFont)
	: fpsCounter(pathToFont, {5, 60}),
	health (
		Vector2f{ 10, 10 }, 
		BinaryAnimator(
			"health/full/anim", 30,
			"health/full/static", 30, true
		),
		BinaryAnimator(
			"health/empty/anim", 30,
			"health/empty/static", 30, true
		)
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
