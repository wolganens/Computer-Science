#ifndef T800_H
#define T800_H

#include "Maze.h"
#include "Robot.h"
#include "Texture.h"
#include <string>
#include <utility>

using namespace std;

class T800: public Robot {

    typedef pair <int, int> Coor;
    typedef struct state {
        string path;
        Coor point;
        state(string _path, int _x, int _y) : path(_path), point(make_pair(_x,_y)) {}
    }State;

	public:
        T800(const Point& iniPos, Maze*l, int maxSteps);	// Constructor
        void draw();
        void generateSteps();
        vector<Point> getSteps();
    private:
        TEX* roboTex; // robot texture id
};

#endif
