#include<iostream>
#include<math.h>
#include"point.h"
#include"linesegment.h"
#include"triangle.h"

double distance(Point &p1, Point &p2){
    return sqrt(pow(p2.getX() - p1.getX(), 2) + (pow (p2.getY() - p1.getY(), 2)));
}


int main(){
    Point p0(2,5);
    Point p01(5,9);
    std::cout << distance(p0,p01) << std::endl;
    //Point
    Point p1(2,5);
    Point p2(5,9);
    Point p3(-1, -2);
    std::cout << p1.toString() << std::endl;
    std::cout << p2.toString() << std::endl;
    std::cout << p3.toString() << std::endl;

    Point p4;
    p4 = p2;
    std::cout << p4.toString() << std::endl;
    Point p5(p4);
    std::cout << p5.toString() << std::endl;


    //Line
    Line_segment l1(p1, p2);
    std::cout << l1.toString() << std::endl;
    Line_segment l2(p2,p1);
    std::cout << l2.toString() << std::endl;
    l2 = l1;
    std::cout << l2.toString() << std::endl;
    Line_segment l3(l2);
    std::cout << l3.toString() << std::endl;

    //Triangle
    Triangle t1(p1, p2, p3);
    std::cout << t1.toString() << std::endl;
    Triangle t2(p3, p2, p1);
    t2 = t1;
    std::cout << t2.toString() << std::endl;
    Triangle t3(t2);
    std::cout << t3.toString() << std::endl;

    t2 = t2;
    std::cout << t2.toString() << std::endl;


    return 0;
}
