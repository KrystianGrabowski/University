#include<iostream>

class Queue{
    int capacity;
    int current_size;
    int first;
    std::string *Q;

public:
    Queue(int);
    Queue();
    Queue(std::initializer_list<std::string>);
    Queue(const Queue&);
    Queue(Queue&&);
    ~Queue();

    Queue& operator=(const Queue&);
    Queue& operator=(Queue&&);

    void insert(std::string);
    std::string get();
    std::string check();
    int size();

    friend std::ostream& operator<< (std::ostream&, const Queue&);
};
