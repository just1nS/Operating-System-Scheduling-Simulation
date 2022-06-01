#include "Process.hpp"
#include <time.h>



process::process(){
    processID = "NULL";
    timeBurst = rand()%50+5;
    status = state::READY;
    priority = rand()%5+1;
};

process::process(std::string processID){
    this->processID = processID;
    timeBurst = rand()%50+5;
    status = state::READY;
    priority = rand()%5+1;
};

process::process(std::string processID, int priority){
    this->processID = processID;
    timeBurst = rand()%50+5;
    status = state::READY;
    this->priority = priority;
};

int process::getTimeBurst(){
    return timeBurst;
};

std::string process::getProcessID(){
    return processID;
};

process::state process::getState(){
    return status;
};

int process::getPriority(){
    return priority;
};

void process::setState(state status){
    this->status = status;
};

void process::setTimeBurst(){
    timeBurst--;
}

std::string process::displayState(){
    switch (status) {
        case READY:
            return ("READY");
            break;
        case RUNNING:
            return ("RUNNING");
            break;
        case EXIT:
            return ("FINISHED - EXIT");
        default:
            return ("ERROR");
            break;
    }
};
