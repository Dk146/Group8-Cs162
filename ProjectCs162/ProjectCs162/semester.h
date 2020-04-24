#ifndef semester_h
#define semester_h

#include "class.h"
#include "student.h"
#include "course.h"
#include "lecturer.h"
#include "include.h"

class Semester{
    string semesterName;
    
    int total_class;
    Class arrClass[15];
    
    int total_course;
    Course arrCourse[50];
    
    int total_lecturer;
    Lecturer arrLecturer[50];
    
public:
    void setTotalClass(int _totalClass);
    void setTotalCourse(int _totalCourse);
    int getTotalClass();
    int getTotalCourse();
    void addStudentToCourse(int _studentID, string _courseID, string class_name);
    void addCourseToClass(string _courseID, string class_name);
};

#endif
