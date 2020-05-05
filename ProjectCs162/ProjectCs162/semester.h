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
    
    void loadStudentsFromCSV(ifstream& fin); // beginning of the program
    void addCourseToClass(string _courseID, string class_name); // For loading file (Ton)
    void ManuallyaddStudentToClass(); // 7
    void editAnExistingStudent(string _ID); //8
    void RemoveAStudent(string _studentID); // 9
    void changeClass(string _ID); // 10
<<<<<<< HEAD
    void removeACourse(string _courseID); //17  
=======
    void viewListOfClasses(string _className); //11
    void viewListOfStudent(string _ClassName); //12
     void ManuallyAddNewCourse(); //15
    void removeACourse(string _courseID); //17
>>>>>>> 7fd5b25c14f5b9daeb81a7ca8356771e26b70ad0
    void removeAStudentFromACourse(string _studentID, string _courseID, string _className); //18
    void addStudentToCourse(string _studentID, string _courseID, string class_name); //19


    bool isCourseActive(string _courseID); // check Course's status
    bool isStudentActive(string _studentID); // check Student's status
<<<<<<< HEAD
    void loadStudentsFromCSV(ifstream& fin); // beginning 
    void loadLecturersFromCSV(ifstream& fin); //beginning
    void loadStaffsFromCSV(ifstream& fin); // beginning
=======
    

>>>>>>> 7fd5b25c14f5b9daeb81a7ca8356771e26b70ad0
};

#endif
