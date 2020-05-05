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
    
    void setSemesterName(string _semesterName);
    void setTotalClass(int _totalClass);
    void setTotalCourse(int _totalCourse);
    void setTotalLecturer(int _totalLecturer);
    
    string getSemesterName();
    int getTotalClass();
    int getTotalCourse();
    int getTotalLecturer();
    
    void addStudentToCourse(string _studentID, string _courseID, string class_name); //19
    void addCourseToClass(string _courseID, string class_name); // For loading file (Ton)
    void ManuallyAddNewCourse(); //15
    void ManuallyaddStudentToClass(); // 7
    void editAnExistingStudent(string _ID); //8
    void changeClass(string _ID); // 10
    void removeACourse(string _courseID); //17
    void removeAStudentFromACourse(int _studentID, string _courseID, string _className); //18
    void loadStudentsFromCSV(ifstream& fin); // beginning of the program
    void removeAStudentFromACourse(string _studentID, string _courseID, string _className); //18
    void viewListOfClasses(string _className); //11
    void viewListOfStudent(string _ClassName); //12
    void viewListOfCourses(); //20 
    void viewListStudentOfCourse(string _CourseName); //21
    bool isCourseActive(string _courseID); // check Course's status
    bool isStudentActive(string _studentID); // check Student's status
    void getStudent(string _ID);// get student name from id
    

};

#endif
