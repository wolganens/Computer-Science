#ifndef TESTMAZE_H
#define TESTMAZE_H

#include <fstream>
#include "Maze.h"

using namespace std;

class TestMaze : public Maze {
	#define MAX_MAZE 100
	typedef pair <int, int> Coor;
	enum Direction {EAST, SOUTH, WEST, NORTH};
	public:
		TestMaze();	// Constructor
        bool isEmpty(const Point& ponto) const;
    	bool isIdx(int x, int y);
	    int  getWidth();
	    int  getHeight();
	    void loadMaze(string arquivo);
	    void generateMaze(int r);
        int  getRobot();
        Point getIniPos();
	private:
		int dimx, dimy;		// Maze size
        char lab[MAX_MAZE][MAX_MAZE];	// The maze
        int robot;
        Point posIni;
};

#endif
