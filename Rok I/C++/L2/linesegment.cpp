#include<iostream>
#include"linesegment.h"
#include<sstream>

Line_segment::Line_segment(Point p_a, Point p_b)
    : a(p_a), b(p_b)
    {}

Line_segment::Line_segment(const Line_segment &ls)
    : a(ls.a), b(ls.b)
    {}

void Line_segment::translate(double vec_x, double vec_y){
    a.translate(vec_x, vec_y);
    b.translate(vec_x, vec_y);
}
Line_segment & Line_segment::operator= (const Line_segment &ls){
    if (this != &ls){
        a = ls.a;
        b = ls.b;
    }

    return *this;
}

void Line_segment::rotation(Point &p, double angle){
    a.rotation(p, angle);
    b.rotation(p, angle);
}

std::string Line_segment::toString(){
    std::stringstream ss;
    ss << "(" << a.toString() << ", " << b.toString() << ")";
    return ss.str();
}
