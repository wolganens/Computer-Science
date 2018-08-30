#include "Robby.h"
#include "GL.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

Robby::Robby(const Point& iniPos, Maze*l, int maxSteps)
    : Robot(iniPos, l, maxSteps)
{
    srand(time(NULL));
    roboTex = LoadTexture("img/artur.jpg", false);
}

void Robby::generateSteps()
{
    int cont = 1;
    bool saiu = false;
    int x = iniPos.getX();
    int y = iniPos.getY();
    steps.push_back(Point(x,y));
    while(!saiu && cont < maxSteps){
        if(maze->isEmpty(Point(x + 1, y)))
            x += 1;
        else if(maze->isEmpty(Point(x - 1, y)))
            x -= 1;
        else
            break;
      
        steps.push_back(Point(x, y));
        cont++;
        if(x >= maze->getWidth() || x < 0 || y >= maze->getHeight() || y < 0)
            saiu = true;
    }
}

void Robby::draw()
{
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
