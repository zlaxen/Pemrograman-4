#include <iostream>

#include "snake.h"
#include "gameplay.h"

using std::cout;
using std::endl;

Snake::Snake(int size) : myDirection(RIGHT)
{
	isReady = false;
	indulgence = 0;
	Body headSegment(dSnakeInitialPositionX, dSnakeInitialPositionY);
	myScales.push_back(headSegment);
	for (int i = 0; i < size - 1; i++)
    {
		AddScale();
	}
	isReady = true;
}

bool Snake::Turn(direction newDirection) {
	bool turnsProperlyX = (myDirection >= 2 && newDirection <  2);
	bool turnsProperlyY = (myDirection <  2 && newDirection >= 2);
	if ( (turnsProperlyX || turnsProperlyY) && canTurn )
    {
		myDirection = newDirection;
		canTurn = false;
		return false;
	}
	else
    {
		return true;
	}
}

void Snake::Move()
{
	canTurn = true;
	if (HasCrashed())
    {
		if (indulgence == 0)
		{
			indulgence = INDULGENCE_SIZE;
			Punish();
		}
        else
        {
			indulgence -= 1;
		}
	}
	else
    {
		indulgence = 0;
	}
	DelScale();
	AddScale();
}

bool Snake::HasCrashed()
{
	int end = myScales.size() - 1;
	for (int i = 0; i < myScales.size(); i++)
    {
		bool sameX = myScales[end].X() == myScales[i].X();
		bool sameY = myScales[end].Y() == myScales[i].Y();
		if (sameX && sameY && i != end)
		{
			return true;
		}
	}
	return false;
}

bool Snake::HasCaughtSnack(int x, int y)
{
	int end = myScales.size() - 1;
	if (x == myScales[end].X() && y == myScales[end].Y())
    {
		AddScale();
		PrintSize();
		return true;
	}
    else
    {
		return false;
	}
}

bool Snake::IsHere(int x, int y)
{
	for (int i = 0; i < myScales.size(); i++)
    {
        if (x == myScales[i].X() && y == myScales[i].Y())
        {
            return true;
        }
	}
	return false;
}

Body const Snake::GetScale(int n)
{
	return myScales[n];
}

int const Snake::Size()
{
	return myScales.size();
}

void Snake::AddScale()
{
	int end = myScales.size() - 1;
	int changeX = 0, changeY = 0;
	switch(myDirection)
	{
		case UP:
			changeY = 1;
			break;
		case RIGHT:
			changeX = 1;
			break;
		case DOWN:
			changeY = -1;
			break;
		case LEFT:
			changeX = -1;
			break;
	}
	int lastX = myScales[end].X() + changeX;
	int lastY = myScales[end].Y() + changeY;

	if (isReady)
    {
		Gameplay::gdMoveSnakeThroughWall(lastX, lastY);
	}
	Body tmpScale(lastX, lastY);
	myScales.push_back(tmpScale);
}

void Snake::DelScale()
{
	myScales.erase(myScales.begin());
}

void Snake::Punish()
{
	for (int j = 0; j < CRASH_PENALTY; j++)
    {
		if (myScales.size() >= MIN_SIZE + 2)
		{
				DelScale();
		}
	}
	PrintSize();
}

void Snake::PrintSize()
{
	cout << "Snake's length is " << Size() << " now" << endl;
}
