#include<iostream>
#ifndef GLOBAL_H
#define GLOBAL_H
#include"point.h"
#include"linesegment.h"
#include"triangle.h"

bool collinear(Point &p1, Point &p2, Point &p3);
double distance(Point &p1, Point &p2);
bool parallel(Line_segment &l1, Line_segment &l2);
bool perpendicular(Line_segment &l1, Line_segment &l2);
Point intersection(Line_segment &l1, Line_segment &l2);
double vectorX(Line_segment &l);
double vectorY(Line_segment &l);
double perimeter_three(Point &a, Point &b, Point &c);
double area_three(Point &a, Point &b, Point &c);
bool disjoint(Triangle &t1, Triangle &t2);
bool contains(Triangle &t1, Triangle &t2);

#endif
