#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED

#include "Body.h"

enum food_type {normal};

class Food
{
	public:
		Food(int x, int y, food_type inType) : type(inType)
		{
			coordinate = Body(x, y);
		}
		Food(Body inCoordinate, food_type inType) : type(inType)
		{
			coordinate = inCoordinate;
		}
		int const X() {return coordinate.X();}
		int const Y() {return coordinate.Y();}
		int const Type() {return type;}

	private:
		food_type type;
		Body coordinate;
};

#endif // FOOD_H_INCLUDED
