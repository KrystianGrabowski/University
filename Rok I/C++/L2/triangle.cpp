#include<iostream>
#include"triangle.h"
#include<sstream>

bool Triangle::collinear(Point p1, Point p2, Point p3){
    if((p1.getX() * p2.getY() * 1) +
       (p2.getX() * p3.getY() * 1) +
       (p3.getX() * p1.getY() * 1) == 0){
        return true;
    }
    else{
         return false;
    }
}

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

std::string Triangle::toString(){
    std::stringstream ss;
    ss << "(" << a.toString() << ", " << b.toString() << ", " << c.toString() << ")";
    return ss.str();
}
