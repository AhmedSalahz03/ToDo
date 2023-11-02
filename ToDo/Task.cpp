#include <iostream>
#include <qstring>
#include "Task.h"

using namespace std;


Task::Task(std::string Cname) {
	name = Cname;
	done = 0;
}
void Task::setName(string Cname){
	name = Cname;
}
void Task::setDone(bool Cdone) {
	done = Cdone;
}