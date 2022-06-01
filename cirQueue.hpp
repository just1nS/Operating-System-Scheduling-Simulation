#ifndef cirQueue_hpp
#define cirQueue_hpp

#include <stdio.h>
#include "Process.hpp"

#define MAX_SIZE 10

//Circular Queue
class cQueue{
public:
    cQueue();
    void enqueue(process*);
    void dequeue();
    void display();
    process* getFirst(); // Returns front process
    bool isEmpty();
    int getHighestPriority(); //Returns highest process priority value
private:
    process queue[MAX_SIZE];
    int first;
    int last;
};

#endif 
