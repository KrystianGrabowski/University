#include<iostream>

#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include"point.h"

class Line_segment{
public:
    Point a;
    Point b;

    Line_segment(Point p_a, Point p_b);
    Line_segment(const Line_segment &ls);
    Line_segment & operator= (const Line_segment &ls);

    void translate(double vec_x, double vec_y);
    void rotation(Point &p, double angle);
    double length();
    bool on_line(Point &p);
    Point middle();
    std::string toString();
};

#endif
