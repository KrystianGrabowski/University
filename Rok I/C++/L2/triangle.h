#include<iostream>

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include"point.h"

class Triangle{
    Point a;
    Point b;
    Point c;
    bool collinear(Point, Point, Point);

public:
    Triangle(Point, Point, Point);
    Triangle(const Triangle &t);
    void translate(double, double);
    void rotation(Point &p, double);
    Triangle & operator= (const Triangle &p);

    std::string toString();
};

#endif
