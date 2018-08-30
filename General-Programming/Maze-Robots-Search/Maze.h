#ifndef MAZE_H
#define MAZE_H

#include "Point.h"
#include <string>

using namespace std;

// Class that defines the maze interface
// All methods must be implemented in derived classes

class Maze
{
    public:

    virtual bool isEmpty(const Point& ponto) const = 0;
	virtual int  getWidth() = 0;
	virtual int  getHeight() = 0;
    virtual int  getRobot() = 0;
    virtual Point getIniPos() = 0;
	virtual void loadMaze(string arquivo) = 0;
	virtual void generateMaze(int r) = 0;
};

#endif
