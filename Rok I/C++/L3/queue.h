#include<iostream>

class Queue{
    int capacity;
    int size;
    int first;
    std::string *Q;

public:
    void insert(std::string);
    std::string get();
    std::string check();
    int size();
}
