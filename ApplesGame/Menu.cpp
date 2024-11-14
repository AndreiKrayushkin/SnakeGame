#include <assert.h>
#include "Menu.h"
#include "Application.h"

namespace SnakeGame
{
	void Menu::initMenu(const MenuItem& item)
	{
		rootItem = item;

		initMenuItem(rootItem);
		if (!rootItem.childrens.empty()) {
			selectMenuItem(rootItem.childrens.front());
		}
	}
	
	void Menu::initMenuItem(MenuItem& item)
	{
		for (auto& child : item.childrens)
		{
			child.parent = &item;
			initMenuItem(child);
		}
	}

	void Menu::drawMenu(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin)
	{
		MenuItem& expandedItem = getCurrentContext();

		std::vector<sf::Text*> texts;
		texts.reserve(expandedItem.childrens.size());
		for (auto& child : expandedItem.childrens) {
			if (child.isEnabled) {
				texts.push_back(&child.text);
			}
		}

		drawTextList(
			window,
			texts,
			expandedItem.childrenSpacing,
			expandedItem.childrenOrientation,
			expandedItem.childrenAlignment,
			position,
			origin);
	}
	
	void Menu::pressOnSelectedItem()
	{
		if (!selectedItem) {
			return;
		}

		if (selectedItem->onPressCallback) {
			selectedItem->onPressCallback(*selectedItem);
			return;
		}

		if (!selectedItem->childrens.empty()) {
			selectMenuItem(selectedItem->childrens.front());
		}

		Application::instance().getGame().playEnterPressedSound();
	}

	void Menu::goBack()
	{
		MenuItem& parent = getCurrentContext();
		if (&parent != &rootItem) {
			selectMenuItem(parent);
		}
	}

	void Menu::switchToPreviousMenuItem()
	{
		if (!selectedItem) {
			return;
		}
		
		MenuItem* parent = selectedItem->parent;
		assert(parent);

		auto it = std::find_if(parent->childrens.begin(), parent->childrens.end(), [this](const auto& item) {
			return selectedItem == &item;
		});
		if (it != parent->childrens.begin()) {
			selectMenuItem(*std::prev(it));
		}

		Application::instance().getGame().playMenuHoverSound();
	}

	void Menu::switchToNextMenuItem()
	{
		if (!selectedItem) {
			return;
		}
		
		MenuItem* parent = selectedItem->parent;
		assert(parent);
		
		auto it = std::find_if(parent->childrens.begin(), parent->childrens.end(), [this](const auto& item) {
			return selectedItem == &item;
			});
		it = std::next(it);
		if (it != parent->childrens.end()) {
			selectMenuItem(*it);
		}

		Application::instance().getGame().playMenuHoverSound();
	}

	void Menu::selectMenuItem(MenuItem& item)
	{
		assert(&item != &rootItem);

		if (selectedItem == &item)
		{
			return;
		}

		if (!item.isEnabled)
		{
			return;
		}

		if (selectedItem)
		{
			selectedItem->text.setFillColor(selectedItem->deselectedColor);
		}

		selectedItem = &item;

		if (selectedItem)
		{
			selectedItem->text.setFillColor(selectedItem->selectedColor);
		}
	}

	MenuItem& Menu::getCurrentContext()
	{
		return selectedItem ? *(selectedItem->parent) : rootItem;
	}
}
