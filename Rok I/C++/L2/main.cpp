#include<iostream>
#include<math.h>
#include"point.h"
#include"linesegment.h"
#include"triangle.h"
#include"global.h"




int main(){
    //Tests
    Point p0(2,5);
    Point p01(5,9);
    std::cout << distance(p0,p01) << std::endl;
    Point p02(-1,2);
    p02.translate(-2,2);
    std::cout << p02.toString() << std::endl;

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

    //translation
    Triangle t122(p0, p01, p02);
    std::cout << t122.toString() << std::endl;
    t122.translate(-2,2);
    std::cout << t122.toString() << std::endl;

    //rotation
    Point pr1(3,2);
    Point z(0,0);
    pr1.rotation(z, -140);
    std::cout << pr1.toString() << std::endl;

    Point prrr1(3,5);
    prrr1.rotation(z, 90);
    std::cout << prrr1.toString() << std::endl;

    //on
    Line_segment ss1(p0, p01);
    std::cout << ss1.length() << std::endl;

    Point col1(0,0);
    Point col2(4,4);
    Point onco(2,2);
    Line_segment coll(col1, col2);
    std::cout << coll.on_line(onco) << std::endl;

    //parallel
    Point par1(4,2);
    Point par2(7,4);
    Point par3(3,4);
    Point par4(9,8);
    Line_segment paral1(par1, par2);
    Line_segment paral2(par3, par4);
    std::cout << parallel(paral1, paral2) << std::endl;

    Point per5(3,3);
    Point per6(5,1);
    Point per7(3,1);
    Point per8(8,6);
    Line_segment perpe1(per5, per6);
    Line_segment perpe2(per7, per8);

    std::cout << perpendicular(perpe1, perpe2) << std::endl;

    Point peri1(0,0);
    Point peri2(0,5);
    Point peri3(5,0);
    Triangle tr1(peri1, peri2, peri3);
    std::cout << tr1.perimeter() << std::endl;
    std::cout << tr1.area() << std::endl;
    Point in(3, 3);
    Point out(3, -3);
    std::cout << tr1.in_triangle(in) << std::endl;
    std::cout << tr1.center().toString() << std::endl;

    Line_segment linter1(peri1, peri3);
    Line_segment linter2(in, out);
    std::cout << intersection(linter1, linter2).toString() << std::endl;

    Point cont1(2,2);
    Point cont2(3,5);
    Point cont3(5,2);
    Triangle conttest(cont1, cont2, cont3);
    std::cout << "disjoint?: " << disjoint(tr1, conttest) << std::endl;
    std::cout << "contains:? " << contains(tr1, conttest) << std::endl;

    Point cont4(3,3);
    Point cont5(3,5);
    Point cont6(5,2);
    Triangle conttest2(cont4, cont5, cont6);
    std::cout << "disjoint?: " << disjoint(tr1, conttest2) << std::endl;
    std::cout << "contains:? " << contains(tr1, conttest2) << std::endl;

    Point cont7(1,3);
    Point cont8(1,1);
    Point cont9(3,1);
    Triangle conttest3(cont7, cont8, cont9);
    std::cout << "disjoint?: " << disjoint(tr1, conttest3) << std::endl;
    std::cout << "contains:? " << contains(tr1, conttest3) << std::endl;

    Point cont10(0,0);
    Point cont11(0,6);
    Point cont12(6,0);
    Triangle conttest4(cont10, cont11, cont12);
    std::cout << "disjoint?: " << disjoint(tr1, conttest4) << std::endl;
    std::cout << "contains:? " << contains(tr1, conttest4) << std::endl;

    Point cont13(0,0);
    Point cont14(0,4);
    Point cont15(4,0);
    Triangle conttest5(cont13, cont14, cont15);
    std::cout << "disjoint?: " << disjoint(tr1, conttest5) << std::endl;
    std::cout << "contains:? " << contains(tr1, conttest5) << std::endl;
    return 0;
}
