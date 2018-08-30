#include "T800.h"
#include "GL.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <sstream>

using namespace std;

T800::T800(const Point& iniPos, Maze*l, int maxSteps)
    : Robot(iniPos, l, maxSteps) {
    srand(time(NULL));
    roboTex = LoadTexture("img/t800.jpg", false);
}

void T800::generateSteps(){
    queue<state> q;
    set<Coor> visited;
    int cont;

    string path;
    Coor current = make_pair(iniPos.getX(), iniPos.getY());
    q.push(state(to_string(current.first) + " " + to_string(current.second), current.first, current.second));

    while(1){
        path = q.front().path;
        current = q.front().point;
        q.pop();
        if(current.first >= maze->getWidth() || current.first < 0 || current.second >= maze->getHeight() || current.second < 0){
            break;
        }
        
        if(visited.find(current) != visited.end()){
            continue;
        }
        visited.insert(current);

        if(maze->isEmpty(Point(current.first + 1, current.second))) {
            q.push(state(path + "," + to_string(current.first + 1) + " " + to_string(current.second), current.first + 1, current.second));
        }

        if(maze->isEmpty(Point(current.first, current.second + 1))) {
            q.push(state(path + "," + to_string(current.first) + " " + to_string(current.second + 1), current.first, current.second + 1));
        }

        if(maze->isEmpty(Point(current.first - 1, current.second))) {
            q.push(state(path + "," + to_string(current.first - 1) + " " + to_string(current.second), current.first - 1, current.second));
        }

        if(maze->isEmpty(Point(current.first, current.second - 1))){
            q.push(state(path + "," + to_string(current.first) + " " + to_string(current.second - 1), current.first, current.second - 1));
        }
    }
    
    istringstream spath(path);
    int x, y;
    char c;
    
    cont = 1;
    while(1){
        spath >> x >> y;
        steps.push_back(Point(x, y));
        if(spath.eof() || cont == maxSteps)
            break;
        else
            spath >> c;
        cont++;
    }
}

void T800::draw() {
    float rx,ry;
    float deltax = GL::getDeltaX();
    float deltay = GL::getDeltaY();
    rx = pos.getX() * deltax;
    ry = pos.getY() * deltay;
    GL::enableTexture(roboTex->texid);
    GL::setColor(255,255,255);
    GL::drawRect(rx, ry, rx+deltax, ry+deltay);
    GL::disableTexture();
}