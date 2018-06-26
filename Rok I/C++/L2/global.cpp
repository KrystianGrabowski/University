#include<iostream>
#include"global.h"
#include"linesegment.h"
#include"point.h"
#include"triangle.h"
#include<math.h>

bool collinear(Point &p1, Point &p2, Point &p3){
    if((p1.getX() * p2.getY() * 1) +
       (p2.getX() * p3.getY() * 1) +
       (p3.getX() * p1.getY() * 1) -
       (1 * p2.getY() * p3.getX()) -
       (1 * p3.getY() * p1.getX()) -
       (1 * p1.getY() * p2.getX()) == 0){
        return true;
    }
    else{
         return false;
    }
}


double distance(Point &p1, Point &p2){
    return sqrt(pow(p2.getX() - p1.getX(), 2) + (pow (p2.getY() - p1.getY(), 2)));
}

double vectorX(Line_segment &l){
    return (l.b.getX() - l.a.getX());
}
double vectorY(Line_segment &l){
    return (l.b.getY() - l.a.getY());
}

bool parallel(Line_segment &l1, Line_segment&l2){
    return (vectorX(l1) / vectorX(l2)) ==
            (vectorY(l1)/ vectorY(l2));
}

bool perpendicular(Line_segment &l1, Line_segment&l2){
    return ((vectorX(l1) * vectorX(l2)) +
            (vectorY(l1) * vectorY(l2))) == 0;
}

Point intersection(Line_segment &l1, Line_segment &l2){
    double Ax = l1.a.getX();
    double Ay = l1.a.getY();
    double Bx = l1.b.getX();
    double By = l1.b.getY();
    double Cx = l2.a.getX();
    double Cy = l2.a.getY();
    double Dx = l2.b.getX();
    double Dy = l2.b.getY();
    double x=((Bx-Ax)*(Dx*Cy-Dy*Cx)-(Dx-Cx)*(Bx*Ay-By*Ax))/((By-Ay)*(Dx-Cx)-(Dy-Cy)*(Bx-Ax));
    double y=((Dy-Cy)*(Bx*Ay-By*Ax)-(By-Ay)*(Dx*Cy-Dy*Cx))/((Dy-Cy)*(Bx-Ax)-(By-Ay)*(Dx-Cx));
    return Point(x, y);
}

double perimeter_three(Point &a, Point &b, Point &c){
    return (distance(a, b) + distance(b, c) + distance(c, a));
}

double area_three(Point &a, Point &b, Point &c){
    double half_per = (1/2.0) * perimeter_three(a, b, c);
    return sqrt(half_per * (half_per - distance(a, b)) *
                (half_per - distance(b, c)) * (half_per - distance(c, a)));
}

bool point_in_triangle(Triangle &t, Point &p){
    return fabs(area_three(t.a, t.b, t.c) - (area_three(t.a, t.b, p) +
            area_three(t.a, t.c, p) + area_three(t.b, t.c, p))) <= 0.001;
}
bool disjoint(Triangle &t1, Triangle &t2){
    return (not (point_in_triangle(t1, t2.a))) &&
            (not (point_in_triangle(t1, t2.b))) &&
             (not (point_in_triangle(t1, t2.c)));
}

bool contains(Triangle &t1, Triangle &t2){
    return (point_in_triangle(t1, t2.a)) &&
            (point_in_triangle(t1, t2.b)) &&
             (point_in_triangle(t1, t2.c));
}
