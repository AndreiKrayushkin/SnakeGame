#pragma once
#include <list>
#include <array>
#include "SFML/Graphics.hpp"

namespace SnakeGame
{
	enum class SnakeDirection
	{
		Up = 0,
		Right,
		Down,
		Left
	};

	enum class SnakePart : uint8_t
	{
		Head = 0,
		Body,
		BodyBend,
		Tail,
		Count
	};

	class Snake
	{
	public:
		void loadTextures();
		void initSnake();
		void drawSnake(sf::RenderWindow& window);
		void moveSnake(float timeDelta);
		void updateDirections(SnakeDirection newDirection);
		void growSnake();
		bool checkSnakeCollisionWithHimself();
		bool hasSnakeCollisionWithRect(const sf::FloatRect& rect);

		const std::list<sf::Sprite>& getBody() const { return body; }
		const std::list<sf::Sprite>::iterator& getHead() const { return head; }
		const sf::Vector2f& getPosition() const { return sprite.getPosition(); }
		const sf::FloatRect& getRect() const { return sprite.getGlobalBounds(); }

	protected:
		sf::Sprite sprite;
		sf::Texture texture;

	private:
		void setHeadSprite(std::list<sf::Sprite>::iterator it);
		void setTailSprite(std::list<sf::Sprite>::iterator it);
		sf::Sprite getAngleElement(SnakeGame::SnakeDirection oldDirection, SnakeGame::SnakeDirection newDirection);
		sf::Vector2f getDirectionVector(SnakeDirection direction);
		void setBendRotation(sf::Sprite& segment, SnakeDirection from, SnakeDirection to);
		void setTailRotation(sf::Sprite& tail, SnakeDirection direciton);

	private:
		std::list<sf::Sprite> body;
		std::list<sf::Sprite>::iterator head;
		std::list<sf::Sprite>::iterator tail;

		float speed = 0.f;

		SnakeDirection direction = SnakeDirection::Up;
		SnakeDirection prevDirection = SnakeDirection::Up;

		std::array<sf::Texture, (size_t)SnakePart::Count> textures;
	};
}