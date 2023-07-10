#pragma once
#include <UI/UIElement.h>

class UI : public sf::Drawable
{
public:
	void addElement(const std::shared_ptr<UIElement>& element);

	void update();

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::vector<std::shared_ptr<UIElement>> elements;
};