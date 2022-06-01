#ifndef Process_hpp
#define Process_hpp

#include <stdio.h>
#include <string>

class process {
public:
    enum state{
        RUNNING,
        READY,
        EXIT
    };
    process();
    process(std::string);
    process(std::string, int);
    state getState();
    int getPriority();
    std::string getProcessID();
    int getTimeBurst();
    void setState(state);
    void setTimeBurst(); // Decreases time till process finished
    std::string displayState();
private:
    state status;
    int priority;
    std::string processID;
    int timeBurst; // Estimated time till process finishes execution
};

#endif
