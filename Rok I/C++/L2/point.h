#include<iostream>

#ifndef POINT_H
#define POINT_H

class Point{
    double x;
    double y;

public:
    Point(double p_x=0, double p_y=0);
    Point(const Point &p);
    Point & operator= (const Point &p);

    double getX();
    double getY();
    void translate(double vec_x, double vec_y);
    void rotation(Point &p, double angle);
    std::string toString();
};

#endif
