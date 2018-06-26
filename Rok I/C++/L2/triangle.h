#include<iostream>

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include"point.h"

class Triangle{
public:
    Point a;
    Point b;
    Point c;

    Triangle(Point, Point, Point);
    Triangle(const Triangle&);
    Triangle & operator= (const Triangle&);

    void translate(double, double);
    void rotation(Point&, double);
    double perimeter();
    double area();
    bool in_triangle(Point&);
    Point center();
    std::string toString();
};

#endif
