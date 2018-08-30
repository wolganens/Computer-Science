#ifndef ROBOTB9_H
#define ROBOTB9_H

#include "Maze.h"
#include "Robot.h"
#include "Texture.h"

using namespace std;

class RobotB9: public Robot {
	public:
        RobotB9(const Point& iniPos, Maze*l, int maxSteps);	// Constructor
        void draw();
        void generateSteps();
        vector<Point> getSteps();
    private:
        TEX* roboTex; // robot texture id
};

#endif
