#include<iostream>
#include"queue.h"

int test(Queue &q){
    int choice;
    std::string arg;

    while(true){
        std::cout << "1.Insert" << std::endl;
        std::cout << "2.Get"    << std::endl;
        std::cout << "3.Check"  << std::endl;
        std::cout << "QUEUE -> " << q << std::endl;
        std::cin >> choice;
        switch(choice){
            case 1:
                std::cout << "Enter value: ";
                std::cin >> arg;
                q.insert(arg);
            break;
            case 2:
                std::cout << q.get() << std::endl;
                getchar(); getchar();
            break;
            case 3:
                std::cout << q.check() << std::endl;
                getchar(); getchar();
            break;
            default:
                std::cerr << "Wrong number!" << std::endl;
                exit(0);
        }
        system("clear");

    }

}

int main(){
    Queue c1;
    test(c1);
    return 0;
}
