#include<iostream>

#ifndef POINT_H
#define POINT_H

class Point{
    double x;
    double y;

public:
    Point(double=0, double=0);
    Point(const Point &p);
    double getX();
    double getY();
    Point & operator= (const Point &p);

    std::string toString();
};

#endif
