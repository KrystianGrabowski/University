#include<iostream>

#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include"point.h"

class Line_segment{
    Point a;
    Point b;
public:
    Line_segment(Point, Point);
    Line_segment(const Line_segment &ls);
    Line_segment & operator= (const Line_segment &p);
};

#endif
