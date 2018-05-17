#ifndef GAMEPLAY_H_INCLUDED
#define GAMEPLAY_H_INCLUDED

#include <vector>
#include <cstdlib>

#include "snake.h"
#include "food.h"

enum key {key_up, key_right, key_down, key_left, key_esc};

class Gameplay
{
	public:
		static void gdStart(int argc, char ** argv);
		static void gdProcess();
		static void gdKeyPressed(key pressedKey);
		static void gdMoveSnakeThroughWall(int & X, int & Y);

		static bool  gdIsActive();
		static Snake gdGetSnake();
		static Food  gdGetSnack(int n);
		static int   gdGetSnacksQuantity();

	private:
		static inline void gdPause();
		static inline void gdTurnSnake(direction newDirection);
		static void gdAddSnack(food_type type = normal);

		static Snake Python;
		static vector<Food> gdSnacks;
		static bool isActive;

		static const int SNACKS_LIMIT = 1;
		static const int FIELD_WIDTH = 30;
		static const int FIELD_HEIGHT = 20;
};

#endif // GAMEPLAY_H_INCLUDED
