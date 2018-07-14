#include<iostream>

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include"point.h"

class Triangle{
public:
    Point a;
    Point b;
    Point c;

    Triangle(Point p_a, Point p_b, Point p_c);
    Triangle(const Triangle &t);
    Triangle & operator= (const Triangle &p);

    void translate(double vec_x, double vec_y);
    void rotation(Point &p, double angle);
    double perimeter();
    double area();
    bool in_triangle(Point &p);
    Point center();
    std::string toString();
};

#endif
