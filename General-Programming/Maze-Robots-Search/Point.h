#ifndef POINT_H
#define POINT_H

class Point
{
    public:
        Point(int x=0, int y=0) { this->x = x; this->y = y; }
        int getX() const { return x; }
        int getY() const { return y; }
    private:
        int x, y;
};

#endif

