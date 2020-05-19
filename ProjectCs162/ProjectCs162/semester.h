#ifndef semester_h
#define semester_h

#include "class.h"
#include "student.h"
#include "course.h"
#include "lecturer.h"
#include "include.h"
#include "Staff.h"

class Semester{
    string semesterName;
    
    int total_class;
    Class arrClass[15];
    
    int total_course;
    Course arrCourse[20];
    
    int total_lecturer;
    Lecturer arrLecturer[20];

    int total_staff;
    Staff arrStaff[10];
    
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
    void editAnExistingStudent(); //8
    void RemoveAStudent(); // 9
    void changeClass(); // 10
    void viewListOfClasses(); //11
    void viewListOfStudent(int _pos); //12
    void ManuallyAddNewCourse(); //15
    void editAnExistingCourse(); //16
    void removeACourse(); //17
    void removeAStudentFromACourse(); //18
    void addStudentToCourse(); //19
    void viewListOfCourses(); //20
    void viewListStudentOfCourse(string _CourseName); //21
    void viewProfileStudent(string _studentID);
    void viewProfileStaff(string _staffUser);
    void viewProfileLecturer(string _lecturerID);

    void viewListStudentOfCourse(); //21
    void viewListLecturer(); //23
    
    bool isCourseActive(string _courseID); // check Course's status
    bool isStudentActive(string _studentID); // check Student's status
    string getClassOfStudent(string _studentID);
    Student getStudent(string _ID);
    Course getCourse(string _courseID);
    Class getClass(string _ClassName);
    Staff getStaff(string _StaffUser);
    Lecturer getLecturer(string _LecturerUser);

    // Ton
    void loadStudentsFromCSV(ifstream& fin); // beginning
    void loadLecturersFromCSV(ifstream& fin); //beginning
    void loadStaffsFromCSV(ifstream& fin); // beginning 
    void loadSingleClassFromCSV(ifstream& fin); // 6
    void loadCoursesFromCSV(ifstream& fin); // 14    
    void loadStudentsToTxt(ofstream& fout); // ending
    void loadLecturersToTxt(ofstream& fout); // ending 
    void loadStudentsFromTxt(ifstream& fin); // beginning, condition 2
    void loadLecturersFromTxt(ifstream& fin); // beginning, condition 2 
    // void checkStaffsFromTxt(ifstream& fin); // check username + pass
    void loadAllCoursesToTxt(ofstream& fout); // ending, thong tin chung        
    void loadAllCoursesFromTxt(ifstream& fin); // load khai quat                 
    void loadEachCourseToTxt(ofstream& fout); // load cu the                     // khi nao biet diem danh thi  
    void loadEachCourseFromTxt(ifstream& fin); // load cu the                    // add vao 2 function nay
    void loadStaffsToTxt(ofstream& fout);
    void loadStaffsFromTxt(ifstream& fin);
    void loadScoreBoard(ifstream& fin);
    void viewScoreOfACourse();


    void StaffMenu(string _username);
    void ClassOption();
    void CourseOption();
    void ScoreboardOption(); // chua lam
    void AttendenceListOption(); // chua lam
    
    void StudentMenu(string _username);
    void CheckIn(string _ID); //
    void viewCheckInResult(string _ID); // chua lam
    void viewSchedule(string _ID); // chua lam
    void viewScore(string _ID); // chua lam
    
    void LecturerMenu();
    void viewCoursesofLecturer();
    void viewAttendanceList(); // chua lam
    void editAnAttendance(); // chua lam
    void editGradeOfAStudent(); // chua lam
    void viewAScoreBoard(); // chua lam
    
    void Login();
    void StaffOption(string _username);
    void StudentOption(string _username);
    void LecturerOption(string _username);
    void changePassStaff(string _username);
    void changePassStudent(string _username);
    void changePassLecturer(string _username);
    bool isStudent(string _username, string _password);
    bool isLecturer(string _username, string _password);
    bool isStaff(string _username, string _password);

    Semester(){
        total_lecturer = 0;
        total_class = 0;
        total_course = 0;
        total_staff = 0;
    }
    
};

#endif
