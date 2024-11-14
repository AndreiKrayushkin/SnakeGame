#include "GameStateMainMenu.h"
#include "Application.h"
#include "Game.h"
#include <assert.h>

namespace SnakeGame
{
	void GameStateMainMenuData::init()
	{
		assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));
		Game& game = Application::instance().getGame();

		MenuItem startGame;
		startGame.text.setString("Start Game");
		startGame.text.setFont(font);
		startGame.text.setCharacterSize(24);
		startGame.onPressCallback = [](MenuItem&) {
			Application::instance().getGame().switchStateTo(GameStateType::Playing);
			};

		MenuItem changeDifficultyLevel;
		changeDifficultyLevel.text.setString("Difficulty Level");
		changeDifficultyLevel.text.setFont(font);
		changeDifficultyLevel.text.setCharacterSize(24);
		changeDifficultyLevel.hintText.setString("Difficulty Level");
		changeDifficultyLevel.hintText.setFont(font);
		changeDifficultyLevel.hintText.setCharacterSize(48);
		changeDifficultyLevel.hintText.setFillColor(sf::Color::Red);
		changeDifficultyLevel.childrenOrientation = Orientation::Vertical;
		changeDifficultyLevel.childrenAlignment = Alignment::Middle;
		changeDifficultyLevel.childrenSpacing = 10.f;

		currentLevel.setString("Current difficulty level: ");
		currentLevel.setFont(font);
		currentLevel.setCharacterSize(24);

		MenuItem levelSimple;
		levelSimple.text.setString("Simple");
		levelSimple.text.setFont(font);
		levelSimple.text.setCharacterSize(24);
		bool isLevelSimple = game.isEnableDifficultyLevelOptions(GameDifficultyLevel::Simple);
		if (isLevelSimple)
		{
			currentLevel.setString("Current difficulty level: Simple");
		}
		levelSimple.onPressCallback = [&](MenuItem& item) {
			Game& game = Application::instance().getGame();
			game.disableDifficultyLevelOption(game.getCurrentDifficultyLevelOption());
			game.setDifficultyLevelOption(GameDifficultyLevel::Simple);
			currentLevel.setString("Current difficulty level: Simple");
			};

		MenuItem levelHeavierThanSimple;
		levelHeavierThanSimple.text.setString("Heavier Than Simple");
		levelHeavierThanSimple.text.setFont(font);
		levelHeavierThanSimple.text.setCharacterSize(24);
		bool isLevelHeavierThanSimple = game.isEnableDifficultyLevelOptions(GameDifficultyLevel::HeavierThanSimple);
		if (isLevelHeavierThanSimple)
		{
			currentLevel.setString("Current difficulty level: Heavier Than Simple");
		}
		levelHeavierThanSimple.onPressCallback = [&](MenuItem& item) {
			Game& game = Application::instance().getGame();
			game.disableDifficultyLevelOption(game.getCurrentDifficultyLevelOption());
			game.setDifficultyLevelOption(GameDifficultyLevel::HeavierThanSimple);
			currentLevel.setString("Current difficulty level: Heavier Than Simple");
			};

		MenuItem levelMedium;
		levelMedium.text.setString("Medium");
		levelMedium.text.setFont(font);
		levelMedium.text.setCharacterSize(24);
		bool isLevelMedium = game.isEnableDifficultyLevelOptions(GameDifficultyLevel::Medium);
		if (isLevelMedium)
		{
			currentLevel.setString("Current difficulty level: Medium");
		}
		levelMedium.onPressCallback = [&](MenuItem& item) {
			Game& game = Application::instance().getGame();
			game.disableDifficultyLevelOption(game.getCurrentDifficultyLevelOption());
			game.setDifficultyLevelOption(GameDifficultyLevel::Medium);
			currentLevel.setString("Current difficulty level: Medium");
			};

		MenuItem levelLighterThanHeavy;
		levelLighterThanHeavy.text.setString("Lighter Than Heavy");
		levelLighterThanHeavy.text.setFont(font);
		levelLighterThanHeavy.text.setCharacterSize(24);
		bool isLevelLighterThanHeavy = game.isEnableDifficultyLevelOptions(GameDifficultyLevel::LighterThanHeavy);
		if (isLevelLighterThanHeavy)
		{
			currentLevel.setString("Current difficulty level: Lighter Than Heavy");
		}
		levelLighterThanHeavy.onPressCallback = [&](MenuItem& item) {
			Game& game = Application::instance().getGame();
			game.disableDifficultyLevelOption(game.getCurrentDifficultyLevelOption());
			game.setDifficultyLevelOption(GameDifficultyLevel::LighterThanHeavy);
			currentLevel.setString("Current difficulty level: Lighter Than Heavy");
			};

		MenuItem levelHeavy;
		levelHeavy.text.setString("Heavy");
		levelHeavy.text.setFont(font);
		levelHeavy.text.setCharacterSize(24);
		bool isLevelHeavy = game.isEnableDifficultyLevelOptions(GameDifficultyLevel::Heavy);
		if (isLevelHeavy)
		{
			currentLevel.setString("Current difficulty level: Heavy");
		}
		levelHeavy.onPressCallback = [&](MenuItem& item) {
			Game& game = Application::instance().getGame();
			game.disableDifficultyLevelOption(game.getCurrentDifficultyLevelOption());
			game.setDifficultyLevelOption(GameDifficultyLevel::Heavy);
			currentLevel.setString("Current difficulty level: Heavy");
			};

		changeDifficultyLevel.childrens.push_back(levelSimple);
		changeDifficultyLevel.childrens.push_back(levelHeavierThanSimple);
		changeDifficultyLevel.childrens.push_back(levelMedium);
		changeDifficultyLevel.childrens.push_back(levelLighterThanHeavy);
		changeDifficultyLevel.childrens.push_back(levelHeavy);
		
		const bool isWithSound = Application::instance().getGame().isEnableOptions(GameOptions::WithSound);
		MenuItem optionsWithSound;
		optionsWithSound.text.setString("Sound: " + std::string(isWithSound ? "On" : "Off"));
		optionsWithSound.text.setFont(font);
		optionsWithSound.text.setCharacterSize(24);
		optionsWithSound.onPressCallback = [](MenuItem& item) {
			Game& game = Application::instance().getGame();
			bool newOptionValue = !game.isEnableOptions(GameOptions::WithSound);
			game.setOption(GameOptions::WithSound, newOptionValue);
			item.text.setString("Sound: " + std::string(newOptionValue ? "On" : "Off"));
			};

		const bool isWithMusic = Application::instance().getGame().isEnableOptions(GameOptions::WithMusic);
		MenuItem optionsWithMusic;
		optionsWithMusic.text.setString("Music: " + std::string(isWithMusic ? "On" : "Off"));
		optionsWithMusic.text.setFont(font);
		optionsWithMusic.text.setCharacterSize(24);
		optionsWithMusic.onPressCallback = [](MenuItem& item) {
			Game& game = Application::instance().getGame();
			bool newOptionValue = !game.isEnableOptions(GameOptions::WithMusic);
			game.setOption(GameOptions::WithMusic, newOptionValue);
			item.text.setString("Music: " + std::string(newOptionValue ? "On" : "Off"));
			if (newOptionValue)
			{
				game.playBackgroundMusic();
			} 
			else
			{
				game.stopBackgroundMusic();
			}
			};

		MenuItem recordsItem;
		recordsItem.text.setString("Records");
		recordsItem.text.setFont(font);
		recordsItem.text.setCharacterSize(24);
		recordsItem.onPressCallback = [](MenuItem&) {
			Application::instance().getGame().pushState(GameStateType::Records, true);
			};

		MenuItem options;
		options.text.setString("Options");
		options.text.setFont(font);
		options.text.setCharacterSize(24);
		options.hintText.setString("Options");
		options.hintText.setFont(font);
		options.hintText.setCharacterSize(48);
		options.hintText.setFillColor(sf::Color::Red);
		options.childrenOrientation = Orientation::Vertical;
		options.childrenAlignment = Alignment::Middle;
		options.childrenSpacing = 10.f;
		options.childrens.push_back(optionsWithSound);
		options.childrens.push_back(optionsWithMusic);

		MenuItem yesItem;
		yesItem.text.setString("Yes");
		yesItem.text.setFont(font);
		yesItem.text.setCharacterSize(24);
		yesItem.onPressCallback = [](MenuItem&) {
			Application::instance().getGame().switchStateTo(GameStateType::None);
			};

		MenuItem noItem;
		noItem.text.setString("No");
		noItem.text.setFont(font);
		noItem.text.setCharacterSize(24);
		noItem.onPressCallback = [this](MenuItem&) {
			menu.goBack();
			};

		MenuItem exitGameItem;
		exitGameItem.text.setString("Exit Game");
		exitGameItem.text.setFont(font);
		exitGameItem.text.setCharacterSize(24);
		exitGameItem.hintText.setString("Are you sure?");
		exitGameItem.hintText.setFont(font);
		exitGameItem.hintText.setCharacterSize(48);
		exitGameItem.hintText.setFillColor(sf::Color::Red);
		exitGameItem.childrenOrientation = Orientation::Horizontal;
		exitGameItem.childrenAlignment = Alignment::Middle;
		exitGameItem.childrenSpacing = 10.f;
		exitGameItem.childrens.push_back(yesItem);
		exitGameItem.childrens.push_back(noItem);

		MenuItem mainMenu;
		mainMenu.hintText.setString(GAME_NAME);
		mainMenu.hintText.setFont(font);
		mainMenu.hintText.setCharacterSize(48);
		mainMenu.hintText.setFillColor(sf::Color::Red);
		mainMenu.childrenOrientation = Orientation::Vertical;
		mainMenu.childrenAlignment = Alignment::Middle;
		mainMenu.childrenSpacing = 10.f;
		mainMenu.childrens.push_back(startGame);
		mainMenu.childrens.push_back(changeDifficultyLevel);
		mainMenu.childrens.push_back(recordsItem);
		mainMenu.childrens.push_back(options);
		mainMenu.childrens.push_back(exitGameItem);

		menu.initMenu(mainMenu);
	}

	void GameStateMainMenuData::handleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::B)
			{
				menu.goBack();
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				menu.pressOnSelectedItem();
			}
			
			Orientation orientation = menu.getCurrentContext().childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::W ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::A)
			{
				menu.switchToPreviousMenuItem();
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::S ||
						orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::D)
			{
				menu.switchToNextMenuItem();
			}
		}
	}

	void GameStateMainMenuData::update(float timeDelta)
	{

	}

	void GameStateMainMenuData::draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();

		sf::Text* hintText = &menu.getCurrentContext().hintText;
		hintText->setOrigin(getTextOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		currentLevel.setPosition(0.f, 0.f);
		window.draw(*hintText);
		window.draw(currentLevel);

		menu.drawMenu(window, viewSize / 2.f, { 0.5f, 0.f });
	}

}
