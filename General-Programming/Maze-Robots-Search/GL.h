#ifndef GL_H
#define GL_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Maze.h"
#include "Robot.h"

#include "Texture.h"

using namespace std;

class GL {
	public:
        static void init();
        static void setMazeRobot(Maze* maze, Robot* robot);
		static void drawRect(float x1, float y1, float x2, float y2);
		static void drawTri(float x1, float y1, float x2, float y2, float x3, float y3);
		static void drawCirc(float x1, float y1, float r);
        static void drawLine(float x1, float y1, float x2, float y2);
        static void drawText(float x, float y, string txt);
		static void setColor(GLubyte r, GLubyte g, GLubyte b) { glColor3ub(r,g,b); }
		static void clear();
		static void show() { glutSwapBuffers(); }
		static void loop();
		static void keyboard(unsigned char key, int x, int y);
        static void keyboardSpecial(int key, int x, int y);
        static void draw();
        static void enableTexture(GLuint texid);
        static void disableTexture();
        static float getDeltaX() { return deltax; }
        static float getDeltaY() { return deltay; }
    private:
        static int width,height;
        static vector<Point> steps;
        static int current;
        static float deltax, deltay;
        static int dimx, dimy;
        static Maze* lab;
        static Robot* rob;
        static TEX* wallTex;
};

#endif

