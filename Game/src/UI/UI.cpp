#include "UI.h"
#include <Utilities/DeltaTime.h>

using namespace sf;

void UI::addElement(const std::shared_ptr<UIElement>& element)
{
	elements.push_back(element);
}

void UI::update()
{
	for (size_t i = 0; i < elements.size(); i++)
		elements[i]->update();
}

void UI::draw(RenderTarget& target, RenderStates states) const
{
	sf::View original = target.getView();
	target.setView(View(FloatRect(0, 0, original.getSize().x, original.getSize().y)));

	for (size_t i = 0; i < elements.size(); i++)
		target.draw(*elements[i], states);

	target.setView(original);
}
