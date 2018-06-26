#include<iostream>
#ifndef GLOBAL_H
#define GLOBAL_H
#include"point.h"
#include"linesegment.h"
#include"triangle.h"

bool collinear(Point&, Point&, Point&);
double distance(Point&, Point&);
bool parallel(Line_segment&, Line_segment&);
bool perpendicular(Line_segment&, Line_segment&);
Point intersection(Line_segment&, Line_segment&);
double vectorX(Line_segment&);
double vectorY(Line_segment&);
double perimeter_three(Point&, Point&, Point&);
double area_three(Point&, Point&, Point&);
bool disjoint(Triangle&, Triangle&);
bool contains(Triangle&, Triangle&);

#endif
