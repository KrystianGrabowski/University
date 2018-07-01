#include<iostream>
#include"queue.h"

Queue::Queue(int p_capacity)
    : capacity(p_capacity), current_size(0), first(0){
    Q = new std::string[p_capacity];
}

Queue::Queue(): Queue(4){}

Queue::Queue(std::initializer_list<std::string> list)
    : first(0) {
    capacity = list.size();
    current_size = 0;
    Q = new std::string[capacity];
    for (std::string elem : list){
        Q[current_size] = elem;
        current_size++;
    }
}

Queue::Queue(const Queue &q)
    :capacity(q.capacity), current_size(q.current_size), first(q.first) {
    Q = new std::string[capacity];
    for (int i=0; i<capacity; i++){
        Q[i] = q.Q[i];
    }
}

Queue::Queue(Queue &&q)
    :capacity(q.capacity), current_size(q.current_size), first(q.first), Q(q.Q){
    q.Q = nullptr;
    q.capacity = 0;
    q.current_size = 0;
    q.first = 0;
}

Queue& Queue::operator=(const Queue &q){
    if(this != &q){
        capacity = q.capacity;
        current_size = q.current_size;
        first = q.first;
        delete [] Q;
        Q = new std::string[capacity];
        for (int i=0; i<capacity; i++){
            Q[i] = q.Q[i];
        }
    }
    return *this;
}

Queue& Queue::operator=(Queue &&q){
    if(this != &q){
        capacity = q.capacity;
        current_size = q.current_size;
        first = q.first;
        delete [] Q;
        Q = q.Q;

        q.Q = nullptr;
        q.capacity = 0;
        q.current_size = 0;
        q.first = 0;
    }
    return *this;
}

std::ostream& operator<< (std::ostream &os, const Queue &q){
    os << "[";
    int iter = q.first;
    int number = q.current_size;
    while(number > 0){
        os << q.Q[iter];
        if (number != 1){
            os << ", ";
        }
        number--;
        iter++;
        if (iter == q.capacity){
            iter == 0;
        }
    }
    os << "]";
    return os;
}


Queue::~Queue(){
    delete[] Q;
}
