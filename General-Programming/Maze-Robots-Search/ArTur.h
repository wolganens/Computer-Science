#ifndef ArTur_H
#define ArTur_H

#include "Maze.h"
#include "Robot.h"
#include "Texture.h"

using namespace std;

class ArTur: public Robot {
	enum Direction {EAST, SOUTH, WEST, NORTH};

	public:
        ArTur(const Point& iniPos, Maze*l, int maxSteps);	// Constructor
        void draw();
        void generateSteps();
        vector<Point> getSteps();
    private:
        TEX* roboTex; // robot texture id
        int x, y;

        bool east();
        bool south();
        bool west();
        bool north();

        void goEast();
        void goSouth();
        void goWest();
        void goNorth();
};

#endif
