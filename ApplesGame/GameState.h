#pragma once
#include <SFML/Graphics.hpp>


namespace SnakeGame
{

	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		ExitDialog,
		Records,
	};

	class GameState
	{
	public:
		GameState() = default;
		GameState(GameStateType type, bool isExclusivelyVisible);
		GameState(const GameState& state) = delete;
		GameState(GameState&& state) { operator=(std::move(state)); }

		~GameState();

		GameState& operator= (const GameState& state) = delete;
		GameState& operator= (GameState&& state) noexcept {
			type = state.type;
			data = state.data;
			isExclusivelyVisible = state.isExclusivelyVisible;
			state.data = nullptr;
			return *this;
		}

		bool isVisible() const { return isExclusivelyVisible; }

		void update(float timeDelta);
		void draw(sf::RenderWindow& window);
		void handleWindowEvent(sf::Event& event);

	private:
		GameStateType type = GameStateType::None;
		void* data = nullptr;
		bool isExclusivelyVisible = false;
	};

}