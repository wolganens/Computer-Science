#ifndef Robby_H
#define Robby_H

#include "Maze.h"
#include "Robot.h"
#include "Texture.h"

using namespace std;

class Robby: public Robot {
	public:
        Robby(const Point& iniPos, Maze*l, int maxSteps);	// Constructor
        void draw();
        void generateSteps();
        vector<Point> getSteps();
    private:
        TEX* roboTex; // robot texture id
};

#endif
