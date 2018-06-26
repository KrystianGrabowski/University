#include<iostream>

#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include"point.h"

class Line_segment{
public:
    Point a;
    Point b;

    Line_segment(Point, Point);
    Line_segment(const Line_segment&);
    Line_segment & operator= (const Line_segment&);

    void translate(double, double);
    void rotation(Point&, double);
    double length();
    bool on_line(Point&);
    Point middle();
    std::string toString();
};

#endif
