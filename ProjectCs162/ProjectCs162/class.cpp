#include "class.h"

void Class::settotalStudent(int _totalStudent){
    totalStudent = _totalStudent;
}
void Class::setClassName(string _className){
    ClassName = _className;
}
string Class::getClassName(){
    return ClassName;
}
void Class::addStudent(Student new_student){
    student[totalStudent] = new_student;
    ++totalStudent;
}
