#ifndef class_h
#define class_h

#include "include.h"
#include "student.h"

class Class{
    private:
        Student student[50];
        string ClassName;
        int totalStudent;
    public:
    void settotalStudent(int _totalStudent){
        totalStudent = _totalStudent;
    }
    void setClassName(string _className){
        ClassName = _className;
    }
    string getClassName(){
        return ClassName;
    }
    Student getStudent(int index){
        return student[index];
    }
    int gettotalStudent(){
        return totalStudent;
    }
    Class(){
        totalStudent = 0;
    }
};

#endif
