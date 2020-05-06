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
    getline(fin, skipfirstline, '\n');

    while (fin.good())
    {
        getline(fin, _No, ',');
        getline(fin, _ID, ',');
        getline(fin, _fullname, ',');
        getline(fin, _class, ',');
        getline(fin, _doB, ',');
        getline(fin, _gen, '\n');

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

// for loading file (Ton)
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

    for (int i = 0; i < total_class; ++i){
        if (arrClass[i].getClassName() == _className){
            arrClass[i].addStudent(a);
        }
    }
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
 
//9
void Semester::RemoveAStudent(string _studentID){
    int k = 0;
    for (int i = 0; i < total_class; ++i){
        for (int j = 0; i < arrClass[i].totalStudent; j++){
            if (arrClass[i].student[j].getID() == _studentID){
                arrClass[i].student[j].setStatus(0);
                k = 1;
                break;
            }
        }
        if(k == 1)
            break;
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
                    cout << "Full name of student " << i + 1 << " : " << arrClass[i].student[j].getFullName();
                }
            }
        }
    }
    
}

//15
void Semester::ManuallyAddNewCourse(){
    Course new_course;
    string _No;
    string _ID, _CourseName, _Room, _LUsername, _LName, _LDegree, _Class;
    bool _LGender, _status; // 1 is active, 0 is inactive
    string _startDate, _endDate;
    string _sHour, _sMin, _eHour, _eMin;
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

//17
void Semester::removeACourse(string _courseID){
    for (int i = 0; i < total_course; ++i){
        if (arrCourse[i].getID() == _courseID){
            arrCourse[i].setStatus(0);
            break;
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


void Semester::loadLecturersFromCSV(ifstream& fin)
{
    string link;
    cout << "Please input the link to Lecturers.csv file: ";
    getline(cin, link);
    
    fin.open(link + "Lecturers.csv"); // khai quat

    string skipfirstline, _user, _pass, _name, _gen, _degree;
    bool _gender;

    if (fin.is_open())
    {
        getline(fin, skipfirstline, '\n');

        while (fin.good())
        {
            getline(fin, _user, ',');
            getline(fin, _pass, ',');
            getline(fin, _name, ',');
            getline(fin, _degree, ',');
            getline(fin, _gen, '\n');
            
            if (_gen == "Male") _gender = true;
            else _gender = false;

            Lecturer A;
            A.setUserName(_user);
            A.setPassword(_pass);
            A.setName(_name);
            A.setDegree(_degree);
            A.setGender(_gender);
        
            arrLecturer[total_lecturer] = A;
            ++total_lecturer;
        }
        fin.close();
    }
}

void Semester::loadStaffsFromCSV(ifstream& fin, ofstream& fout)
{
    string link;
    cout << "Please input the link to Staffs.csv: ";
    getline(cin, link);
    
    fin.open(link + "Staffs.csv"); // khai quat

    string skip, _user, _pass, _name, _gen;
    
    if (fin.is_open())
    {
        getline(fin, skip, '\n');
        fout.open("Staffs.txt"); // khai quat
        
        while (fin.good())
        {
            getline(fin, _user, ',');
            getline(fin, _pass, ',');
            getline(fin, _name, ',');
            getline(fin, _gen, '\n');

            fout << _name << endl;
            fout << _user << endl;
            fout << _pass << endl;
            fout << _gen << endl;
        }
        fin.close();
        fout.close();
    }
    else cout << "Cannot open file Staffs.csv";
}


// 6
void Semester::loadSingleClassFromCSV(ifstream& fin)
{
    string link; // co the co hoac khong
    string name;

    cout << "Please input class's name: ";
    getline(cin, name);
    
    for (int i = 0; i < total_class; ++i)
    {
        if (arrClass[i].getClassName() == name)
        {
            cout << "Class already imported! ";
            return;
        }
    }

    arrClass[total_class].setClassName(name);
    
    cout << "Please input the link to " << name << ".csv";
    getline(cin, link);
    
    fin.open(link + name + ".csv");
    if (fin.is_open())
    {
        string skip, id, no, fullname, gen, doB;
        bool gender;

        getline(fin, skip, '\n');
        
        while (fin.good())
        {
            getline(fin, no, ',');
            getline(fin, id, ',');
            getline(fin, fullname, ',');
            getline(fin, gen, ',');
            getline(fin, doB, '\n');

            if (gen == "Male") gender = true;
            else gender = false;

            Student A;
            A.setID(id);
            A.setFullName(fullname);
            A.setGender(gender);
            A.setDoB(doB);
            A.setStatus(true);
            A.createAccount();

            arrClass[total_class].addStudent(A);
        }
        fin.close();
    }
    ++total_class;
    fin.close();
}

//20
void Semester::viewListOfCourses()
{
    for (int i = 0; i < total_course; i++)
    {
        if (arrCourse[i].getStatus() == true)
        {
            cout << i + 1 << " : " << arrCourse[i].getCourseName() << endl;
        }
    }
}
//21
void Semester::viewListStudentOfCourse(string _CourseName)
{
    Student a;
    for (int i = 0; i < total_course; i++)
    {
        if (arrCourse[i].getCourseName() == _CourseName)
        {
            for (int j = 0; j < arrCourse[i].getTotalStudent(); j++)
            {
                a = getStudent(arrCourse[i].c_ListStudent[j]);
                if (a.getStatus() == true)
                    cout << j+1 << ": " << a.getFullName() << " - " << a.getID() << endl;
                else
                    cout << j+1 << ": " << endl;
            }
        }
    }
}

Student Semester::getStudentForCourse(string _ID) {
}

Student Semester::getStudent(string _ID){
    Student a;
    for (int i = 0; i < total_class; ++i){
        for (int j = 0; j < arrClass[i].totalStudent; ++j){
            if (arrClass[i].student[j].getID() == _ID){
                a = arrClass[i].student[j];
                return a;
            }
        }
    }
    return a;
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

void Semester::loadCoursesFromCSV(ifstream& fin)
{
    string link;
    cout << "Please input the link to Courses.csv";
    getline(cin, link);

    fin.open(link + "Courses.csv"); // khai quat
    if (fin.is_open())
    {
        string skip;
        getline(fin, skip, '\n');
        string no, id, c_name, _class, l_user, l_name, l_degree, l_gen, sday, eday, doW, shour, ehour, smin, emin, room;
        bool gender;
        
        while (fin.good())
        {
            getline(fin, no, ',');
            getline(fin, id, ',');
            getline(fin, c_name, ',');
            getline(fin, _class, ',');
            getline(fin, l_user, ',');
            getline(fin, l_name, ',');
            getline(fin, l_degree, ',');
            getline(fin, l_gen, ',');
            if (l_gen == "Male") gender = true;
            else gender = false; 
            getline(fin, sday, ',');
            getline(fin, eday, ',');
            getline(fin, doW, ',');
            getline(fin, shour, ',');
            getline(fin, smin, ',');
            getline(fin, ehour, ',');
            getline(fin, emin, ',');
            getline(fin, room, ',');

            Course a;
            a.setID(id);
            a.setCourseName(c_name);
            a.setClass(_class);
            a.setLUsername(l_user);
            a.setLName(l_name);
            a.setLGender(gender);
            a.setLDegree(l_degree);
            a.setTime(sday, eday, shour, smin, ehour, emin, doW);
            a.setStatus(true);
            a.setTotalStudent(0);

            arrCourse[total_course] = a;
            addCourseToClass(id, _class);
            ++total_course;
        }
    }
}