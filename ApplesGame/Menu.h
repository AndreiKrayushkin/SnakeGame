#pragma once
#include "SFML/Graphics.hpp"
#include "Text.h"
#include <list>
#include <functional>


namespace SnakeGame
{
	struct MenuItem
	{
		sf::Text text;
		sf::Text hintText; 
		Orientation childrenOrientation = Orientation::Vertical;
		Alignment childrenAlignment = Alignment::Min;
		float childrenSpacing;

		sf::Color selectedColor = sf::Color::Yellow;
		sf::Color deselectedColor = sf::Color::White;

		bool isEnabled = true;
		std::vector<MenuItem> childrens;

		std::function<void(MenuItem& item)> onPressCallback;

		MenuItem* parent = nullptr;
	};

	class Menu
	{
	public:
		void initMenu(const MenuItem& item);

		void updateMenu(float deltaTime);

		void drawMenu(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin);

		void pressOnSelectedItem();
		void goBack();	
		
		void switchToPreviousMenuItem();
		void switchToNextMenuItem();

		MenuItem& getCurrentContext();

	private:
		void initMenuItem(MenuItem& item);
		void selectMenuItem(MenuItem& item);

	private:
		MenuItem rootItem;
		MenuItem* selectedItem = nullptr;
	};
}
