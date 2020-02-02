#include<iostream>

class Queue{
    int capacity;
    int current_size;
    int first;
    std::string *Q;

public:
    Queue(int p_capacity);
    Queue();
    Queue(std::initializer_list<std::string> list);
    Queue(const Queue &q);
    Queue(Queue &&q);
    ~Queue();

    Queue& operator=(const Queue &q);
    Queue& operator=(Queue &&q);

    void insert(std::string elem);
    std::string get();
    std::string check();
    int size();

    friend std::ostream& operator<< (std::ostream &os, const Queue &q);
};
