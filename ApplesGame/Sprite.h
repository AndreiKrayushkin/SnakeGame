#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "GameSettings.h"

namespace SnakeGame
{
	void initSprite(sf::Sprite& sprite, float desiredWidth, float desiredHeight, const sf::Texture& texture);
	void setSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
	void setSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);

	void setSpriteRandomPosition(sf::Sprite& sprite, const sf::FloatRect& rect, const std::list<sf::Sprite>& collection);

	sf::Vector2f getRandomSpritePositionInRectangle(const sf::Sprite& sprite, const sf::FloatRect& rect);
	
	sf::Vector2f getVectorBetweenSprites(const sf::Sprite& spriteFrom, const sf::Sprite& spriteTo);
	float getManhattanDistanceBetweenSprites(const sf::Sprite& spriteFrom, const sf::Sprite& spriteTo);

	bool isCheckSpriteIntersection(const sf::Sprite& sprite1, const sf::Sprite& sprite2);	
	
	template<class InputIt>
	bool isFullCheckCollisions(InputIt first, const InputIt last, const sf::Sprite& sprite) 
	{
		for (; first != last; ++first) 
		{
			if (isCheckSpriteIntersection(*first, sprite)) 
			{
				return true;
			}
		}
		return false;
	}

	void drawSprite(const sf::Sprite& sprite, sf::RenderWindow& window);
	template<class InputIt>
	void drawSprites(InputIt first, const InputIt last, sf::RenderWindow& window)
	{
		for (; first != last; ++first)
		{
			drawSprite(*first, window);
		}
	}
}
