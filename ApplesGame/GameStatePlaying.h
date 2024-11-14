#pragma once
#include "SFML/Graphics.hpp"
#include "Snake.h"

namespace SnakeGame
{
	class Game;

	class GameStatePlayingData
	{
	public:
		void init();
		void handleWindowEvent(const sf::Event& event);
		void update(float timeDelta);
		void draw(sf::RenderWindow& window);

	private:
		void eatApple();

	private:
		sf::Texture appleTexture;
		sf::Texture stoneTexture;
		sf::Font font;

		Snake snake;
		sf::Sprite apple;
		std::vector<sf::Sprite> stones;

		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape background;

		int numEatenApples = 0;
	};
}
