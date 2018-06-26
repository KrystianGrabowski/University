#include<iostream>

#ifndef POINT_H
#define POINT_H

class Point{
    double x;
    double y;

public:
    Point(double=0, double=0);
    Point(const Point&);
    Point & operator= (const Point&);

    double getX();
    double getY();
    void translate(double, double);
    void rotation(Point&, double);
    std::string toString();
};

#endif
