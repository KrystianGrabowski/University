#include<iostream>
#include"point.h"
#include"linesegment.h"
#include"triangle.h"

int main(){
    //Point
    Point p1(2,2);
    Point p2(9,10);
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

    std::cout << "TRIANG " << std::endl;
    //Triangle
    Triangle t1(p1, p2, p3);
    std::cout << t1.toString() << std::endl;
    Triangle t2(p3, p2, p1);
    t2 = t1;
    std::cout << t2.toString() << std::endl;
    Triangle t3(t2);
    std::cout << t3.toString() << std::endl;


    return 0;
}
