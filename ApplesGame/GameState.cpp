#include "GameState.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStatePauseMenu.h"
#include "GameStateMainMenu.h"
#include "GameStateRecords.h"

#include <assert.h>


namespace SnakeGame
{
	GameState::GameState(GameStateType type, bool isExclusivelyVisible)
		: type(type)
		, isExclusivelyVisible(isExclusivelyVisible)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			data = new GameStateMainMenuData();
			((GameStateMainMenuData*)data)->init();
			break;
		}
		case GameStateType::Playing:
		{
			data = new GameStatePlayingData();
			((GameStatePlayingData*)data)->init();
			break;
		}
		case GameStateType::GameOver:
		{
			data = new GameStateGameOverData();
			((GameStateGameOverData*)data)->init();
			break;
		}
		case GameStateType::ExitDialog:
		{
			data = new GameStatePauseMenuData();
			((GameStatePauseMenuData*)data)->init();
			break;
		}
		case GameStateType::Records:
		{
			data = new GameStateRecordsData();
			((GameStateRecordsData*)data)->init();
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	GameState::~GameState()
	{
		if (data) {
			switch (type)
			{
			case GameStateType::MainMenu:
			{
				delete ((GameStateMainMenuData*)data);
				break;
			}
			case GameStateType::Playing:
			{
				delete ((GameStatePlayingData*)data);
				break;
			}
			case GameStateType::GameOver:
			{
				delete ((GameStateGameOverData*)data);
				break;
			}
			case GameStateType::ExitDialog:
			{
				delete ((GameStatePauseMenuData*)data);
				break;
			}
			case GameStateType::Records:
			{
				delete ((GameStateRecordsData*)data);
				break;
			}
			default:
				assert(false); // We want to know if we forgot to implement new game state
				break;
			}
 			
			data = nullptr;
		}
	}

	void GameState::update(float timeDelta)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			((GameStateMainMenuData*)data)->update(timeDelta);
			break;
		}
		case GameStateType::Playing:
		{
			((GameStatePlayingData*)data)->update(timeDelta);
			break;
		}
		case GameStateType::GameOver:
		{
			((GameStateGameOverData*)data)->update(timeDelta);
			break;
		}
		case GameStateType::ExitDialog:
		{
			((GameStatePauseMenuData*)data)->update(timeDelta);
			break;
		}
		case GameStateType::Records:
		{
			((GameStateRecordsData*)data)->update(timeDelta);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	void GameState::draw(sf::RenderWindow& window)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			((GameStateMainMenuData*)data)->draw(window);
			break;
		}
		case GameStateType::Playing:
		{
			((GameStatePlayingData*)data)->draw(window);
			break;
		}
		case GameStateType::GameOver:
		{
			((GameStateGameOverData*)data)->draw(window);
			break;
		}
		case GameStateType::ExitDialog:
		{
			((GameStatePauseMenuData*)data)->draw(window);
			break;
		}
		case GameStateType::Records:
		{
			((GameStateRecordsData*)data)->draw(window);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	void GameState::handleWindowEvent(sf::Event& event)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			((GameStateMainMenuData*)data)->handleWindowEvent(event);
			break;
		}
		case GameStateType::Playing:
		{
			((GameStatePlayingData*)data)->handleWindowEvent(event);
			break;
		}
		case GameStateType::GameOver:
		{
			((GameStateGameOverData*)data)->handleWindowEvent(event);
			break;
		}
		case GameStateType::ExitDialog:
		{
			((GameStatePauseMenuData*)data)->handleWindowEvent(event);
			break;
		}
		case GameStateType::Records:
		{
			((GameStateRecordsData*)data)->handleWindowEvent(event);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}
}