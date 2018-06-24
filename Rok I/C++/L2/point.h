#include<iostream>

#ifndef POINT_H
#define POINT_H

class Point{
    double x;
    double y;

public:
    Point(int=0, int=0);
    Point(const Point &p);
    Point & operator= (const Point &p);
};

#endif
