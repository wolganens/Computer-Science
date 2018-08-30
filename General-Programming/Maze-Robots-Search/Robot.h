#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include "Point.h"

using namespace std;

// Class which defines the public interface for any robot
// The 3 robot types must implement these methods

class Robot
{
    public:
        Robot(const Point& iniPos, Maze* maze, int maxSteps) {
            this->iniPos = iniPos;
            this->maze = maze;
            this->maxSteps = maxSteps;
        }
    	virtual void draw() = 0;

        void move(const Point &pos) {
            this->pos = pos; 
        }
    	virtual void generateSteps() = 0;
    	
        vector<Point> getSteps() { 
            return steps; 
        }

    protected:
        Point iniPos, pos;
        Maze* maze;
        int maxSteps;
    	vector<Point> steps;
};

#endif
