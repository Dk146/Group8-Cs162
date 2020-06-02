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
	int max_class;
    Class* arrClass;
    
    int total_course;
	int max_course;
	Course* arrCourse;
    
    int total_lecturer;
	int max_lecturer;
	Lecturer* arrLecturer;

    int total_staff;
	int max_staff;
	Staff* arrStaff;
    
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
    void changeClass(); // 10                     // da sua
    void viewListOfClasses(); //11
    void viewListOfStudent(int _pos); //12
    void ManuallyAddNewCourse(); //15
    void editAnExistingCourse(); //16
    void removeACourse(); //17
    void removeAStudentFromACourse(); //18
    void addStudentToCourse(); //19
    void viewListOfCourses(); //20
    void viewListStudentOfCourse(int _pos); //21
    void viewProfileStudent(string _studentID);
    void viewProfileStaff(string _staffUser);
    void viewProfileLecturer(string _lecturerID);
    void viewListLecturer(); //23
    
    bool isCourseActive(string _courseID, string _classCourse); // check Course's status
    bool isStudentActive(string _studentID); // check Student's status
    string getClassOfStudent(string _studentID);
    Student getStudent(string _ID);
    Course getCourse(string _courseID, string _className);
    Class getClass(string _ClassName);
    Staff getStaff(string _StaffUser);
    Lecturer getLecturer(string _LecturerUser);
	Course getCourseOfLecturer(string _courseID, string _LUsername);

    // Ton
    void loadStudentsFromCSV(ifstream& fin); // beginning // da sua
    void loadLecturersFromCSV(ifstream& fin); //beginning // da sua
    void loadStaffsFromCSV(ifstream& fin); // beginning   // da sua
    void loadSingleClassFromCSV(ifstream& fin); // 6      // da sua
    void loadCoursesFromCSV(ifstream& fin); // 14         // da sua

    void loadClassesToTxt(ofstream& fout); // ending    
    void loadEachClassToTxt(ofstream& fout);
    void loadClassesFromTxt(ifstream& fin);
    void loadLecturersToTxt(ofstream& fout); // ending 
    void loadEachClassFromTxt(ifstream& fin); // beginning, condition 2
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
    void exportScore(ofstream& fout);
	void exportAttendanceList(ofstream& fout);

    void StaffMenu(string _username);
    void ClassOption();
    void CourseOption();
    void ScoreboardOption(); // chua lam
    void AttendenceListOption(); // chua lam
    
    void StudentMenu(string _username);
    void CheckIn(string _studentID); 
    void viewCheckInResult(string _ID); 
    void viewScheduleOfStudent(string _ID); 
    void viewScore(string _ID); // chua lam
	bool isCourseNow(string _courseID, string _classCourse);
	void viewStudentCourseNow(string _studentID);
	int rdn(int y, int m, int d);
	int getDaysBetween(string sDate, string _Dow);
	int lengthCourse(string _courseID, string _className);
	void getTomorow(int& day, int& month, int& year);
	void getWeekAfter(int& day, int& month, int& year);
	void viewAStudentAttendanceOfACourse(string _studentID, string _courseID, string _className);
    
    void LecturerMenu(string _LUsername);
    void viewCoursesofLecturer(string _LUsername);
    void viewAttendanceList(string _LUsername);
	void viewAttendanceListOfACourse(string _courseID, string _className);
    void editAnAttendance(string _courseID, string _className, string _studentID); // chua lam
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

	void resizeArrClass();
	void resizeArrCourse();
	void resizeArrStaff();
	void resizeArrLecturer();

	void DeallocateAll();

	void runProgram(ifstream& fin, ofstream& fout);

    Semester(){
        total_lecturer = 0;
        total_class = 0;
        total_course = 0;
        total_staff = 0;
		max_class = 15;
		max_staff = 10;
		max_course = 30;
		max_lecturer = 15;
		arrLecturer = new Lecturer[max_lecturer];
		arrClass = new Class[max_class];
		arrStaff = new Staff[max_staff];
		arrCourse = new Course[max_course];
    }
};

#endif
