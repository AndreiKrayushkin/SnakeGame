#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>

namespace SnakeGame
{
	void GameStatePlayingData::init()
	{	
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		assert(stoneTexture.loadFromFile(TEXTURES_PATH + "Rock.png"));
		assert(appleTexture.loadFromFile(TEXTURES_PATH + "Apple.png"));

		snake.loadTextures();

		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color::Green);

		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::White);

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(24);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Use arrow keys to move, P to pause");
		inputHintText.setOrigin(getTextOrigin(inputHintText, { 1.f, 0.f }));

		snake.initSnake();

		stones.resize(STONES_VALUE);
		for (sf::Sprite& stone : stones)
		{
			initSprite(stone, SONE_SIZE, SONE_SIZE, stoneTexture);
			setSpriteRandomPosition(stone, background.getGlobalBounds(), snake.getBody() );
		}

		initSprite(apple, APPLE_SIZE, APPLE_SIZE, appleTexture);
		setSpriteRandomPosition(apple, background.getGlobalBounds(), snake.getBody());
	}

	void GameStatePlayingData::handleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::P)
			{
				Application::instance().getGame().pushState(GameStateType::ExitDialog, false);
			}
		}
	}

	void GameStatePlayingData::update(float timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			snake.updateDirections(SnakeDirection::Up);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			snake.updateDirections(SnakeDirection::Right);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			snake.updateDirections(SnakeDirection::Down);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			snake.updateDirections(SnakeDirection::Left);
		}

		snake.moveSnake(timeDelta);

		if (isCheckSpriteIntersection(*snake.getHead(), apple))
		{
			Application::instance().getGame().playSnakeHitSound();

			snake.growSnake();
			eatApple();
			setSpriteRandomPosition(apple, background.getGlobalBounds(), snake.getBody());
		}

		if (isFullCheckCollisions(stones.begin(), stones.end(), *snake.getHead())
			|| snake.checkSnakeCollisionWithHimself()
			|| !snake.hasSnakeCollisionWithRect(background.getGlobalBounds()))
		{
			Application::instance().getGame().playGameOverSound();
			Application::instance().getGame().updateRecord(PLAYER_NAME, numEatenApples);

			Application::instance().getGame().switchStateTo(GameStateType::GameOver);
		}

		scoreText.setString("Apples: " + std::to_string(numEatenApples));
	}

	void GameStatePlayingData::draw(sf::RenderWindow& window)
	{
		window.draw(background);

		snake.drawSnake(window);
		drawSprites(stones.begin(), stones.end(), window);
		drawSprite(apple, window);

		scoreText.setOrigin(getTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}

	void GameStatePlayingData::eatApple()
	{
		numEatenApples = numEatenApples + Application::instance().getGame().getCounterIsEatenApple();
	}
}
