#include<iostream>
#include"triangle.h"
#include<sstream>
#include<math.h>
#include"global.h"

Triangle::Triangle(Point p_a, Point p_b, Point p_c)
{
    try{
        if (collinear(p_a, p_b, p_c)){
            throw "Collinear points";
        }
        else{
            a = p_a;
            b = p_b;
            c = p_c;
        }
    }
    catch (const char* s){
        std::cerr << s << std::endl;
    }
}

Triangle::Triangle(const Triangle &t)
    : a(t.a), b(t.b), c(t.c)
    {}

Triangle & Triangle::operator= (const Triangle &p){
    if (this != &p){
        a = p.a;
        b = p.b;
        c = p.c;
    }
    return *this;
}

void Triangle::translate(double vec_x, double vec_y){
    a.translate(vec_x, vec_y);
    b.translate(vec_x, vec_y);
    c.translate(vec_x, vec_y);
}

void Triangle::rotation(Point &p, double angle){
    a.rotation(p, angle);
    b.rotation(p, angle);
    c.rotation(p, angle);
}

double Triangle::perimeter(){
    return (distance(a, b) + distance(b, c) + distance(c, a));
}

double Triangle::area(){
    double half_per = (1/2.0) * perimeter();
    return sqrt(half_per * (half_per - distance(a, b)) *
                (half_per - distance(b, c)) * (half_per - distance(c, a)));
}

bool Triangle::in_triangle(Point &p){
    return fabs(area() - (area_three(a, b, p) + area_three(a, c, p) + area_three(b, c, p))) <= 0.001;
}

Point Triangle::center(){
    return Point((a.getX() + b.getX() + c.getX()) / 3, (a.getY() + b.getY() + c.getY()) / 3);
}

std::string Triangle::toString(){
    std::stringstream ss;
    ss << "(" << a.toString() << ", " << b.toString() << ", " << c.toString() << ")";
    return ss.str();
}
