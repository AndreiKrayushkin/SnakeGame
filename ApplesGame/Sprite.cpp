#include "Sprite.h"
#include "GameSettings.h"


namespace SnakeGame
{
	void initSprite(sf::Sprite& sprite, float desiredWidth, float desiredHeight, const sf::Texture& texture)
	{
		sprite.setTexture(texture);
		setSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
		setSpriteSize(sprite, desiredWidth, desiredHeight);
	}

	sf::Vector2f getRandomSpritePositionInRectangle(const sf::Sprite& sprite, const sf::FloatRect& rect)
	{
		sf::Vector2f result;
		const auto spriteWidth = sprite.getGlobalBounds().width;
		const auto spriteHeight = sprite.getGlobalBounds().height;
		result.x = rand() / (float)RAND_MAX * (rect.width - 2 * spriteWidth) + rect.left + spriteWidth;
		result.y = rand() / (float)RAND_MAX * (rect.height - 2 * spriteHeight) + rect.top + spriteHeight;
		return result;
	}

	void setSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getGlobalBounds();
		sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}

	void setSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getGlobalBounds();
		sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
	}

	void setSpriteRandomPosition(sf::Sprite& sprite, const sf::FloatRect& rect, const std::list<sf::Sprite>& collection)
	{
		do {
			const auto newPosition = getRandomSpritePositionInRectangle(sprite, rect);
			sprite.setPosition(newPosition);
		} while (isFullCheckCollisions(collection.begin(), collection.end(), sprite));
	}

	bool isCheckSpriteIntersection(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
		const auto distance = sprite1.getPosition() - sprite2.getPosition();
		if (sqrtf(distance.x * distance.x + distance.y * distance.y) * 2 < sprite1.getGlobalBounds().width + sprite2.getGlobalBounds().width) {
 			return true;
		}
		return false;
	}

	sf::Vector2f getVectorBetweenSprites(const sf::Sprite& spriteFrom, const sf::Sprite& spriteTo) {
		const auto result = spriteTo.getPosition() - spriteFrom.getPosition();
		return result;
	}

	float getManhattanDistanceBetweenSprites(const sf::Sprite& spriteFrom, const sf::Sprite& spriteTo) {
		const auto result = spriteTo.getPosition() - spriteFrom.getPosition();
		return std::fabs(result.x) + std::fabs(result.y);
	}

	void drawSprite(const sf::Sprite& sprite, sf::RenderWindow& window)
	{
		window.draw(sprite);
	}
}
