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

	semester.runProgram(fin, fout);



    return 0;
}

