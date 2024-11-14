#include "GameStatePauseMenu.h"
#include "Application.h"
#include "Game.h"
#include <assert.h>

namespace SnakeGame
{
	void GameStatePauseMenuData::init()
	{
		assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		background.setFillColor(sf::Color(0, 0, 0, 128));

		titleText.setString("Pause");
		titleText.setFont(font);
		titleText.setCharacterSize(48);
		titleText.setFillColor(sf::Color::Red);

		MenuItem resumeItem;
		resumeItem.text.setString("Return to game");
		resumeItem.text.setFont(font);
		resumeItem.text.setCharacterSize(24);
		resumeItem.onPressCallback = [](MenuItem&) {
			Application::instance().getGame().popState();
			};

		MenuItem exitItem;
		exitItem.text.setString("Exit to main menu");
		exitItem.text.setFont(font);
		exitItem.text.setCharacterSize(24);
		exitItem.onPressCallback = [](MenuItem&) {
			Application::instance().getGame().switchStateTo(GameStateType::MainMenu);
			};

		MenuItem pauseMenu;
		pauseMenu.childrenOrientation = Orientation::Vertical;
		pauseMenu.childrenAlignment = Alignment::Middle;
		pauseMenu.childrens.push_back(resumeItem);
		pauseMenu.childrens.push_back(exitItem);

		menu.initMenu(pauseMenu);
	}

	void GameStatePauseMenuData::handleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::instance().getGame().popState();
			}

			if (event.key.code == sf::Keyboard::Enter)
			{
				menu.pressOnSelectedItem();
			}

			Orientation orientation = menu.getCurrentContext().childrenOrientation;
			if (event.key.code == sf::Keyboard::Up)
			{
				Application::instance().getGame().playMenuHoverSound();
				menu.switchToPreviousMenuItem();
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				Application::instance().getGame().playMenuHoverSound();
				menu.switchToNextMenuItem();
			}
		}
	}

	void GameStatePauseMenuData::update(float timeDelta)
	{

	}

	void GameStatePauseMenuData::draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();
		
		background.setSize(viewSize);
		window.draw(background);

		titleText.setOrigin(getTextOrigin(titleText, { 0.5f, 0.f }));
		titleText.setPosition(viewSize.x / 2.f, 100);
		window.draw(titleText);

		menu.drawMenu(window, window.getView().getCenter(), { 0.5f, 0.f });
	}

}
