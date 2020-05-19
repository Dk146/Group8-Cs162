#include <iostream>
#include <fstream>
#include "student.h"
#include "course.h"
#include "lecturer.h"
#include "class.h"
#include "semester.h"

using namespace std;

int main(){
    
    Semester semester;
    ifstream fin;
    ofstream fout;
    
    semester.loadStudentsFromCSV(fin);
    semester.loadLecturersFromCSV(fin);
    semester.loadCoursesFromCSV(fin);
    semester.loadStaffsFromCSV(fin);
    
    //semester.loadStudentsFromTxt(fin);
    //semester.loadAllCoursesFromTxt(fin);
    //semester.loadEachCourseFromTxt(fin);
    //semester.loadLecturersFromTxt(fin);
    //semester.loadStaffsFromTxt(fin);
    
    semester.Login();
    //semester.StaffMenu();
    
    semester.loadStudentsToTxt(fout);
    semester.loadAllCoursesToTxt(fout);
    semester.loadEachCourseToTxt(fout);
    semester.loadLecturersToTxt(fout);
    semester.loadStaffsToTxt(fout);
    
    cout << "\nSucceeded\n" << endl;
    return 0;
}

