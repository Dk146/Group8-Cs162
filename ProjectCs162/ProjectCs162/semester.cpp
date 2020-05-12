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

    string skipfirstline, line;
    string _No, _ID, _gen;
    string _fullname, _class, _doB;
    bool _gender;
    getline(fin, skipfirstline, '\n');

    while (getline(fin, line))
    {
        stringstream ss(line);
        getline(ss, _No, ',');
        getline(ss, _ID, ',');
        getline(ss, _fullname, ',');
        getline(ss, _class, ',');
        getline(ss, _doB, ',');
        getline(ss, _gen, ',');

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
                arrClass[i].addStudent(A);
                exist = 1;
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
void Semester::addCourseToClass(string _courseID, string _className){
    int pos_Course = 0;
    int pos_Class = 0;
    int pos_Lecturer = 0;
    for (int i = 0; i < total_course; ++i){
        if (arrCourse[i].getID() == _courseID){
            pos_Course = i;
            break;
        }
    }
    for (int i = 0; i < total_class; ++i){
        if (arrClass[i].getClassName() == _className){
            pos_Class = i;
            break;
        }
    }
    
    Course &_course(arrCourse[pos_Course]);
    Class &_class(arrClass[pos_Class]);
    
    for (int i = 0; i < total_lecturer; ++i){
        if(arrLecturer[i].getName() == _course.getLName()){
            pos_Lecturer = i;
            break;
        }
    }
    
    Lecturer &_lecturer(arrLecturer[pos_Lecturer]);
    _lecturer.L_ListCourse[_lecturer.L_totalCourse++] = _courseID;
    
    for (int i = 0; i < _class.totalStudent; ++i){
        _class.student[i].s_ListCourse[_class.student[i].numberofCourse++] = _courseID;
    }
    for (int i = 0; i < _class.totalStudent; ++i){
        _course.c_ListStudent[i] = _class.student[i].getID();
    }
    _course.c_totalStudent = _class.totalStudent;
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
    cin.ignore();
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
    cin.ignore();
    getline(cin, _className);

    for (int i = 0; i < total_class; ++i){
        if (arrClass[i].getClassName() == _className){
            arrClass[i].addStudent(a);
            break;
        }
    }
}

// 8
void Semester::editAnExistingStudent()
{
    string _ID;
    cout << "Student ID: ";
    cin >> _ID;
    for (int i = 0; i < total_class; ++i)
    {
        for (int j = 0; j < arrClass[i].totalStudent; ++j)
        {
            if (arrClass[i].student[j].getID() == _ID)
            {
                string _fullname, _doB, _nclass;
                int choose;
                do
                {
                    cout << "Which do you want to perform? \n"
                        << "1. Change student's name. \n"
                        << "2. Change student's date of birth. \n"                       
                        << "3. Exit. \n";
                    cin >> choose;
                    switch (choose)
                    {
                    case 1:
                        cout << "Input student's new full name: ";
                        cin.ignore();
                        getline(cin, _fullname);
                        arrClass[i].student[j].setFullName(_fullname);
                        break;
                    case 2:
                        cout << "Input student's new date of birth: ";
                        cin.ignore();
                        getline(cin, _doB);
                        arrClass[i].student[j].setDoB(_doB);
                        break;
                    case 3:
                        break;
                    }
                } while (choose!=3);
            }
        }
    }
}
 
//9
void Semester::RemoveAStudent(){
    string _studentID;
    cout << "Student ID: ";
    cin >> _studentID;
    int k = 0;
    for (int i = 0; i < total_class; ++i){
        for (int j = 0; j < arrClass[i].totalStudent; j++){
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
void Semester::changeClass()
{
    int k = 0;
    string _ID;
    cout << "Student ID: ";
    cin >> _ID;
    if (isStudentActive(_ID) == false){
        cout << "This ID does not exist!" << endl;
        return;
    }
    string _newclass;
    int x = 0, y = 0;
    cout << "Which class does this student move to? ";
    cin.ignore();
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
                        k = 1;
                        break;
                    }
                }
                break;
            }
        }
        if(k==1)
            break;
    }
    
    arrClass[x].totalStudent -= 1;
    while (y < arrClass[x].totalStudent)
    {
        arrClass[x].student[y] = arrClass[x].student[y+1];
        ++y;
    }
}

//11
void Semester::viewListOfClasses()
{
    cout << "List of classes: " << endl;
    for (int i = 0; i < total_class; i++)
    {
        cout << i << ": " << arrClass[i].getClassName() << endl;
    }

}

//12
void Semester::viewListOfStudent()
{
    string _ClassName;
    cout << "View Class: " ;
    cin >> _ClassName;
    cout << "List of student in class " << _ClassName << ": \n";
    for (int i = 0; i < total_class; ++i)
    {
        if (_ClassName==arrClass[i].getClassName())
        {
            for (int j = 0; j <arrClass[i].totalStudent; j++)
            {
                if (arrClass[i].student[j].getStatus() == true)
                {
                    cout << "Student " << j + 1 << " : " << arrClass[i].student[j].getID()  << " - " << arrClass[i].student[j].getFullName() << endl;
                }
            }
        }
    }
    
}

//15
void Semester::ManuallyAddNewCourse(){
    Course &new_course = arrCourse[total_course++];
    
    string _No;
    string _ID, _CourseName, _Room, _LUsername, _LName, _LDegree, _Class;
    bool _LGender, _status; // 1 is active, 0 is inactive
    string _startDate, _endDate;
    string _sHour, _sMin, _eHour, _eMin;
    string _DoW;

    cin.ignore();
    cout << "No: ";
    getline(cin, _No,'\n');
    new_course.setNo(_No);
    cout << "ID:";
    getline(cin, _ID,'\n');
    new_course.setID(_ID);
    cout << "Course name: ";
    getline(cin, _CourseName,'\n');
    new_course.setCourseName(_CourseName);
    cout << "Class name: ";
    getline(cin, _Class,'\n');
    new_course.setClass(_Class);
    cout << "Lecturer Username:";
    getline(cin, _LUsername,'\n');
    new_course.setLUsername(_LUsername);
    cout << "Lecturer Name :";
    getline(cin, _LName,'\n');
    new_course.setLDegree(_LName);
    cout << "Lecturer Degree's: ";
    getline(cin, _LDegree,'\n');
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
}

//16
void Semester::editAnExistingCourse(){
    int choose;
    string _courseID, all;
    cout << "Course's ID: ";
    cin >> _courseID;
    if(isCourseActive(_courseID) == false){
        cout << "This course does not exist! \n";
        return;
    }
    for (int i = 0; i < total_course; ++i){
        if(arrCourse[i].getID() == _courseID){
            do{
                cout << "0. Exit \n"
                     << "1. Change course's name \n"
                     << "2. Change course's room \n"
                     << "3. Change course's day of week \n"
                     << "4. Change course's start date \n"
                     << "5. Change course's end date \n"
                     << "6. Time study \n"
                     << "Which do you want to perform? \n";
                cin >> choose;
                switch (choose) {
                    case 1:
                        cout << "New name: " ;
                        cin.ignore();
                        getline(cin, all, '\n');
                        arrCourse[i].setCourseName(all);
                        break;
                    case 2:
                        cout << "Room: " ;
                        cin.ignore();
                        getline(cin, all, '\n');
                        arrCourse[i].setRoom(all);
                        break;
                    case 3:
                        cout << "DoW: ";
                        cin.ignore();
                        getline(cin, all, '\n');
                        arrCourse[i].setDoW(all);
                        break;
                    case 4:
                        cout << "Start date: ";
                        cin.ignore();
                        getline(cin, all, '\n');
                        arrCourse[i].setStartDate(all);
                        break;
                    case 5:
                        cout << "End date: ";
                        cin.ignore();
                        getline(cin, all, '\n');
                        arrCourse[i].setEndDate(all);
                        break;
                    case 6:
                        cout << "Start hour: ";
                        cin.ignore();
                        getline(cin, all, '\n');
                        arrCourse[i].setsHour(all);
                        cout << "Start min: ";
                        cin.ignore();
                        getline(cin, all, '\n');
                        arrCourse[i].setsMin(all);
                        cout << "End hour: ";
                        cin.ignore();
                        getline(cin, all, '\n');
                        arrCourse[i].seteHour(all);
                        cout << "End minute: ";
                        cin.ignore();
                        getline(cin, all, '\n');
                        arrCourse[i].seteMin(all);
                        break;
                    default:
                        break;
                }
            }while(choose);
            break;
        }
    }
}

//17
void Semester::removeACourse(){
    string _courseID;
    cout << "Remove course: ";
    cin >> _courseID;
    for (int i = 0; i < total_course; ++i){
        if (arrCourse[i].getID() == _courseID){
            arrCourse[i].setStatus(0);
            break;
        }
    }
}

//18
void Semester::removeAStudentFromACourse(){
    string _courseID;
    string _studentID;
    string _className;
    cout << "Student ID: " ;
    cin >> _studentID;
    if(isStudentActive(_studentID) == false){
        cout << "This student is not exist! \n" ;
        return;
    }
    cout << "Course ID: ";
    cin >> _courseID;
    if(isCourseActive(_courseID) == false){
        cout << "This course is not exist! \n" ;
        return;
    }
    cout << "Class Name: ";
    cin >> _className;
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
void Semester::addStudentToCourse(){
    string _studentID, _courseID, class_name;
    cout << "Student ID: ";
    cin >> _studentID;
    if(isStudentActive(_studentID) == false){
        cout << "This student does not exist! \n" ;
        return;
    }
    cout << "Course ID: " ;
    cin >> _courseID;
    if(isCourseActive(_courseID) == false){
        cout << "This course does not exist! \n" ;
        return;
    }
    cout << "Class name: " ;
    cin >> class_name;
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

    string skipfirstline, _user, _pass, _name, _gen, _degree, line;
    bool _gender;

    if (fin.is_open())
    {
        getline(fin, skipfirstline, '\n');

        while (getline(fin, line))
        {
            stringstream ss(line);
            getline(ss, _user, ',');
            getline(ss, _pass, ',');
            getline(ss, _name, ',');
            getline(ss, _degree, ',');
            getline(ss, _gen, 'e');
            if (_gen == "Mal") _gender = true;
            else _gender = false;

            // Lecturer &A = arrLecturer[total_lecturer++]; cai nay de neu bi loi ko load tu csv dc
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

void Semester::loadStaffsFromCSV(ifstream& fin)
{
    string link;
    cout << "Please input the link to Staffs.csv: ";
    getline(cin, link);
    
    fin.open(link + "Staffs.csv"); // khai quat

    string skip, _user, _pass, _name, _gen, line;
    bool gender;

    if (fin.is_open())
    {
        getline(fin, skip, '\n');
        
        while (getline(fin, line))
        {
            stringstream ss(line);
            getline(ss, _user, ',');
            getline(ss, _pass, ',');
            getline(ss, _name, ',');
            getline(ss, _gen, ',');
            if (_gen == "Male") gender = true;
            else gender = false;

            Staff a;
            a.setName(_name);
            a.setUser(_user);
            a.setPass(_pass);
            a.setGender(gender);

            arrStaff[total_staff] = a;
            ++total_staff;
        }
        fin.close();
    }
    else cout << "Cannot open file Staffs.csv";
}


// 6
void Semester::loadSingleClassFromCSV(ifstream& fin)
{
    string link; // co the co hoac khong
    string name;

    cout << "Please input class's name: ";
    cin.ignore();
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
        string skip, id, no, fullname, gen, doB, line;
        bool gender;

        getline(fin, skip, '\n');
        
        while (getline(fin, line))
        {
            stringstream ss(line);
            getline(ss, no, ',');
            getline(ss, id, ',');
            getline(ss, fullname, ',');
            getline(ss, gen, ',');
            getline(ss, doB, ',');

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
    else
        cout << "Can not open file!" << endl;
    ++total_class;
}

//20
void Semester::viewListOfCourses()
{
    for (int i = 0; i < total_course; i++)
    {
        if (arrCourse[i].getStatus() == true)
        {
            cout << i + 1 << " : " << arrCourse[i].getID() << " - " << arrCourse[i].getCourseName() << endl;
        }
    }
}
//21
void Semester::viewListStudentOfCourse()
{
    string _courseID;
    cout << "View Course: " ;
    cin >> _courseID;
    if(isCourseActive(_courseID) == false){
        cout << "This course does not exist! \n" ;
        return;
    }
    Student a;
    cout << "List of student in course " << _courseID << " : \n";
    for (int i = 0; i < total_course; i++)
    {
        if (arrCourse[i].getID() == _courseID)
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

void Semester::viewListLecturer(){
    for (int i = 0; i < total_lecturer; ++i)
        cout << arrLecturer[i].getName() << endl;
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

Course Semester::getCourse(string _courseID){
    Course a;
    for (int i = 0; i < total_course; ++i){
        if (arrCourse[i].getID() == _courseID){
            a = arrCourse[i];
            return a;
        }
    }
    return a;
}

Class Semester::getClass(string _ClassName){
    Class a;
    for (int i = 0; i < total_class; ++i){
        if (arrClass[i].getClassName() == _ClassName){
            a = arrClass[i];
            return a;
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
        string line, no, id, c_name, _class, l_user, l_name, l_degree, l_gen, sday, eday, doW, shour, ehour, smin, emin, room;
        bool gender;
        
        while (getline(fin, line))
        {
            stringstream ss(line);
            getline(ss, no, ',');
            getline(ss, id, ',');
            getline(ss, c_name, ',');
            getline(ss, _class, ',');
            getline(ss, l_user, ',');
            getline(ss, l_name, ',');
            getline(ss, l_degree, ',');
            getline(ss, l_gen, ',');
            if (l_gen == "Male") gender = true;
            else gender = false; 
            getline(ss, sday, ',');
            getline(ss, eday, ',');
            getline(ss, doW, ',');
            getline(ss, shour, ',');
            getline(ss, smin, ',');
            getline(ss, ehour, ',');
            getline(ss, emin, ',');
            getline(ss, room, ',');

            Course a;
            a.setID(id);
            a.setCourseName(c_name);
            a.setClass(_class);
            a.setLUsername(l_user);
            a.setLName(l_name);
            a.setLGender(gender);
            a.setLDegree(l_degree);
            a.setRoom(room);
            a.setTime(sday, eday, shour, smin, ehour, emin, doW);
            a.setStatus(true);
            a.setTotalStudent(0);

            arrCourse[total_course++] = a;
            addCourseToClass(id, _class);
        }
        fin.close();
    }
    else
        cout << "Cannot open file!" << endl;
}

void Semester::loadStudentsToTxt(ofstream& fout)
{
    fout.open("Students.txt"); // khai quat
    if (fout.is_open())
    {
        for (int i = 0; i < total_class; ++i)
        {
            for (int j = 0; j < arrClass[i].totalStudent; ++j)
            {
                fout << arrClass[i].student[j].getID() << ',';
                fout << arrClass[i].student[j].getFullName() << ',';
                fout << arrClass[i].getClassName() << ',';
                if (arrClass[i].student[j].getGender() == true) fout << "Male" << ',';
                else fout << "Female" << ',';
                fout << arrClass[i].student[j].getDoB() << ',';
                fout << arrClass[i].student[j].getUsername() << ',';
                fout << arrClass[i].student[j].getPass() << ',';
                if (arrClass[i].student[j].getStatus() == true) fout << "1" << ',';
                else fout << "0" << ',';
                fout << arrClass[i].student[j].numberofCourse << ',';
                for (int z = 0; z < arrClass[i].student[j].numberofCourse - 1; ++z)
                {
                    fout << arrClass[i].student[j].s_ListCourse[z] << ',';
                }
                if(arrClass[i].student[j].numberofCourse >= 1)
                    fout << arrClass[i].student[j].s_ListCourse[arrClass[i].student[j].numberofCourse - 1];
                fout << endl;
            }
        }
        fout.close();
    }
    else cout << "Cannot open file output!";
}

void Semester::loadStudentsFromTxt(ifstream& fin)
{
    fin.open("Students.txt");
    if (fin.is_open())
    {
        string line, id, name, _class, gen, dob, user, pass, stat, num, course;
        bool status, gender;
        int numofCourses;
        
        while (getline(fin, line))
        {
            stringstream ss(line);
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, _class, ',');
            getline(ss, gen, ',');
            if (gen == "Male") gender = true;
            else gender = false;
            getline(ss, dob, ',');
            getline(ss, user, ',');
            getline(ss, pass, ',');
            getline(ss, stat, ',');
            if (stat == "1") status = true;
            else status = false;
            getline(ss, num, ',');
            numofCourses = stoi(num);

            Student a;
            a.setID(id);
            a.setFullName(name);
            a.setGender(gender);
            a.setDoB(dob);
            a.setUsername(user);
            a.setPass(pass);
            a.setStatus(status);
            a.setNumberofCourse(numofCourses);

            for (int i = 0; i < a.getNumberofCourse() - 1; ++i)
            {
                getline(ss, course, ',');
                a.s_ListCourse[i] = course;
            }
            if(a.getNumberofCourse() >= 1){
                getline(ss, course, ',');
                a.s_ListCourse[a.getNumberofCourse() - 1] = course;
            }
            int exist = 0;
            for (int i = 0; i < total_class; ++i)
            {
                if (arrClass[i].getClassName() == _class)
                {
                    arrClass[i].addStudent(a);
                    exist = 1;
                }
            }
        
            if (exist == 0)
            {
                arrClass[total_class].setClassName(_class);
                arrClass[total_class].addStudent(a);
                ++total_class;
            }
        }
        fin.close(); 
    }
    else
        cout << "Cannot open file! \n";
}

void Semester::loadLecturersToTxt(ofstream& fout)
{
    fout.open("Lecturers.txt");
    if (fout.is_open())
    {
        fout << total_lecturer << '\n';
        for (int i = 0; i < total_lecturer; ++i)
        {
            fout << arrLecturer[i].getName() << ',';
            fout << arrLecturer[i].getUserName() << ',';
            fout << arrLecturer[i].getPassword() << ',';
            fout << arrLecturer[i].getDegree() << ',';
            if (arrLecturer[i].getGender() == true) fout << "Male" << ',';
            else fout << "Female" << ',';
            fout << arrLecturer[i].L_totalCourse << ',';
            for (int j = 0; j < arrLecturer[i].L_totalCourse - 1; ++j)
            {
                fout << arrLecturer[i].L_ListCourse[j] << ',';
            }
            fout << arrLecturer[i].L_ListCourse[arrLecturer[i].L_totalCourse - 1] << '\n';
        }
        fout.close();
    }
    else cout << "Cannot open file output! ";
}

void Semester::loadLecturersFromTxt(ifstream& fin)
{
    fin.open("Lecturers.txt");
    if (fin.is_open())
    {
        int total;
        fin >> total;
        total_lecturer = total;
        fin.ignore();
        
        string line, user, pass, name, degree, gen, course, num;
        int numofCourse, count = 0;
        bool gender;
        
        while (getline(fin, line))
        {
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, user, ',');
            getline(ss, pass, ',');
            getline(ss, degree, ',');
            getline(ss, gen, ',');
            if (gen == "Male") gender = true;
            else gender = false;
            getline(ss, num, ',');
            numofCourse = stoi(num);

            Lecturer a;
            a.setName(name);
            a.setUserName(user);
            a.setPassword(pass);
            a.setDegree(degree);
            a.setGender(gender);
            a.L_totalCourse = numofCourse;

            for (int i = 0; i < a.L_totalCourse; ++i)
            {
                getline(ss, course, ',');
                a.L_ListCourse[i] = course; // co the bug o day
            }

            arrLecturer[count] = a;
            ++count;
        }
        fin.close();
    }
    else cout << "Cannot open file input! ";    
}

// file course chung (bao gom thong tin + total_course)
void Semester::loadAllCoursesToTxt(ofstream& fout)
{
    fout.open("Courses.txt");
    if (fout.is_open())
    {
        fout << total_course << '\n';

        for (int i = 0; i < total_course; ++i)
        {
            fout << arrCourse[i].getID() << ',';
            fout << arrCourse[i].getCourseName() << ',';
            fout << arrCourse[i].getClass() << ',';
            fout << arrCourse[i].getRoom() << ',';
            fout << arrCourse[i].getLName() << ',';
            fout << arrCourse[i].getUsername() << ',';
            fout << arrCourse[i].getLDegree() << ',';
            if (arrCourse[i].getLGender() == true) fout << "Male" << ',';
            else fout << "Female" << ',';
            if (arrCourse[i].getStatus() == true) fout << '1' << ',';
            else fout << '0' << ',';
            fout << arrCourse[i].getStartDate() << ',';
            fout << arrCourse[i].getEndDate() << ',';
            fout << arrCourse[i].getsHour() << ',';
            fout << arrCourse[i].getsMin() << ',';
            fout << arrCourse[i].geteHour() << ',';
            fout << arrCourse[i].geteMin() << ',';
            fout << arrCourse[i].getDoW() << '\n';
        }
        fout.close();
    }
    else cout << "Cannot open file output! ";
}

void Semester::loadAllCoursesFromTxt(ifstream& fin)
{
    fin.open("Courses.txt");
    if (fin.is_open())
    {
        string line, id, name, room, _class, luser, lname, ldegree, gen, stat, sday, eday, shour, smin, ehour, emin, doW;
        bool gender, status;
        int total;

        fin >> total;
        total_course = total;
        fin.ignore();
        for (int i = 0; i < total_course; ++i) // co 2 cach input: while (getline) / for ...
        {
            getline(fin, line);
            stringstream ss(line);
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, _class, ',');
            getline(ss, room, ',');
            getline(ss, lname, ',');
            getline(ss, luser, ',');
            getline(ss, ldegree, ',');
            getline(ss, gen, ',');
            getline(ss, stat, ',');
            getline(ss, sday, ',');
            getline(ss, eday, ',');
            getline(ss, shour, ',');
            getline(ss, smin, ',');
            getline(ss, ehour, ',');
            getline(ss, emin, ',');
            getline(ss, doW, ',');
            if (gen == "Male") gender = true;
            else gender = false;
            if (stat == "1") status = true;
            else status = false;

            arrCourse[i].setID(id);
            arrCourse[i].setCourseName(name);
            arrCourse[i].setClass(_class);
            arrCourse[i].setRoom(room);
            arrCourse[i].setLName(lname);
            arrCourse[i].setLUsername(luser);
            arrCourse[i].setLDegree(ldegree);
            arrCourse[i].setLGender(gender);
            arrCourse[i].setStatus(status);
            arrCourse[i].setStartDate(sday);
            arrCourse[i].setEndDate(eday);
            arrCourse[i].setsHour(shour);
            arrCourse[i].setsMin(smin);
            arrCourse[i].seteHour(ehour);
            arrCourse[i].seteMin(emin);
            arrCourse[i].setDoW(doW);
        }
        fin.close();
    }
    else cout << "Cannot open file input! ";
}

void Semester::loadEachCourseToTxt(ofstream& fout)
{
    for (int i = 0; i < total_course; ++i)
    {
        string _coursename, _class;
        _coursename = arrCourse[i].getCourseName();
        _class = arrCourse[i].getClass();

        fout.open(_coursename + "-" + _class + ".txt");
        if (fout.is_open())
        {
            fout << arrCourse[i].c_totalStudent << '\n';
            for (int j = 0; j < arrCourse[i].c_totalStudent; ++j)
            {
                fout << arrCourse[i].c_ListStudent[j] << '\n';
            }
            fout.close();
        }
        else cout << "Cannot open file output! ";
    }
}

// cai nay dung sau khi da loadAllCoursesFromTxt
void Semester::loadEachCourseFromTxt(ifstream& fin)
{
    for (int i = 0; i < total_course; ++i)
    {
        int total;
        fin.open(arrCourse[i].getCourseName() + "-" + arrCourse[i].getClass() + ".txt");
        if (fin.is_open())
        {
            fin >> total;
            arrCourse[i].c_totalStudent = total;
            fin.ignore();
            for (int j = 0; j < arrCourse[i].c_totalStudent; ++j)
            {
                getline(fin, arrCourse[i].c_ListStudent[j], '\n');
            }
            fin.close();
        }
        else cout << "Cannot open file input! ";
    }
}

void Semester::StaffMenu(){
    int choose = 0;
    do{
        cout << "\nStaff Menu: \n"
             << "0. Exit \n"
             << "1. Class \n"
             << "2. Course \n"
             << "3. Scoreboard \n"
             << "4. Attendence list \n\n";
        cout << "Please choose an option: ";
        cin >> choose;
        switch (choose) {
            case 1:
                ClassOption();
                break;
            case 2:
                CourseOption();
                break;
            case 3:
                ScoreboardOption();
                break;
            case 4:
                AttendenceListOption();
                break;
            default:
                break;
        }
    }while(choose);
}

void Semester::ClassOption(){
    int choose;
    ifstream fin;
    do{
        cout << "\nCLASS: \n"
             << "0. Exit \n"
             << "1. Import students of a class. \n"
             << "2. Manually add a new student to a class. \n"
             << "3. Edit an existing student. \n"
             << "4. Remove a student. \n"
             << "5. Change student from class A to class B. \n"
             << "6. View list of classes. \n"
             << "7. View list of student in class. \n\n";
        cout << "Choose an option: ";
        cin >> choose ;
        switch (choose) {
            case 1:
                loadSingleClassFromCSV(fin);
                break;
            case 2:
                ManuallyaddStudentToClass();
                break;
            case 3:
                editAnExistingStudent();
                break;
            case 4:
                RemoveAStudent();
                break;
            case 5:
                changeClass();
                break;
            case 6:
                viewListOfClasses();
                break;
            case 7:
                viewListOfStudent();
                break;
                
            default:
                break;
        }
    }while(choose);
    
}

void Semester::CourseOption(){
    int choose;
    ifstream fin;
        do{
        cout << "\nCOURSE: \n"
             << "0. Exit \n"
             << "1. Import courses from a csv file \n"
             << "2. Manually add a new course \n"
             << "3. Edit an existing course \n"
             << "4. Remove a course \n"
             << "5. Remove a specific student from a course \n"
             << "6. Add a specific student to a course \n"
             << "7. View list of course in current semester \n"
             << "8. View students of a course \n"
             << "9. View list of lecturer \n"
             << "10. \n\n" ;
        cout << "Choose an option: ";
        cin >> choose;
        switch (choose) {
            case 1:
                loadCoursesFromCSV(fin);
                break;
            case 2:
                ManuallyAddNewCourse();
                break;
            case 3:
                editAnExistingCourse();
                break;
            case 4:
                removeACourse();
                break;
            case 5:
                removeAStudentFromACourse();
                break;
            case 6:
                addStudentToCourse();
                break;
            case 7:
                viewListOfCourses();
                break;
            case 8:
                viewListStudentOfCourse();
                break;
            case 9:
                viewListLecturer();
                break;
            case 10:
                break;
            default:
                break;
        }
    }while(choose);
}

void Semester::ScoreboardOption(){
    
}
void Semester::AttendenceListOption(){
    
}

void Semester::StudentMenu(string _username){
    int choose;
    string _ID = _username;
    do{
        cout << "\nStudent Menu: \n"
            << "0. Exit \n"
            << "1. Check in \n"
            << "2. View check in result \n"
            << "3. View schedules \n"
            << "4. View score of a course \n\n";
        cout << "Choose an option: ";
        cin >> choose;
        switch (choose) {
            case 1:
                //CheckIn(string _ID);
                break;
            case 2:
                //viewCheckInResult(string _ID);
                break;
            case 3:
                //viewSchedule(string _ID);
                break;
            case 4:
                //viewScore(string _ID);
                break;
            default:
                break;
        }
    }while(choose);
}

void Semester::LecturerMenu(){
    int choose;
    do{
        cout << "\nLecturer Menu: \n"
            << "0. Exit \n"
            << "1. View list of courses in the current semester \n"
            << "2. View list of students of a course \n"
            << "3. View attendance list of a course \n"
            << "4. Edit an attendance \n"
            << "5. Import scoreboard of a course (midterm, final, lab, bonus) from a csv file \n"
            << "6. Edit grade of a student \n"
            << "7. View a scoreboard \n";
        cout << "Choose an option: ";
        cin >> choose;
        switch (choose) {
            case 1:
                //viewCoursesofLecturer();
                break;
            case 2:
                //viewListStudentOfCourse();
                break;
            case 3:
                //viewAttendanceList();
                break;
            case 4:
                //editAnAttendance();
                break;
            case 5:
                //
                break;
            case 6:
                //editGradeOfAStudent();
                break;
            case 7:
                //viewAScoreBoard();
                break;
            default:
                break;
        }
    }while(choose);
}

void Semester::Login(){
    string _username, _password;
    cout << "\nUsername: " ;
    getline(cin, _username, '\n');
    cout << "Password: " ;
    getline(cin, _password, '\n');
    if(isStudent(_username, _password) == true){
        StudentMenu(_username);
        return ;
    }
    if(isLecturer(_username, _password) == true){
        LecturerMenu();
        return ;
    }
    if(isStaff(_username, _password) == true){
        StaffMenu();
        return ;
    }
    cout << "Wrong username or password, please try again! \n";
    Login();
}

bool Semester::isStudent(string _username, string _password){
    for (int i = 0; i < total_class; ++i){
        for (int j = 0; j < arrClass[i].totalStudent; ++j){
            if(arrClass[i].student[j].getUsername() == _username){
                if(arrClass[i].student[j].getPass() == _password)
                    return true;
                return false;
            }
        }
    }
    return false;
}
     
bool Semester::isLecturer(string _username, string _password){
    for (int i = 0; i < total_lecturer; ++i){
        if(arrLecturer[i].getUserName() == _username){
            if(arrLecturer[i].getPassword() == _password)
                return true;
            return false;
        }
    }
    return false;
}
            
bool Semester::isStaff(string _username, string _password){
    for (int i = 0; i < total_staff; ++i){
        if (arrStaff[i].getUser() == _username){
            if(arrStaff[i].getPass() == _password)
                return true;
            return false;
        }
    }
    return false;
}

void Semester::loadStaffsToTxt(ofstream& fout)
{
    fout.open("Staffs.txt");
    if (fout.is_open())
    {
        fout << total_staff << '\n';

        for (int i = 0; i < total_staff; ++i)
        {
            fout << arrStaff[i].getName() << ',';
            fout << arrStaff[i].getUser() << ',';
            fout << arrStaff[i].getPass() << ',';
            fout << arrStaff[i].getGender() << '\n';
        }
        fout.close();
    }
    else cout << "Cannot open file staff.txt";
}

void Semester::loadStaffsFromTxt(ifstream& fin)
{
    fin.open("Staffs.txt");
    if (fin.is_open())
    {
        fin >> total_staff;
        fin.ignore();
        string line, user, name, pass, gen;
        bool gender;
        for (int i = 0; i < total_staff; ++i)
        {
            getline(fin, line);
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, user, ',');
            getline(ss, pass, ',');
            getline(ss, gen, ',');

            if (gen == "Male") gender = true;
            else gender = false;

            arrStaff[i].setName(name);
            arrStaff[i].setUser(user);
            arrStaff[i].setPass(pass);
            arrStaff[i].setGender(gender);
        }
        fin.close();
    }
    else cout << "Cannot open file input! ";
}
