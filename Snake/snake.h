#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include <vector>
#include "Body.h"

using std::vector;

enum direction {UP, DOWN, RIGHT, LEFT, NONE};

class Snake {
	public:
		Snake(int size = dSnakeSize);

		bool Turn(direction newDirection);
		void Move();

		bool HasCrashed();
		bool HasCaughtSnack(int x, int y);
		bool IsHere(int x, int y);

		Body const GetScale(int n);
		int const Size();

	private:
		void AddScale();
		void DelScale();
		void Punish();
		void PrintSize();

		direction myDirection;
		vector<Body> myScales;
		bool canTurn;
		bool isReady;
		int indulgence;

		static const int dSnakeSize = 4;
		static const int dSnakeInitialPositionX = 0;
		static const int dSnakeInitialPositionY = 9;
		static const int CRASH_PENALTY = 3;
		static const int INDULGENCE_SIZE = 12;
		static const int MIN_SIZE = 3;
};

#endif // SNAKE_H_INCLUDED
