#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <math.h>
#include "Rendering.h"
#include "gameplay.h"
#include "snake.h"

int Render::rdFrame = 0;
float Render::rdAngle = 0.0f;

const float Render::PI = 3.14159265358979323846f;
const char* Render::TITLE = "Ataraxer's Snake";

void Render::rdInitialize(int argc, char** argv)
{
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowSize(WIDTH, HEIGHT);
		glutCreateWindow(TITLE);
	}
    {
		glutDisplayFunc(rdRender);
		glutReshapeFunc(rdWindowResize);
		glutKeyboardFunc(rdKeyPressed);
		glutSpecialFunc(rdSpecialKeyPressed);
		glutTimerFunc(1000/FRAME_RATE, rdFrameControl, 0);
	}
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glViewport(0, 0, WIDTH, HEIGHT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, WIDTH, 0, HEIGHT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	{
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
	}
	glutMainLoop();
}

void Render::rdRender()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
		glBegin(GL_QUADS);
		rdRenderSnacks();
		rdRenderSnake(Gameplay::gdGetSnake());
	glEnd();
    glutSwapBuffers();
}

void Render::rdFrameControl(int arg) {
	if (rdFrame == 60)
    {
		rdFrame = 0;
	}
	rdFrame += 1;
	rdAngle += PI/(FRAME_RATE/2);
	if (rdFrame % (FRAME_RATE/SNAKE_SPEED) == 0)
    {
		Gameplay::gdProcess();
	}
    glutPostRedisplay();
    glutTimerFunc(1000/FRAME_RATE, rdFrameControl, 0);
}

void Render::rdWindowResize(GLsizei W, GLsizei H)
{
	glutReshapeWindow(WIDTH, HEIGHT);
	int left = (glutGet(GLUT_SCREEN_WIDTH) - WIDTH) / 2;
	int top = (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) / 2;
	glutPositionWindow(left, top);
}

void Render::rdKeyPressed(unsigned char pressedKey, int x, int y)
{
	switch (pressedKey)
	{
		case 'w':
			Gameplay::gdKeyPressed(key_up);
			break;
		case 'd':
			Gameplay::gdKeyPressed(key_right);
			break;
		case 's':
			Gameplay::gdKeyPressed(key_down);
			break;
		case 'a':
			Gameplay::gdKeyPressed(key_left);
			break;
		case 27:
			rdAngle = 0;
			Gameplay::gdKeyPressed(key_esc);
			break;
	}
}

void Render::rdSpecialKeyPressed(int pressedKey, int x, int y)
{
	switch (pressedKey)
	{
		case GLUT_KEY_UP:
			Gameplay::gdKeyPressed(key_up);
			break;
		case GLUT_KEY_RIGHT:
			Gameplay::gdKeyPressed(key_right);
			break;
		case GLUT_KEY_DOWN:
			Gameplay::gdKeyPressed(key_down);
			break;
		case GLUT_KEY_LEFT:
			Gameplay::gdKeyPressed(key_left);
			break;
	}
}

float Render::rdOpacity(float modifier)
{
	if (Gameplay::gdIsActive())
    {
		return (sin(rdAngle * modifier + 3*PI/2) + 1)/2;
	}
	else
    {
		return 0.0f;
	}
}

void Render::rdSetColor(int red, int green, int blue, float alpha)
{
	GLubyte red_alpha   = (255 - red)   * alpha;
	GLubyte green_alpha = (255 - green) * alpha;
	GLubyte blue_alpha  = (255 - blue)  * alpha;
	glColor3ub(red + red_alpha, green + green_alpha, blue + blue_alpha);
}

void Render::rdPickColor(color newColor, float opacity)
{
	switch(newColor)
	{
		case white:
			rdSetColor(255, 255, 255);
			break;
		case black:
			rdSetColor(000, 000, 000, opacity);
			break;
		case red:
			rdSetColor(220, 000, 000, opacity);
			break;
		case dark_red:
			rdSetColor(175, 000, 000, opacity);
			break;
		case green:
			rdSetColor(115, 195, 75, opacity);
			break;
		case dark_green:
			rdSetColor(90, 150, 60, opacity);
			break;
		case blue:
			rdSetColor(40, 115, 220, opacity);
			break;
		case orange:
			rdSetColor(215, 140, 35, opacity);
			break;
	}
}

void Render::rdRenderSnake(Snake inSnake)
{
	for (int i = 0; i < inSnake.Size(); i++)
    {
		int X = inSnake.GetScale(i).X() * SQUARE_SIZE;
		int Y = inSnake.GetScale(i).Y() * SQUARE_SIZE;
		if (i == inSnake.Size() - 1)
        {
			if (inSnake.HasCrashed())
			{
				rdPickColor(dark_red);
			}
            else
            {
				rdPickColor(dark_green);
			}
		}
		else
        {
			if (inSnake.HasCrashed())
			{
				rdPickColor(red);
			}
            else
            {
				rdPickColor(green);
			}
		}
		rdDrawSquare(X, Y);
	}
}

void Render::rdRenderSnacks()
{
	for (int i = 0; i < Gameplay::gdGetSnacksQuantity(); i++)
    {
		int X = Gameplay::gdGetSnack(i).X() * SQUARE_SIZE;
		int Y = Gameplay::gdGetSnack(i).Y() * SQUARE_SIZE;
		rdPickColor(blue, rdOpacity());
		rdDrawSquare(X, Y);
	}
}

void Render::rdDrawSquare(float x, float y, float size)
{
	float delta = 2.0f;
	glVertex2f(x + delta, y + delta);
	glVertex2f(x + size - delta, y + delta);
	glVertex2f(x + size - delta, y + size - delta);
	glVertex2f(x + delta, y + size - delta);
}
