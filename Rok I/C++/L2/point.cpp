#include<iostream>
#include"point.h"
#include<sstream>

Point::Point(double p_x, double p_y){
    x = p_x;
    y = p_y;
}

Point::Point(const Point &p){
    x = p.x;
    y = p.y;
}

double Point::getX(){
    return x;
}

double Point::getY(){
    return y;
}

Point & Point::operator= (const Point &p){
    if (this != &p){
        x = p.x;
        y = p.y;        
    }

    return *this;
}

std::string Point::toString(){
    std::stringstream ss;
    ss << "(" << x << ", " << y << ")";
    return ss.str();
}
