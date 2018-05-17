#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include "gameplay.h"
#include "Rendering.h"

using std::cout;
using std::endl;

int main(int argc, char ** argv) {
	cout << "Welcome To Snake Game" << endl;
	Gameplay::gdStart(argc, argv);
}
