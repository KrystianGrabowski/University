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
    Triangle(const Triangle &t);
    void translate(double, double);
    void rotation(Point &p, double);
    Triangle & operator= (const Triangle &p);

    double perimeter();
    double area();
    bool in_triangle(Point &p);
    Point center();


    std::string toString();
};

#endif
