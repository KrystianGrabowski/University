#include<iostream>
#include"point.h"
#include"linesegment.h"
#include"triangle.h"

int main(){
    Point p1(2,2);
    Point p2(9,10);
    Point p3(-1, -2);
    std::cout << p1.toString() << std::endl;
    std::cout << p2.toString() << std::endl;
    std::cout << p3.toString() << std::endl;

    Line_segment l1(p1, p2);
    std::cout << l1.toString() << std::endl;

    Triangle t1(p1, p2, p3);
    std::cout << t1.toString() << std::endl;

    return 0;
}
