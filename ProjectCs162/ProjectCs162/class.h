#ifndef class_h
#define class_h

#include "include.h"
#include "student.h"

class Class{
    private:
    
        string ClassName;
    
    public:
    
    int totalStudent;
    Student student[50];

    void settotalStudent(int _totalStudent);
    void setClassName(string _className);
    string getClassName();
    void addStudent(Student new_student);
    
    Class(){
        totalStudent = 0;
    }
};

#endif
