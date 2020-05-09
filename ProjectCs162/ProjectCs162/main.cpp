#include <iostream>
#include <fstream>
#include "student.h"
#include "course.h"
#include "lecturer.h"
#include "class.h"
#include "semester.h"

using namespace std;

int main(){
    
//  Note: Khi tao semester moi, phai set day du moi thu bat dau = 0
//   Phai chay loop set all total (total student, total class, ...) = 0


//    ifstream fin;
//    ofstream fout;
//    int x;
//
//    fin.open("D:\Check.txt");
//    if (fin.is_open()) fin >> x;
//    else cout << "Cannot open file check! ";
//
//    if (x == 0)
//    {
//        // loadStudentsFromCsv (fin);
//        // loadLecturersFromCsv (fin);
//        // loadStaffFromCsv (fin);
//        // x = 1;  
//    }
//    else if (x == 1)
//    {
//        // loadStudentsFromTxt (fin);
//        // loadLecturersFromTxt (fin);
//        // loadStaffFromCsv (fin);
//    }
    Semester semester;
    ifstream fin;
    ofstream fout;
    semester.loadStudentsFromCSV(fin);
    semester.loadLecturersFromCSV(fin);
    semester.loadCoursesFromCSV(fin);
    semester.StaffMenu();
    

    return 0;
}

