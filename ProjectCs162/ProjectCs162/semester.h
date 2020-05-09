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
    
    void addCourseToClass(string _courseID, string class_name); // For loading file (Ton)
    void ManuallyaddStudentToClass(); // 7
    void editAnExistingStudent(string _ID); //8
    void RemoveAStudent(string _studentID); // 9
    void changeClass(string _ID); // 10
    void viewListOfClasses(); //11
    void viewListOfStudent(string _ClassName); //12
    void ManuallyAddNewCourse(); //15
    void removeACourse(string _courseID); //17
    void removeAStudentFromACourse(string _studentID, string _courseID, string _className); //18
    void addStudentToCourse(string _studentID, string _courseID, string class_name); //19
    void viewListOfCourses(); //20
    void viewListStudentOfCourse(string _CourseName); //21
    Student getStudentForCourse(string _ID);    
    bool isCourseActive(string _courseID); // check Course's status
    bool isStudentActive(string _studentID); // check Student's status
    Student getStudent(string _ID);
    Course getCourse(string _courseID);
    Class getClass(string _ClassName);

    // Ton
    void loadStudentsFromCSV(ifstream& fin); // beginning
    void loadLecturersFromCSV(ifstream& fin); //beginning
    void loadStaffsFromCSV(ifstream& fin, ofstream& fout); // beginning 
    void loadSingleClassFromCSV(ifstream& fin); // 6
    void loadCoursesFromCSV(ifstream& fin); // 14
    
    void loadStudentsToTxt(ofstream& fout); // ending
    void loadLecturersToTxt(ofstream& fout); // ending
    void loadCoursesToTxt(ofstream& fout); // ending
    void loadStudentsFromTxt(ifstream& fin); // beginning, condition 2
    void loadLecturersFromTxt(ifstream& fin); // beginning, condition 2 
    

};

#endif
