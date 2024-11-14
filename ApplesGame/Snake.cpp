#include <assert.h>
#include "Snake.h"
#include "GameSettings.h"
#include "Sprite.h"
#include "Application.h"

namespace SnakeGame
{
	void Snake::loadTextures()
	{
		assert(textures[(size_t)SnakePart::Head].loadFromFile(TEXTURES_PATH + "Head.png"));
		assert(textures[(size_t)SnakePart::Body].loadFromFile(TEXTURES_PATH + "Body.png"));
		assert(textures[(size_t)SnakePart::BodyBend].loadFromFile(TEXTURES_PATH + "BodyBend.png"));
		assert(textures[(size_t)SnakePart::Tail].loadFromFile(TEXTURES_PATH + "Tail.png"));
	}

	void Snake::initSnake()
	{
		speed = Application::instance().getGame().getSnakeSpeed();
		direction = SnakeDirection::Up;
		prevDirection = SnakeDirection::Up;

		//init head
		sf::Sprite headElement;
		initSprite(headElement, SNAKE_SIZE, SNAKE_SIZE, textures[(size_t)SnakePart::Head]);
		headElement.setPosition((float)SCREEN_WIDTH / 2.f, (float)SCREEN_HEIGHT / 2.f);
		body.push_front(headElement);

		//init tail
		sf::Sprite tailElement;
		initSprite(tailElement, SNAKE_SIZE, SNAKE_SIZE, textures[(size_t)SnakePart::Tail]);
		tailElement.setPosition((float)SCREEN_WIDTH / 2.f, (float)SCREEN_HEIGHT / 2.f + SNAKE_SIZE * (INITIAL_SNAKE_SIZE - 1));
		body.push_front(tailElement);

		head = std::prev(body.end());
		tail = body.begin();
	}

	void Snake::drawSnake(sf::RenderWindow& window)
	{
		for (auto segment = body.begin(); segment != head; ++segment)
		{
			auto nextSegment = std::next(segment);
			float width = SNAKE_SIZE, height = getManhattanDistanceBetweenSprites(*segment, *nextSegment) - SNAKE_SIZE;
			float angle = segment->getPosition().x != nextSegment->getPosition().x ? 90.f : 0.f;

			if (width > 0.f && height > 0.f) 
			{
				sf::Sprite sprite;
				initSprite(sprite, width, height, textures[(size_t)SnakeGame::SnakePart::Body]);
				auto position = (segment->getPosition() + nextSegment->getPosition()) / 2.f;
				sprite.setPosition(position);
				sprite.setRotation(angle);
				drawSprite(sprite, window);
			}
		}

		drawSprites(body.begin(), body.end(), window);
	}

	void Snake::moveSnake(float timeDelta)
	{
		float shift = speed * timeDelta;
		sf::Vector2f newDirection = getDirectionVector(direction) * shift / SNAKE_SIZE;

		auto prevHead = head;

		// new rotation
		if (prevDirection != direction)
		{
			head = body.insert(++head, *prevHead);
			setHeadSprite(head);

			*prevHead = getAngleElement(prevDirection, direction);
			prevHead->setPosition(head->getPosition());
		}

		head->setPosition(head->getPosition() + newDirection);

		auto nextTail = std::next(tail);
		auto tailDirection = getVectorBetweenSprites(*tail, *nextTail);
		auto dist = getManhattanDistanceBetweenSprites(*tail, *nextTail);

		if (shift > dist) 
		{
			shift -= dist;
			tail = body.erase(tail);
			setTailSprite(tail);
		}
		else 
		{
			tail->setPosition(tail->getPosition() + tailDirection * shift / dist);
		}

		prevDirection = direction;
	}

	void Snake::setBendRotation(sf::Sprite& segment, SnakeDirection from, SnakeDirection to)
	{
		float angle = 0.f;
		// ”станавливаем поворотом сегмента в зависимости от изменени€ направлени€
		if (from == SnakeGame::SnakeDirection::Right && to == SnakeGame::SnakeDirection::Up ||
			from == SnakeGame::SnakeDirection::Down && to == SnakeGame::SnakeDirection::Left)
		{
			angle = 0.f;
		}
		else if (from == SnakeGame::SnakeDirection::Down && to == SnakeGame::SnakeDirection::Right ||
			from == SnakeGame::SnakeDirection::Left && to == SnakeGame::SnakeDirection::Up)
		{
			angle = 90.f;
		}
		else if (from == SnakeGame::SnakeDirection::Left && to == SnakeGame::SnakeDirection::Down ||
			from == SnakeGame::SnakeDirection::Up && to == SnakeGame::SnakeDirection::Right) 
		{
			angle = 180;
		}
		else if (from == SnakeGame::SnakeDirection::Up && to == SnakeGame::SnakeDirection::Left ||
			from == SnakeGame::SnakeDirection::Right && to == SnakeGame::SnakeDirection::Down) 
		{
			angle = -90.f;
		}

		segment.setRotation(angle);
	}

	void Snake::setTailRotation(sf::Sprite& tail, SnakeDirection direciton)
	{
		// ѕоворачиваем хвост в зависимости от направлени€
		switch (direction) {
		case SnakeDirection::Up:
			tail.setRotation(0);
			break;
		case SnakeDirection::Right:
			tail.setRotation(90);
			break;
		case SnakeDirection::Down:
			tail.setRotation(180);
			break;
		case SnakeDirection::Left:
			tail.setRotation(270);
			break;
		}
	}

	void Snake::updateDirections(SnakeDirection newDirection)
	{
		if ((direction == SnakeDirection::Up && newDirection == SnakeDirection::Down) || 
			(direction == SnakeDirection::Down && newDirection == SnakeDirection::Up) ||
			(direction == SnakeDirection::Right && newDirection == SnakeDirection::Left) ||
			(direction == SnakeDirection::Left && newDirection == SnakeDirection::Right))
		{
			return;
		}
		direction = newDirection;
	}

	void Snake::growSnake()
	{
		head->setPosition(head->getPosition() + getDirectionVector(direction));
	}

	bool Snake::checkSnakeCollisionWithHimself()
	{
		auto curIt = tail;
		auto nextIt = std::next(tail);
		while (nextIt != head) {
			auto curRect = curIt->getGlobalBounds();
			auto nextRect = nextIt->getGlobalBounds();

			sf::FloatRect unionRect;
			unionRect.top = std::min(curRect.top, nextRect.top);
			unionRect.left = std::min(curRect.left, nextRect.left);
			unionRect.width = std::fabs(curRect.left - nextRect.left) + SNAKE_SIZE;
			unionRect.height = std::fabs(curRect.top - nextRect.top) + SNAKE_SIZE;

			if (hasSnakeCollisionWithRect(unionRect)) {
				return true;
			}
			curIt = nextIt;
			nextIt = std::next(nextIt);
		}
		return false;
	}

	bool Snake::hasSnakeCollisionWithRect(const sf::FloatRect& rect)
	{
		sf::Vector2f forwardPoint = head->getPosition();
		if (direction == SnakeDirection::Up) {
			forwardPoint.y -= SNAKE_SIZE / 2.f;
		}
		else if (direction == SnakeDirection::Right) {
			forwardPoint.x += SNAKE_SIZE / 2.f;
		}
		else if (direction == SnakeDirection::Down) {
			forwardPoint.y += SNAKE_SIZE / 2.f;
		}
		else {
			forwardPoint.x -= SNAKE_SIZE / 2.f;
		}

		bool result = rect.contains(forwardPoint);
		return result;
	}

	void Snake::setHeadSprite(std::list<sf::Sprite>::iterator segment)
	{
		float angle = 0.f; // Up
		if (direction == SnakeGame::SnakeDirection::Right)
		{
			angle = 90.f;
		}
		else if (direction == SnakeGame::SnakeDirection::Down)
		{
			angle = 180.f;
		}
		else if (direction == SnakeGame::SnakeDirection::Left)
		{
			angle = -90.f;
		}

		segment->setTexture(textures[(size_t)SnakeGame::SnakePart::Head]);
		segment->setRotation(angle);
	}

	void Snake::setTailSprite(std::list<sf::Sprite>::iterator segment)
	{
		segment->setTexture(textures[(size_t)SnakeGame::SnakePart::Tail]);

		auto nextIt = std::next(segment);
		if (nextIt == body.end()) 
		{
			return;
		}

		float angle = 0.f; // Up
		if (nextIt->getPosition().x > segment->getPosition().x)  // Right
		{
			angle = 90.f;
		}
		else if (nextIt->getPosition().y > segment->getPosition().y)  // Down
		{
			angle = 180.f;
		}
		else if (nextIt->getPosition().x < segment->getPosition().x)  // Left
		{
			angle = -90.f;
		}

		segment->setRotation(angle);
	}

	sf::Sprite Snake::getAngleElement(SnakeGame::SnakeDirection oldDirection, SnakeGame::SnakeDirection newDirection)
	{
		sf::Sprite sprite;
		initSprite(
			sprite,
			SNAKE_SIZE,
			SNAKE_SIZE,
			textures[(size_t)SnakeGame::SnakePart::BodyBend]
		);

		float angle = 0.f;
		if (oldDirection == SnakeDirection::Right && newDirection == SnakeDirection::Up ||
			oldDirection == SnakeDirection::Down && newDirection == SnakeDirection::Left)
		{
			angle = 0.f;
		}
		else if (oldDirection == SnakeDirection::Down && newDirection == SnakeDirection::Right ||
			oldDirection == SnakeDirection::Left && newDirection == SnakeDirection::Up)
		{
			angle = 90.f;
		}
		else if (oldDirection == SnakeDirection::Left && newDirection == SnakeDirection::Down ||
			oldDirection == SnakeDirection::Up && newDirection == SnakeDirection::Right)
		{
			angle = 180;
		}
		else if (oldDirection == SnakeDirection::Up && newDirection == SnakeDirection::Left ||
			oldDirection == SnakeDirection::Right && newDirection == SnakeDirection::Down) 
		{
			angle = -90.f;
		}

		sprite.setRotation(angle);
		return sprite;
	}

	sf::Vector2f Snake::getDirectionVector(SnakeDirection direction)
	{
		sf::Vector2f result;

		switch (direction)
		{
		case SnakeDirection::Up:
		{
			result = { 0.f, -SNAKE_SIZE };
			break;
		}
		case SnakeDirection::Right:
		{
			result = { SNAKE_SIZE, 0.f };
			break;
		}
		case SnakeDirection::Down:
		{
			result = { 0.f, SNAKE_SIZE };
			break;
		}
		case SnakeDirection::Left:
		{
			result = { -SNAKE_SIZE, 0.f };
			break;
		}
		}

		return result;
	}
}
