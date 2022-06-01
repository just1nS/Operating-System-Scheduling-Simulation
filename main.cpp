#include <iostream>
#include <pthread.h>
#include "cirQueue.hpp"
#include "Process.hpp"

using namespace std;

void dispatcher(process*, cQueue*);
void scheduler(cQueue*);
void *selectNextProcess(void*);

int main() {
    
    srand(static_cast<unsigned>(time(0)));
    
    // Creation of simulated processes, initiliazed with random execution timebursts and priorities
    process *p1 = new process("Process 1");
    process *p2 = new process("Process 2");
    process *p3 = new process("Process 3");
    process *p4 = new process("Process 4");
    process *p5 = new process("Process 5");
    process *p6 = new process("Process 6");
    process *p7 = new process("Process 7");
    
    // Circular queue used to store readied processes
    cQueue* readyQueue = new cQueue;
    
    readyQueue->enqueue(p1);
    readyQueue->enqueue(p2);
    readyQueue->enqueue(p3);
    readyQueue->enqueue(p4);
    readyQueue->enqueue(p5);
    readyQueue->enqueue(p6);
    readyQueue->enqueue(p7);
    
    
    
    scheduler(readyQueue);
    
    return 0;
}

// Dispatcher function: Executes process and transitions state
void dispatcher(process* proc, cQueue* readyQueue){
    
    // Time Quantum, simulated 10 milliseconds of processor time per function
    int timeSlice = 10;
    
    proc->setState(process::RUNNING); // State of process is transitioned to "Running"
    readyQueue->display();
    
    // PROCESS EXECUTION
    while(timeSlice > 0){
        proc->setTimeBurst(); // Decreases timeslice and time left for execution
        timeSlice--;
        if(proc->getTimeBurst() <= 0){ // If program finishes execution
            proc->setState(process::EXIT); // Process state is transitioned to "Exit/Finished"
            readyQueue->display();
            readyQueue->dequeue(); // Removes process from readied queue
            return;
        };
    };
    
    // Time Quantum expires
    // Process state is transititioned back to "Ready" and placed in readied queue
    readyQueue->dequeue();
    proc->setState(process::READY);
    readyQueue->enqueue(proc);
    cout << "\nTIME SLICE EXPIRED - EXECUTING NEXT PROCESS\n";
};

// Scheduler handles selecting which process in the queue is next for execution, then hands it to the dispatcher
// Follows a Round Robin with Priority algorithm
void scheduler(cQueue* readyQueue){
    while(!readyQueue->isEmpty()){
        // Creates thread to select the next process to be executed
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, selectNextProcess, readyQueue);
        pthread_join(thread_id, NULL);
        dispatcher(readyQueue->getFirst(), readyQueue);
    };
};

//Selects the next process to be executed, based on priority
//Ran as a seperate thread
void *selectNextProcess(void* rQueue){
    cout<<"SELECTING NEXT PROCESS";
    cQueue* readyQueue = (cQueue*)rQueue;
    //Searches queue to find highest priority processes and places them at the front
        while((readyQueue->getFirst())->getPriority() < readyQueue->getHighestPriority()){
            process* temp = readyQueue->getFirst();
            readyQueue->dequeue();
            readyQueue->enqueue(temp);
        }
    cout << ": " << (readyQueue->getFirst())->getProcessID() << endl;
    return NULL;
};
