#include<iostream>
#include<math.h>
#include"point.h"
#include<sstream>
#include"global.h"

Point::Point(double p_x, double p_y){
    x = p_x;
    y = p_y;
}

Point::Point(const Point &p){
    x = p.x;
    y = p.y;
}

Point & Point::operator= (const Point &p){
    if (this != &p){
        x = p.x;
        y = p.y;
    }
    return *this;
}

double Point::getX(){
    return x;
}

double Point::getY(){
    return y;
}

void Point::translate(double vec_x, double vec_y){
    x = x + vec_x;
    y = y + vec_y;
}

void Point::rotation(Point &p, double angle){
    double radians = angle * 3.1416/180;
    double x1 = (x - p.getX()) * cos(radians) - (y - p.getY()) * sin(radians) + p.getX();
    double y1 = (x - p.getX()) * sin(radians) + (y - p.getY()) * cos(radians) + p.getY();
    x = x1;
    y = y1;
}



std::string Point::toString(){
    std::stringstream ss;
    ss << "(" << x << ", " << y << ")";
    return ss.str();
}
