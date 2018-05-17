#ifndef BODY_H_INCLUDED
#define BODY_H_INCLUDED

class Body {
	public:
		Body() { }
		Body(int inX, int inY) : myX(inX), myY(inY) { }

		int X() const {return myX;}
		int Y() const {return myY;}

		bool operator==(const Body & s) {
			return (s.myX == myX && s.myY == myY);
		}

		Body & operator=(const Body & s) {
			myX = s.myX;
			myY = s.myY;
			return *this;
		}

	private:
		int myX, myY;
};

#endif // BODY_H_INCLUDED
