#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "SFML/Audio.hpp"
#include "Sprite.h"
#include "GameSettings.h"
#include "GameState.h"
#include "Snake.h"

namespace SnakeGame
{
	enum class GameOptions: std::uint8_t
	{
		WithSound = 1 << 0,
		WithMusic = 1 << 1,

		Default = WithSound | WithMusic,
		Empty = 0
	};

	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	enum class GameDifficultyLevel : std::uint8_t
	{
		Simple = 1 << 0,
		HeavierThanSimple = 1 << 1,
		Medium = 1 << 2,
		LighterThanHeavy = 1 << 3,
		Heavy = 1 << 4
	};

	class Game
	{
	public:
		using RecordsTable = std::unordered_map<std::string, int>;

		Game();
		~Game();

		void handleWindowEvents(sf::RenderWindow& window);
		bool updateGame(float timeDelta); // Return false if game should be closed
		void drawGame(sf::RenderWindow& window);
		void shutdown();

		bool isEnableOptions(GameOptions option) const;
		void setOption(GameOptions option, bool value);

		bool isEnableDifficultyLevelOptions(GameDifficultyLevel difficultyLevel) const;
		void setDifficultyLevelOption(GameDifficultyLevel difficultyLevel);
		void disableDifficultyLevelOption(GameDifficultyLevel difficultyLevel);
		GameDifficultyLevel getCurrentDifficultyLevelOption() const;

		const RecordsTable& getRecordsTable() const { return recordsTable; }
		int getRecordByPlayerId(const std::string& playerId) const;
		void updateRecord(const std::string& playerId, int score);

		// Add new game state on top of the stack
		void pushState(GameStateType stateType, bool isExclusivelyVisible);

		// Remove current game state from the stack
		void popState();

		// Remove all game states from the stack and add new one
		void switchStateTo(GameStateType newState);

		void playGameOverSound();
		void playSnakeHitSound();
		void playMenuHoverSound();
		void playEnterPressedSound();
		void playBackgroundMusic();
		void stopBackgroundMusic();
		int getCounterIsEatenApple();
		int getSnakeSpeed();
		
	private:
		std::vector<GameState> stateStack;
		GameStateChangeType stateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		bool pendingGameStateIsExclusivelyVisible = false;

		GameDifficultyLevel currentDifficultyLevel = GameDifficultyLevel::Simple;

		GameOptions options = GameOptions::Default;
		RecordsTable recordsTable;

		sf::SoundBuffer gameOverSoundBuffer;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer menuHoverBuffer;

		sf::Sound gameOverSound;
		sf::Sound eatAppleSound;
		sf::Sound menuHoverSound;
		sf::Music enterPressedSound;
		sf::Music backgroundMusic;
	};
}
