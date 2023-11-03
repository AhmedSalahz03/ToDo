

#ifndef TASK_H
#define TASK_H

#include <qstring>

class Task {
public:
    std::string name;
    bool done;

public:
    Task(std::string);
    void setName(std::string);
    void setDone(bool);
};

#endif

