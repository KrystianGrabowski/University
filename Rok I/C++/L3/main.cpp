#include<iostream>
#include"queue.h"

int main(){
    Queue q1 {"ala", "ma", "kota"};
    std::cout << q1 << std::endl;
    Queue q2(q1);
    std::cout << q2 << std::endl;
    Queue q3;
    q3 = Queue(8);
    Queue q4;
    q4 = q2;
    Queue q5;
    q5 = std::move(q4);
    std::cout << q3 << std::endl;
    std::cout << q2 << std::endl;
    std::cout << q4 << std::endl;
    std::cout << q5 << std::endl;
    return 0;
}
