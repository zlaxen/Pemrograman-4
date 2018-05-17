#include <iostream>

#include "gameplay.h"
#include "Rendering.h"

using std::cout;
using std::endl;

Snake Gameplay::Python;
vector<Food> Gameplay::gdSnacks;
bool Gameplay::isActive = false;

void Gameplay::gdStart(int argc, char ** argv)
{
	isActive = true;
	Render::rdInitialize(argc, argv);
}

void Gameplay::gdProcess()
{
	if (isActive)
    {
		bool isHungry = true;
		for (int i = 0; i < gdSnacks.size(); i++)
		{
			int X = gdSnacks[i].X();
			int Y = gdSnacks[i].Y();
			if (Python.HasCaughtSnack(X, Y))
			{
				gdSnacks.erase(gdSnacks.begin() + i);
				isHungry = false;
			}
		}

		if (gdSnacks.size() < SNACKS_LIMIT)
		{
			gdAddSnack();
		}

		if (isHungry)
		{
			Python.Move();
		}
	}
}

void Gameplay::gdKeyPressed(key pressedKey)
{
	switch(pressedKey)
	{
		case key_up:
			gdTurnSnake(UP);
			break;
		case key_right:
			gdTurnSnake(RIGHT);
			break;
		case key_down:
			gdTurnSnake(DOWN);
			break;
		case key_left:
			gdTurnSnake(LEFT);
			break;
		case key_esc:
			gdPause();
			break;
	}
}

void Gameplay::gdMoveSnakeThroughWall(int & X, int & Y)
{
	if (X >= FIELD_WIDTH)
    {
        X = 0;
    }
	if (Y >= FIELD_HEIGHT)
    {
        Y = 0;
    }
	if (X < 0)
    {
        X = FIELD_WIDTH - 1;
    }
	if (Y < 0)
    {
        Y = FIELD_HEIGHT - 1;
    }
}

bool Gameplay::gdIsActive()
{
	return isActive;
}

Snake Gameplay::gdGetSnake()
{
	return Python;
}

Food Gameplay::gdGetSnack(int n)
{
	return gdSnacks[n];
}

int Gameplay::gdGetSnacksQuantity()
{
	return gdSnacks.size();
}

void Gameplay::gdPause()
{
	isActive = !isActive;
	if (isActive)
    {
        cout << "Unpaused" << endl;
    }
    else
    {
        cout << "Paused"   << endl;
    }
}

void Gameplay::gdTurnSnake(direction newDirection)
{
	if (isActive)
    {
		Python.Turn(newDirection);
	}
}

void Gameplay::gdAddSnack(food_type type)
{
	int foodX, foodY;
	do
    {
		foodX = rand() % FIELD_WIDTH;
		foodY = rand() % FIELD_HEIGHT;
	}
	while (Python.IsHere(foodX, foodY));
	gdSnacks.push_back(Food(foodX, foodY, type));
}
