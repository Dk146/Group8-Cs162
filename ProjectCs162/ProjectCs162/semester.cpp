#include "semester.h"

void Semester::setSemesterName(string _semesterName){
    semesterName = _semesterName;
}

void Semester::setTotalLecturer(int _totalLecturer){
    total_lecturer = _totalLecturer;
}

void Semester::setTotalClass(int _totalClass){
    total_class = _totalClass;
}

void Semester::setTotalCourse(int _totalCourse){
    total_course = _totalCourse;
}

string Semester::getSemesterName(){
    return semesterName;
}

int Semester::getTotalClass(){
    return total_class;
}

int Semester::getTotalCourse(){
    return total_course;
}

int Semester::getTotalLecturer(){
    return total_lecturer;
}

//19
void Semester::addStudentToCourse(int _studentID, string _courseID, string class_name){
    for (int i = 0; i < total_class; ++i){
        if(arrClass[i].getClassName() == class_name){
            for (int j = 0; j < arrClass[i].totalStudent; ++j){
                if(arrClass[i].student[j].getID() == _studentID){
                    int k = arrClass[i].student[j].numberofCourse;
                    arrClass[i].student[j].s_ListCourse[k] = _courseID;
                    k++;
                    arrClass[i].student[j].numberofCourse = k;
                    break;;
                }
            }
            break;
        }
    }
    for (int i = 0; i < total_course; ++i){
        if(arrCourse[i].getID() == _courseID){
            int h = arrCourse[i].c_totalStudent;
            arrCourse[i].c_ListStudent[h] = _studentID;
            ++h;
            arrCourse[i].c_totalStudent = h;
            break;
        }
    }
}

void Semester::addCourseToClass(string _courseID, string class_name){
    int pos_class = 0;
    int s_inClass = 0;
    for (int i = 0; i < total_class; ++i){
        if(arrClass[i].getClassName() == class_name){
            pos_class = i;
            s_inClass = arrClass[i].totalStudent;
            for(int j = 0; j < arrClass[i].totalStudent; ++i){
                int temp = arrClass[i].student[j].numberofCourse;
                arrClass[i].student[j].s_ListCourse[temp] = _courseID;
                temp++;
                arrClass[i].student[j].numberofCourse = temp;
            }
            break;
        }
    }
    for (int i = 0; i < total_course; ++i){
        int s_inCourse = arrCourse[i].c_totalStudent;
        if (arrCourse[i].getID() == _courseID){
            int temp = 0;
            for (int j = s_inCourse; j < s_inCourse + s_inClass; ++j){
                arrCourse[i].c_ListStudent[j] = arrClass[pos_class].student[temp++].getID();
            }
            arrCourse[i].c_totalStudent = s_inCourse + s_inClass;
            break;
        }
    }
}


//void Semester::ManuallyAddNewCourse(){
//    Course a;
//    int _No;
//    string _ID, _CName, _Room, _LUsername, _LName, _LDegree, _Class;
//    bool c_LGender, c_status; // 1 is active, 0 is inactive
//    int _year, _month, _day, _sHour, _sMin, _eHour, _eMin;
//    string _DoW;
//    
//    cout << "No: ";
//    cin >> _No;
//    a.setNo(_No);
//    cout << "ID:";
//    cin >> _ID;
//    a.setID(_ID);
//    cout << "Course's name: ";
//    cin >> _CName;
//    a.setNam
//}

// 7
void Semester::addStudentToClass()
{
    int No, ID;
    string lastname, firstname, doB;
    string username, password;
    bool gender;
    string class_name;

    Student a;
    cout << "No: ";
    cin >> No;
    a.setNo(No);
    cout << "ID: ";
    cin >> ID;
    a.setID(ID);
    cout << "Last name: ";
    getline(cin, lastname);
    a.setLastName(lastname);
    cout << "First name: ";
    getline(cin, firstname);
    a.setFirstName(firstname);
    cout << "Date of birth: ";
    getline(cin, doB);
    a.setDoB(doB);
    a.createAccount();
    cout << "Which class does this student enroll in? ";
    getline(cin, class_name);

    for (int i = 0; i < total_class; ++i)
    {
        if (arrClass[i].getClassName() == class_name)
        {
            arrClass[i].addStudent(a);
        }
    }
}

//15
void Semester::ManuallyAddNewCourse(){
    Course new_course;
    int _No;
    string _ID, _CourseName, _Room, _LUsername, _LName, _LDegree, _Class;
    bool _LGender, _status; // 1 is active, 0 is inactive
    string _startDate, _endDate;
    int _sHour, _sMin, _eHour, _eMin;
    string _DoW;

    cout << "No: ";
    cin >> _No;
    new_course.setNo(_No);
    cout << "ID:";
    cin >> _ID;
    new_course.setID(_ID);
    cout << "Course name: ";
    cin >> _CourseName;
    new_course.setCourseName(_CourseName);
    cout << "Class name: ";
    cin >> _Class;
    new_course.setClass(_Class);
    cout << "Lecturer Username:";
    cin >> _LUsername;
    new_course.setLUsername(_LUsername);
    cout << "Lecturer Name :";
    cin >> _LName;
    new_course.setLDegree(_LName);
    cout << "Lecturer Degree's: ";
    cin >> _LDegree;
    new_course.setLDegree(_LDegree);
    cout << "Lecturer Gender: ";
    cin >> _LGender;
    new_course.setLGender(_LGender);
    new_course.setStatus(1);
    new_course.setLGender(_LGender);
    _status = 1;
    new_course.setStatus(_status);
    cout << "Start Date: ";
    cin >> _startDate;
    new_course.setStartDate(_startDate);
    cout << "End Date: ";
    cin >> _endDate;
    new_course.setEndDate(_endDate);
    cout << "Start Hour: ";
    cin >> _sHour;
    new_course.setsHour(_sHour);
    cout << "Start Minute: ";
    cin >> _sMin;
    new_course.setsMin(_sMin);
    cout << "End Hour: ";
    cin >> _eHour;
    new_course.seteHour(_eHour);
    cout << "End Minute: ";
    cin >> _eMin;
    new_course.seteMin(_eMin);
    cout << "Day of week: ";
    cin >> _DoW;
    new_course.setDoW(_DoW);
    int k = total_course;
    arrCourse[k] = new_course;
    k++;
    total_course = k;
}

// 8
void Semester::editAnExistingStudent(int _ID)
{
    for (int i = 0; i < total_class; ++i)
    {
        for (int j = 0; j < arrClass[i].totalStudent; ++i)
        {
            if (arrClass[i].student[j].getID() == _ID)
            {
                string _firstname, _lastname, _doB, _nclass;
                int choose;
                do
                {
                    cout << "Which do you want to perform?\n "
                        << "1. Change student's first name.\n"
                        << "2. Change student's last name.\n"
                        << "3. Change student's date of birth. \n"                       
                        << "4. Exit. \n";
                    cin >> choose;
                    switch (choose)
                    {
                    case 1: 
                        cout << "Input student's new first name: ";
                        getline(cin, _firstname);
                        arrClass[i].student[j].setFirstName(_firstname);
                        break;
                    case 2:                       
                        cout << "Input student's new last name: ";
                        getline(cin, _lastname);
                        arrClass[i].student[j].setLastName(_lastname);
                        break;
                    case 3:
                        cout << "Input student's new date of birth: ";
                        getline(cin, _doB);
                        arrClass[i].student[j].setDoB(_doB);
                        break;
                    case 4:
                        break;
                    }
                } while (choose != 4);
            }
        }
    }
}
<<<<<<< HEAD
 
// 10
void Semester::changeClass(int _ID)
{
    string _newclass;
    int x, y;
    cout << "Which class does this student move to? ";
    getline(cin, _newclass);
    for (int i = 0; i < total_class; ++i)
    {
        for (int j = 0; j < arrClass[i].totalStudent; ++j)
        {
            if (arrClass[i].student[j].getID() == _ID)
            {
                x = i;
                y = j;
                for (int z = 0; z < total_class; ++z)
                {
                    if (arrClass[z].getClassName() == _newclass)
                    {
                        arrClass[z].addStudent(arrClass[i].student[j]);
                    }
                }
            }
        }
    }
    
    arrClass[x].totalStudent -= 1;
    int index = y + 1;
    while (index < arrClass[x].totalStudent)
    {
        arrClass[x].student[y] = arrClass[x].student[index];
        ++y;
        ++index;
    }
}
=======

//17
void Semester::removeACourse(string _courseID){
    for (int i = 0; i < total_course; ++i){
        if (arrCourse[i].getID() == _courseID){
            arrCourse[i].setStatus(0);
        }
    }
}
>>>>>>> 325c7ff4866303e9aa1fda113e8735b7caba7f91
