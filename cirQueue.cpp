#include "cirQueue.hpp"
#include <iostream>

cQueue::cQueue(){
    first = -1;
    last = -1;
};

void cQueue::enqueue(process* proc){
    if(first == -1 && last == -1){
        first = 0;
        last = 0;
        queue[last] = *proc;
    }
    
    else if((last+1)%MAX_SIZE == first){
        std::cout << "ERROR : QUEUE IS FULL\n";
    }
    
    else{
        last = (last+1)%MAX_SIZE;
        queue[last] = *proc;
    }
};

void cQueue::dequeue(){
    if(first == -1 && last == -1){
        std::cout << "ERROR : UNDERFLOW\n";
    }
    else if(first == last){
        first = -1;
        last = -1;
    }
    else{
        first = (first+1)%MAX_SIZE;
    }
};

void cQueue::display(){
    if(first == -1 && last == -1){
        std::cout << "Queue is empty\n";
    }
    else
        {
            std::cout << "\n\nProcesses in Queue are : \n";
            if(last >= first){
                for(int i = first; i <= last; i++)
                {
                    std::cout << queue[i].getProcessID();
                    std::cout << " | Time Burst : " << queue[i].getTimeBurst();
                    std::cout << " | Priority : " << queue [i].getPriority();
                    std::cout << " | Status : " << queue[i].displayState() << std::endl;
                }
            }
            else{
                for(int i = first; i < MAX_SIZE; i++){
                    std::cout << queue[i].getProcessID();
                    std::cout << " | Time Burst : " << queue[i].getTimeBurst();
                    std::cout << " | Priority : " << queue [i].getPriority();
                    std::cout << " | Status : " << queue[i].displayState() << std::endl;
                }
                for(int i = 0; i <= last; i++){
                    std::cout << queue[i].getProcessID();
                    std::cout << " | Time Burst : " << queue[i].getTimeBurst();
                    std::cout << " | Priority : " << queue [i].getPriority();
                    std::cout << " | Status : " << queue[i].displayState() << std::endl;
                }
            }
        }
};

process* cQueue::getFirst(){
    return &queue[first];
};

bool cQueue::isEmpty(){
    if(first == -1 && last == -1){
        return true;
    }
    return false;
}

int cQueue::getHighestPriority(){
    int highestPriority = 0;
    if(first == -1 && last == -1){
        return highestPriority;
    }
    else
        {
            if(last >= first){
                for(int i = first; i <= last; i++)
                {
                    if(queue[i].getPriority() > highestPriority)
                    {
                        highestPriority = queue[i].getPriority();
                    }
                }
            }
            else{
                for(int i = first; i < MAX_SIZE; i++){
                    if(queue[i].getPriority() > highestPriority)
                    {
                        highestPriority = queue[i].getPriority();
                    }
                }
                for(int i = 0; i <= last; i++){
                    if(queue[i].getPriority() > highestPriority)
                    {
                        highestPriority = queue[i].getPriority();
                    }
                }
            }
        }
    return highestPriority;
};
