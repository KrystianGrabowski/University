#include<iostream>
#include"triangle.h"
#include<sstream>

Triangle::Triangle(Point p_a, Point p_b, Point p_c)
    : a(p_a), b(p_b), c(p_c)
    {}

Triangle::Triangle(const Triangle &t)
    : a(t.a), b(t.b), c(t.c)
    {}

Triangle & Triangle::operator= (const Triangle &p){
    a = p.a;
    b = p.b;
    c = p.c;
    return *this;
}

std::string Triangle::toString(){
    std::stringstream ss;
    ss << "(" << a.toString() << ", " << b.toString() << ", " << c.toString() << ")";
    return ss.str();
}
