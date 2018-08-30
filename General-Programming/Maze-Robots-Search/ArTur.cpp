#include "ArTur.h"
#include "GL.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

ArTur::ArTur(const Point& iniPos, Maze*l, int maxSteps)
    : Robot(iniPos, l, maxSteps) {
    srand(time(NULL));
    roboTex = LoadTexture("img/artur.jpg", false);
}

bool ArTur::east(){
    return maze->isEmpty(Point(x + 1, y));
}

bool ArTur::south(){
    return maze->isEmpty(Point(x, y + 1));
}

bool ArTur::west(){
    return maze->isEmpty(Point(x - 1, y));
}

bool ArTur::north(){
    return maze->isEmpty(Point(x, y - 1));
}

void ArTur::goEast(){
    x += 1;
    steps.push_back(Point(x, y));
}

void ArTur::goSouth(){
    y += 1;
    steps.push_back(Point(x, y));
}

void ArTur::goWest(){
    x -= 1;
    steps.push_back(Point(x, y));
}

void ArTur::goNorth(){
    y -= 1;
    steps.push_back(Point(x, y));
}

void ArTur::generateSteps(){
    int cont = 1;
    bool saiu = false;
    Direction last = SOUTH;
    x = iniPos.getX();
    y = iniPos.getY();
    steps.push_back(Point(x, y));
    while(!saiu && cont < maxSteps){
        if(last == EAST){
            if(north()){
                last = NORTH;
                goNorth();
            }else if(east()){
                last = EAST;
                goEast();
            }
            else if(south()){
                last = SOUTH;
                goSouth();
            }
            else if(west()){
                last = WEST;
                goWest();
            }
        }else if(last == SOUTH){
            if(east()){
                last = EAST;
                goEast();
            }
            else if(south()){
                last = SOUTH;
                goSouth();
            }
            else if(west()){
                last = WEST;
                goWest();
            }
            else if(north()){
                last = NORTH;
                goNorth();
            }
        }else if(last == WEST){
            if(south()){
                last = SOUTH;
                goSouth();
            }
            else if(west()){
                last = WEST;
                goWest();
            }
            else if(north()){
                last = NORTH;
                goNorth();
            }else if(east()){
                last = EAST;
                goEast();
            }
        }else if(last == NORTH){
            if(west()){
                last = WEST;
                goWest();
            }
            else if(north()){
                last = NORTH;
                goNorth();
            }else if(east()){
                last = EAST;
                goEast();
            }
            else if(south()){
                last = SOUTH;
                goSouth();
            } 
        }

        cont++;
        if(x >= maze->getWidth() || x < 0 || y >= maze->getHeight() || y < 0)
            saiu = true;
    }
}

void ArTur::draw() {
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