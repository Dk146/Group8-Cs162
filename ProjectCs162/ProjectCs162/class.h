#ifndef class_h
#define class_h

#include "include.h"
#include "student.h"

class Class{
    private:
    
        string ClassName;
    
    public:
    
    int totalStudent;
	int max_student;
	Student* student;
    
    void settotalStudent(int _totalStudent);
    void setClassName(string _className);
    string getClassName();
    void addStudent(Student new_student);

	void resizeClass();

    Class(){
        totalStudent = 0;
		max_student = 40;
		student = new Student[max_student];
	}
};

#endif
