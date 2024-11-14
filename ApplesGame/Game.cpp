#include <assert.h>
#include <algorithm>
#include "Game.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStatePauseMenu.h"
#include "GameStateMainMenu.h"
#include "GameStateRecords.h"

namespace SnakeGame
{

	Game::Game()
	{
		recordsTable =
		{
			{"Player 1", rand() % 100},
			{"Player 2", rand() % 100 },
			{"Player 3", rand() % 100 },
			{"Player 4", rand() % 100 }
		};

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		switchStateTo(GameStateType::MainMenu);

		assert(gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Maodin204__Lose.wav"));
		assert(eatAppleSoundBuffer.loadFromFile(SOUNDS_PATH + "Owlstorm__Snake_hit.wav"));
		assert(menuHoverBuffer.loadFromFile(SOUNDS_PATH + "Theevilsocks__menu-hover.wav"));

		gameOverSound.setBuffer(gameOverSoundBuffer);
		eatAppleSound.setBuffer(eatAppleSoundBuffer);
		menuHoverSound.setBuffer(menuHoverBuffer);
		enterPressedSound.openFromFile(SOUNDS_PATH + "Timgormly__Enter.aiff");
		backgroundMusic.openFromFile(SOUNDS_PATH + "Clinthammer__Background_Music.wav");

		playBackgroundMusic();
	}

	Game::~Game()
	{
		shutdown();
	}

	void Game::handleWindowEvents(sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (stateStack.size() > 0)
			{
				stateStack.back().handleWindowEvent(event);
			}
		}
	}

	bool Game::updateGame(float timeDelta)
	{
		if (stateChangeType == GameStateChangeType::Switch)
		{
			// Shutdown all game states
			while (stateStack.size() > 0)
			{
				stateStack.pop_back();
			}
		}
		else if (stateChangeType == GameStateChangeType::Pop)
		{
			// Shutdown only current game state
			if (stateStack.size() > 0)
			{
				stateStack.pop_back();
			}
		}

		// Initialize new game state if needed
		if (pendingGameStateType != GameStateType::None)
		{
			stateStack.push_back(GameState(pendingGameStateType, pendingGameStateIsExclusivelyVisible));
		}

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;

		if (stateStack.size() > 0)
		{
			stateStack.back().update(timeDelta);
			return true;
		}

		return false;
	}

	void Game::drawGame(sf::RenderWindow& window)
	{
		if (stateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = stateStack.rbegin(); it != stateStack.rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->isVisible())
				{
					break;
				}
			}

			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				(*it)->draw(window);
			}
		}
	}

	void Game::shutdown()
	{
		while (stateStack.size() > 0)
		{
			stateStack.pop_back();
		}

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
	}

	void Game::pushState(GameStateType stateType, bool isExclusivelyVisible)
	{
		pendingGameStateType = stateType;
		pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
		stateChangeType = GameStateChangeType::Push;
	}

	void Game::popState()
	{
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		stateChangeType = GameStateChangeType::Pop;
	}

	void Game::switchStateTo(GameStateType newState)
	{
		pendingGameStateType = newState;
		pendingGameStateIsExclusivelyVisible = false;
		stateChangeType = GameStateChangeType::Switch;
	}

	void Game::playGameOverSound()
	{
		if (isEnableOptions(GameOptions::WithSound))
		{
			gameOverSound.play();
		}
	}

	void Game::playSnakeHitSound()
	{
		if (isEnableOptions(GameOptions::WithSound))
		{
			eatAppleSound.play();
		}
	}

	void Game::playMenuHoverSound()
	{
		if (isEnableOptions(GameOptions::WithSound))
		{
			menuHoverSound.play();
		}
	}

	void Game::playEnterPressedSound()
	{
		if (isEnableOptions(GameOptions::WithSound))
		{
			enterPressedSound.play();
		}
	}

	void Game::playBackgroundMusic()
	{
		if (isEnableOptions(GameOptions::WithMusic))
		{
			backgroundMusic.play();
		}
	}

	void Game::stopBackgroundMusic()
	{
		backgroundMusic.stop();
	}

	int Game::getCounterIsEatenApple()
	{
		int counter = 2;

		if (isEnableDifficultyLevelOptions(GameDifficultyLevel::Simple))
		{
			counter = 2;
		}
		if (isEnableDifficultyLevelOptions(GameDifficultyLevel::HeavierThanSimple))
		{
			counter = 4;
		}
		else if (isEnableDifficultyLevelOptions(GameDifficultyLevel::Medium))
		{
			counter = 6;
		}
		else if (isEnableDifficultyLevelOptions(GameDifficultyLevel::LighterThanHeavy))
		{
			counter = 8;
		}
		else if (isEnableDifficultyLevelOptions(GameDifficultyLevel::Heavy))
		{
			counter = 10;
		}

		return counter;
	}

	int Game::getSnakeSpeed()
	{
		int snakeSpeed = SNAKE_SPEED_DEFAULT;

		if (isEnableDifficultyLevelOptions(GameDifficultyLevel::Simple))
		{
			snakeSpeed = snakeSpeed * 1;
		}
		else if (isEnableDifficultyLevelOptions(GameDifficultyLevel::HeavierThanSimple))
		{
			snakeSpeed = snakeSpeed * 2;
		}
		else if (isEnableDifficultyLevelOptions(GameDifficultyLevel::Medium))
		{
			snakeSpeed = snakeSpeed * 3;
		}
		else if (isEnableDifficultyLevelOptions(GameDifficultyLevel::LighterThanHeavy))
		{
			snakeSpeed = snakeSpeed * 4;
		}
		else if (isEnableDifficultyLevelOptions(GameDifficultyLevel::Heavy))
		{
			snakeSpeed = snakeSpeed * 5;
		}

		return snakeSpeed;
	}

	bool Game::isEnableOptions(GameOptions option) const
	{
		const bool isEnable = ((std::uint8_t)options & (std::uint8_t)option) != (std::uint8_t)GameOptions::Empty;
		return isEnable;
	}

	void Game::setOption(GameOptions option, bool value)
	{
		if (value) {
			options = (GameOptions)((std::uint8_t)options | (std::uint8_t)option);
		}
		else {
			options = (GameOptions)((std::uint8_t)options & ~(std::uint8_t)option);
		}
	}

	bool Game::isEnableDifficultyLevelOptions(GameDifficultyLevel difficultyLevel) const
	{
		const bool isEnable = ((std::uint8_t)currentDifficultyLevel & (std::uint8_t)difficultyLevel);
		return isEnable;
	}

	void Game::setDifficultyLevelOption(GameDifficultyLevel difficultyLevel)
	{
		currentDifficultyLevel = (GameDifficultyLevel)((std::uint8_t)currentDifficultyLevel | (std::uint8_t)difficultyLevel);
	}

	void Game::disableDifficultyLevelOption(GameDifficultyLevel difficultyLevel)
	{
		currentDifficultyLevel = (GameDifficultyLevel)((std::uint8_t)currentDifficultyLevel & ~(std::uint8_t)difficultyLevel);
	}

	GameDifficultyLevel Game::getCurrentDifficultyLevelOption() const
	{
		return currentDifficultyLevel;
	}

	int Game::getRecordByPlayerId(const std::string& playerId) const
	{
		auto it = recordsTable.find(playerId);
		return it == recordsTable.end() ? 0 : it->second;
	}

	void Game::updateRecord(const std::string& playerId, int score)
	{
		recordsTable[playerId] = std::max(recordsTable[playerId], score);
	}
}
