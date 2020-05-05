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
void Semester::addStudentToCourse(string _studentID, string _courseID, string class_name){
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

// 7
void Semester::ManuallyaddStudentToClass()
{
    int _No;
    string _ID, _fullname, _DoB;
    string _userName, _password;
    bool _gender;
    string _className;

    Student a;
    cout << "No: ";
    cin >> _No;
    a.setNo(_No);
    cout << "ID: ";
    cin >> _ID;
    a.setID(_ID);
    cout << "Fullname: ";
    getline(cin, _fullname);
    a.setFullName(_fullname);
    cout << "Date of birth: ";
    getline(cin, _DoB);
    a.setDoB(_DoB);
    cout << "Gender: ";
    cin >> _gender;
    a.setGender(_gender);
    a.createAccount();
    cout << "Which class does this student enroll in? ";
    getline(cin, _className);

    for (int i = 0; i < total_class; ++i)
    {
        if (arrClass[i].getClassName() == _className)
        {
            arrClass[i].addStudent(a);
        }
    }
    // Missing the output to txt file, saved for later.
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
void Semester::editAnExistingStudent(string _ID)
{
    for (int i = 0; i < total_class; ++i)
    {
        for (int j = 0; j < arrClass[i].totalStudent; ++i)
        {
            if (arrClass[i].student[j].getID() == _ID)
            {
                string _fullname, _doB, _nclass;
                int choose;
                do
                {
                    cout << "Which do you want to perform?\n "
                        << "1. Change student's name. \n"
                        << "2. Change student's date of birth. \n"                       
                        << "3. Exit. \n";
                    cin >> choose;
                    switch (choose)
                    {
                    case 1:
                        cout << "Input student's new full name: ";
                        getline(cin, _fullname);
                        arrClass[i].student[j].setFullName(_fullname);
                    case 2:
                        cout << "Input student's new date of birth: ";
                        getline(cin, _doB);
                        arrClass[i].student[j].setDoB(_doB);
                        break;
                    case 3:
                        break;
                    }
                } while (choose != 4);
            }
        }
    }
}
 
// 10
void Semester::changeClass(string _ID)
{
    string _newclass;
    int x = 0, y = 0;
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

//17
void Semester::removeACourse(string _courseID){
    for (int i = 0; i < total_course; ++i){
        if (arrCourse[i].getID() == _courseID){
            arrCourse[i].setStatus(0);
        }
    }
}

//18
void Semester::removeAStudentFromACourse(string _studentID, string _courseID, string _className){
    int pos_c = 0;
    int pos_s = 0;
    int k = 0;
    for (int i = 0; i < total_class; ++i){
        if (arrClass[i].getClassName() == _className){
            pos_c = i;
            for (int j = 0; j < arrClass[i].totalStudent; ++j){
                if (arrClass[i].student[j].getID() == _studentID){
                    pos_s = j;
                    k = arrClass[i].student[j].getNumberofCourse();
                    break;
                }
            }
            break;
        }
    }
    for (int i = 0; i < k; ++i){
        if (arrClass[pos_c].student[pos_s].s_ListCourse[i] == _courseID){
            for (int j = i; j < k-1; ++j){
                arrClass[pos_c].student[pos_s].s_ListCourse[j] = arrClass[pos_c].student[pos_s].s_ListCourse[j+1];
            }
            --k;
            arrClass[pos_c].student[pos_s].numberofCourse = k;
        }
    }
    for (int i = 0; i < total_course; ++i){
        if (arrCourse[i].getID() == _courseID){
            for (int j = 0; j < arrCourse[i].c_totalStudent; ++j){
                if (arrCourse[i].c_ListStudent[j] == _studentID){
                    for (int z = j; z < arrCourse[i].c_totalStudent-1; ++z){
                        arrCourse[i].c_ListStudent[z] = arrCourse[i].c_ListStudent[z+1];
                    }
                    --arrCourse[i].c_totalStudent;
                    break;
                }
            }
            break;
        }
    }
}



void Semester::loadStudentsFromCSV(ifstream& fin)
{
    string link;
    cout << "Please input the link to csv file: ";
    getline(cin, link);

    fin.open(link + "Students.csv"); // cai nay sua tuy theo hoan canh, t de dang khai quat cho de hieu

    string skipfirstline;
    string _No, _ID, _gen;
    string _fullname, _class, _doB;
    bool _gender;
    for (int i = 0; i < 6; ++i)
        getline(fin, skipfirstline, ',');

    while (fin.good())
    {
        getline(fin, _No, ',');
        getline(fin, _ID, ',');
        getline(fin, _fullname, ',');
        getline(fin, _class, ',');
        getline(fin, _doB, ',');
        getline(fin, _gen, ',');

        if (_gen == "Male") _gender = true;
        else _gender = false;

        Student A;
        A.setID(_ID);
        A.setFullName(_fullname);
        A.setDoB(_doB);
        A.setGender(_gender);
        A.setStatus(true);

        A.createAccount();

        int exist = 0;
        for (int i = 0; i < total_class; ++i)
        {
            if (arrClass[i].getClassName() == _class)
            {
                arrClass[i].student[arrClass[i].totalStudent] = A;
                exist = 1;
                ++arrClass[i].totalStudent;
            }
        }

        if (exist == 0)
        {
            arrClass[total_class].setClassName(_class);
            arrClass[total_class].addStudent(A);
            ++total_class;
        }
    }
    fin.close();

}


//check 
bool Semester::isCourseActive(string _courseID) {
    for (int i = 0; i < total_course; ++i) {
        if (arrCourse[i].getID() == _courseID) {
            if (arrCourse[i].getStatus() == true)
                return true;
            return false;
        }
    }
    return false;
}
//check
bool Semester::isStudentActive(string _studentID) {
    for (int i = 0; i < total_class; ++i) {
        for (int j = 0; j < arrClass[i].totalStudent; ++j) {
            if (arrClass[i].student[j].getID() == _studentID) {
                if (arrClass[i].student[j].getStatus() == 1)
                    return true;
                else
                    return false;
            }
        }
    }
    return false;
}
//11
void Semester::viewListOfClasses(string _className)
{
    for (int i = 0; i < total_class; i++)
    {
        cout << i << ": " << arrClass[i].getClassName() << endl;
    }

}
//12
void Semester::viewListOfStudent(string _ClassName)       
{
   
    for (int i = 0; i < total_class; ++i)
    {
        if (_ClassName==arrClass[i].getClassName())
        {
            for (int j = 0; j <arrClass[i].totalStudent; j++)
            {
                if (arrClass[i].student[j].getStatus() == 1)
                {
                    cout << "Full name of student " << j + 1 << " : " << arrClass[i].student[j].getFullName();
                }
            }
        }
    }
    
}

//20
void Semester::viewListOfCourses()
{
    for (int i = 0; i < total_course; i++)
    {
        if (isCourseActive(arrCourse[i].getID()) == true)
        {
            cout << i + 1 << " : " << arrCourse[i].getCourseName() << endl;
        }
    }
}
//21
void Semester::viewListStudentOfCourse(string _CourseName)
{
    for (int i = 0; i < total_course; i++)
    {
        if (_CourseName == arrCourse[i].getCourseName())
        {
            for (int j = 0; j < arrCourse[i].getTotalStudent; j++)
            {
                cout << j + 1 << " : " << arrCourse[i]. << endl;
            }
        }
    }

}

void Semester::getStudent(string _ID)
{

}