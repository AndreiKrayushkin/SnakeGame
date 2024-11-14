#pragma once
#include <string>

namespace SnakeGame
{
	// Resources path
	const std::string RESOURCES_PATH = "Resources/";
	const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
	const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
	const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";

	// Game settings constants
	const int SONE_SIZE = 20;
	const int APPLE_SIZE = 30;
	const float ACCELERATION = 10.f;
	const int MAX_APPLES = 80;
	const int STONES_VALUE = 20;
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEIGHT = 600;
	const float TIME_PER_FRAME = 1.f / 60.f; // 60 fps
	const float SNAKE_SIZE = 20.f;
	const float SNAKE_SPEED_DEFAULT = 80.f;
	const float INITIAL_SNAKE_SIZE = 3;
	
	const int MAX_RECORDS_TABLE_SIZE = 5;
	const std::string PLAYER_NAME = "Andrei Krayushkin"; // нужно вводить вручную

	const std::string GAME_NAME = "SnakeGame";
}
