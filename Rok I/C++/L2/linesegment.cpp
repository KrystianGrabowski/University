#include<iostream>
#include"linesegment.h"
#include<sstream>
#include"global.h"

Line_segment::Line_segment(Point p_a, Point p_b)
    {
        try{
            if (distance(p_a, p_b) == 0){
                throw "Distance equal zero";
            }
            else{
                a = p_a;
                b = p_b;
            }
        }
        catch (const char* s){
            std::cerr << s << std::endl;
        }
    }

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

double Line_segment::length(){
    return distance(a, b);
}

void Line_segment::rotation(Point &p, double angle){
    a.rotation(p, angle);
    b.rotation(p, angle);
}

bool Line_segment::on_line(Point &p){
    return (collinear(a, b, p) &&
        std::min(a.getX(), b.getX()) <= p.getX() && p.getX() <= std::max(a.getX(), b.getX()) &&
        std::min(a.getY(), b.getY()) <= p.getY() && p.getY() <= std::max(a.getY(), b.getY()));
}

Point Line_segment::middle(){
    return Point(((a.getX() + b.getX()) / 2) + ((a.getY()+ b.getY()) / 2));
}

std::string Line_segment::toString(){
    std::stringstream ss;
    ss << "(" << a.toString() << ", " << b.toString() << ")";
    return ss.str();
}
