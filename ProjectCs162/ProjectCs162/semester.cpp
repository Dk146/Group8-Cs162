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

    int exist;
    string skipfirstline, line;
    string _No, _ID, _gen;
    string _fullname, _class, _doB;
    bool _gender;

    fin.open(link + "Students.csv"); // cai nay sua tuy theo hoan canh, t de dang khai quat cho de hieu

    if (fin.is_open())
    {
        getline(fin, skipfirstline);

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

            exist = 0;
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
    else cout << "Cannot open file input!";
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
	if (isStudentActive(_studentID) == false)
		cout << "Remove successful \n";
	else
		cout << "Removed unsuccessful! \n";
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
        if (k==1)
            break;
    }
    
    arrClass[x].totalStudent -= 1;
    while (y < arrClass[x].totalStudent)
    {
        arrClass[x].student[y] = arrClass[x].student[y+1];
        ++y;
    }
	if (getClassOfStudent(_ID) == _newclass)
		cout << "Change successful \n";
	else
		cout << "Change unsuccessful \n";
}

//11
void Semester::viewListOfClasses()
{
    int choose;
    do{
		system("cls");
        cout << "\nList of classes: " << endl;
        cout << "0. Exit" << endl;
        for (int i = 0; i < total_class; i++)
        {
            cout << i+1 << ": " << arrClass[i].getClassName() << endl;
        }
        cout << "\nChoose a class to view students: ";
        cin >> choose;
        if(choose)
            viewListOfStudent(choose - 1);
		system("pause");
    }while(choose);
}

//12
void Semester::viewListOfStudent(int _pos)
{
	for (int i = 0; i < arrClass[_pos].totalStudent; i++) {
		if (arrClass[_pos].student[i].getStatus() == true)
			cout << "Student " << i + 1 << " : " << arrClass[_pos].student[i].getID() << " - " << arrClass[_pos].student[i].getFullName() << endl;
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

	addCourseToClass(new_course.getID(), new_course.getClass());

}

//16
void Semester::editAnExistingCourse(){
    int choose;
    string _courseID, _classCourse, all;
    cout << "Course ID: ";
    cin >> _courseID;
	cout << "Class of Course: ";
    if(isCourseActive(_courseID, _classCourse) == false){
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
	string _classCourse;
    cout << "Remove course: ";
    cin >> _courseID;
	cout << "Of Class: ";
	cin >> _classCourse;
    for (int i = 0; i < total_course; ++i){
        if (arrCourse[i].getID() == _courseID && arrCourse[i].getClass() == _classCourse){
            arrCourse[i].setStatus(0);
            break;
        }
    }
}

//18
void Semester::removeAStudentFromACourse(){
    string _courseID;
    string _studentID;
    string _classCourse;
    cout << "Student ID: " ;
    cin >> _studentID;
	string _classStudent = getClassOfStudent(_studentID);
    if(isStudentActive(_studentID) == false){
        cout << "This student is not exist! \n" ;
        return;
    }
    cout << "Course ID: ";
    cin >> _courseID;
    cout << "Class's Course: ";
    cin >> _classCourse;
	if (isCourseActive(_courseID, _classCourse) == false) {
		cout << "This course is not exist! \n";
		return;
	}
    int pos_c = 0;
    int pos_s = 0;
    int k = 0;
    for (int i = 0; i < total_class; ++i){
        if (arrClass[i].getClassName() == _classStudent){
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
        if (arrCourse[i].getID() == _courseID && arrCourse[i].getClass() == _classCourse){
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
    string _studentID, _courseID, class_name, _classCourse;
    cout << "Student ID: ";
    cin >> _studentID;
	class_name = getClassOfStudent(_studentID);
    if(isStudentActive(_studentID) == false){
        cout << "This student does not exist! \n" ;
        return;
    }
    cout << "Course ID: " ;
    cin >> _courseID;
	cout << "Of Class: ";
	cin >> _classCourse;
	if (isCourseActive(_courseID, _classCourse) == false) {
		cout << "This course does not exist! \n";
		return;
	}
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
        if(arrCourse[i].getID() == _courseID && arrCourse[i].getClass() == _classCourse){
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
            getline(ss, _gen, '\n');
            if (_gen == "Male") _gender = true;
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
	int _pos;
	do {
		system("cls");
		cout << "List of Course: \n\n";
		cout << "0 : Exit \n";
		for (int i = 0; i < total_course; i++)
		{
			if (arrCourse[i].getStatus() == true)
			{
				cout << i + 1 << " : " << arrCourse[i].getID() << " - " << arrCourse[i].getCourseName() << " - " << arrCourse[i].getClass() << endl;
			}
			else
				cout << i + 1 << " : " << "This course has been removed \n";
		}
		cout << "Choose a course to view students: ";
		cin >> _pos;
		if(_pos)
			viewListStudentOfCourse(_pos-1);
		system("pause");
	} while (_pos);

}
//21
void Semester::viewListStudentOfCourse(int _pos)
{
	Student a;
	cout << "List of student in course " << arrCourse[_pos].getID() << " - " << arrCourse[_pos].getClass() << " : \n";
		for (int j = 0; j < arrCourse[_pos].getTotalStudent(); j++)
        {
	        a = getStudent(arrCourse[_pos].c_ListStudent[j]);
            if (a.getStatus() == true)
				cout << j+1 << ": " << a.getFullName() << " - " << a.getID() << endl;
            else
                cout << j+1 << ": " << endl;
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
bool Semester::isCourseActive(string _courseID, string _classCourse) {
    for (int i = 0; i < total_course; ++i) {
        if (arrCourse[i].getID() == _courseID && arrCourse[i].getClass() == _classCourse) {
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
    cout << "Please input the link to Courses.csv: ";
	cin.ignore();
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

            arrCourse[total_course] = a;
            ++total_course;
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
            if (arrLecturer[i].L_totalCourse > 0)
            {
                fout << arrLecturer[i].L_totalCourse << ',';
                for (int j = 0; j < arrLecturer[i].L_totalCourse - 1; ++j)
                {
                    fout << arrLecturer[i].L_ListCourse[j] << ',';
                }
                fout << arrLecturer[i].L_ListCourse[arrLecturer[i].L_totalCourse - 1] << '\n';
            }
			if(arrLecturer[i].L_totalCourse > 0)
				fout << arrLecturer[i].L_ListCourse[arrLecturer[i].L_totalCourse - 1] << '\n';
            else fout << 0 << '\n';
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
            if (arrCourse[i].point == true) fout << "1" << ',';
            else fout << "0" << ',';
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
        string line, id, name, room, _class, luser, lname, ldegree, gen, stat, sday, eday, shour, smin, ehour, emin, doW, point;
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
            getline(ss, point, ',');
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
            if (point == "1") arrCourse[i].point = true;
            else arrCourse[i].point = false;
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
            if (arrCourse[i].point == true)
            {
                for (int j = 0; j < arrCourse[i].c_totalStudent; ++j)
                {
                    fout << arrCourse[i].c_ListStudent[j] << ',' << arrCourse[i].Check[j].score[0] << ',' << arrCourse[i].Check[j].score[1]
                        << ',' << arrCourse[i].Check[j].score[2] << ',' << arrCourse[i].Check[j].score[3] << '\n';
                }
            }
            else
            {
                for (int j = 0; j < arrCourse[i].c_totalStudent; ++j)
                {
                    fout << arrCourse[i].c_ListStudent[j] << '\n';
                }
            }
            fout.close();
        }
        else cout << "Cannot open file output! ";
    }
}

// cai nay dung sau khi da loadAllCoursesFromTxt
void Semester::loadEachCourseFromTxt(ifstream& fin)
{
    string line, mid, final, bonus, total;
    for (int i = 0; i < total_course; ++i)
    {
        fin.open(arrCourse[i].getCourseName() + "-" + arrCourse[i].getClass() + ".txt");
        if (fin.is_open())
        {
            fin >> arrCourse[i].c_totalStudent;
            fin.ignore();
            if (arrCourse[i].point == true)
            {
                for (int j = 0; j < arrCourse[i].c_totalStudent; ++j)
                {
                    getline(fin, line);
                    stringstream ss(line);
                    getline(ss, arrCourse[i].c_ListStudent[j], ',');
                    getline(ss, arrCourse[i].Check[j].score[0], ',');
                    getline(ss, arrCourse[i].Check[j].score[1], ',');
                    getline(ss, arrCourse[i].Check[j].score[2], ',');
                    getline(ss, arrCourse[i].Check[j].score[3], '\n');
                }
            }
            else
            {
                for (int j = 0; j < arrCourse[i].c_totalStudent; ++j)
                {
                    getline(fin, arrCourse[i].c_ListStudent[j], '\n');
                }
            }
            fin.close();
        }
        else cout << "Cannot open file input! ";
    }
}

void Semester::StaffMenu(string _username){
    string _ID = _username;
    int choose = 0;
    do{
		system("cls");
        cout << "\nStaff Menu: \n"
             << "0. Exit \n"
             << "1. Class \n"
             << "2. Course \n"
             << "3. Scoreboard \n"
            << "4. Attendence list \n\n";
        cout << "Please choose an option: ";
        cin >> choose;
        switch (choose) {
			system("cls");
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
		system("cls");
        cout << "\nCLASS: \n"
             << "0. Exit \n"
             << "1. Import students of a class. \n"
             << "2. Manually add a new student to a class. \n"
             << "3. Edit an existing student. \n"
             << "4. Remove a student. \n"
             << "5. Change student from class A to class B. \n"
             << "6. View list of classes. \n\n";
        cout << "Choose an option: ";
        cin >> choose ;
        switch (choose) {
			system("cls");
            case 1:
                loadSingleClassFromCSV(fin);
				system("pause");
                break;
            case 2:
                ManuallyaddStudentToClass();
				system("pause");
                break;
            case 3:
                editAnExistingStudent();
				system("pause");
                break;
            case 4:
                RemoveAStudent();
				system("pause");
                break;
            case 5:
                changeClass();
				system("pause");
                break;
            case 6:
                viewListOfClasses();
                break;
            default:
                break;
        }
    }while (choose);
}

void Semester::CourseOption(){
    int choose;
    ifstream fin;
        do{
		system("cls");
        cout << "\nCOURSE: \n"
             << "0. Exit \n"
             << "1. Import courses from a csv file \n"
             << "2. Manually add a new course \n"
             << "3. Edit an existing course \n"
             << "4. Remove a course \n"
             << "5. Remove a specific student from a course \n"
             << "6. Add a specific student to a course \n"
             << "7. View list of course in current semester \n"
             << "8. View list of lecturer \n"
             << "9. \n\n" ;
        cout << "Choose an option: ";
        cin >> choose;
        switch (choose) {
			system("cls");
            case 1:
                loadCoursesFromCSV(fin);
				//system("pause");
                break;
            case 2:
                ManuallyAddNewCourse();
				system("pause");
				break;
            case 3:
                editAnExistingCourse();
				system("pause");
				break;
            case 4:
                removeACourse();
				system("pause");
				break;
            case 5:
                removeAStudentFromACourse();
				system("pause");
				break;
            case 6:
                addStudentToCourse();
				system("pause");
				break;
            case 7:
                viewListOfCourses();
				break;
            case 8:
                viewListLecturer();
				system("pause");
				break;
            case 10:
                break;
            default:
                break;
        }
		}while(choose);
}

void Semester::ScoreboardOption(){
    ifstream fin;
    int choose;
    cout << "\nScore Board: \n"
        << "1. Import a course's scoreboard. \n"
        << "2. Search and view the scoreboard of a course \n"
        << "3. Export a course's scoreboard \n";
    cout << "Choose an option: ";
    cin >> choose;
    switch (choose)
    {
    case 1:
        loadScoreBoard(fin);
		system("pause");
        break;
    case 2:
        viewScoreOfACourse();
		system("pause");
        break;
    case 3: 
        // export
        break;
    }
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
	system("cls");
    string _username, _password;
    cout << "\nUsername: " ;
    getline(cin, _username, '\n');
    cout << "Password: " ;
    getline(cin, _password, '\n');
    if(isStudent(_username, _password) == true){
		cout << "\nLogin successful \n\n";
		system("pause");
        StudentMenu(_username);
        return ;
    }
    if(isLecturer(_username, _password) == true){
		cout << "\nLogin successful \n\n";
		system("pause");
        LecturerOption(_username);
        return ;
    }
    if(isStaff(_username, _password) == true){
		cout << "\nLogin successful \n\n";
		system("pause");
        StaffOption(_username);
        return ;
    }
    cout << "Wrong username or password, please try again! \n";
	system("pause");
    Login();
}

void Semester::StaffOption(string _username){
    string _ID = _username;
    int choose;
    do{
		system("cls");
        cout << "\n1. Show menu \n"
            << "2. View profile info \n"
            << "3. Change password \n"
            << "4. Logout \n\n" ;
        cout << "Choose an option: ";
        cin >> choose;
        switch (choose) {
            case 1:
                StaffMenu(_ID);
                break;
            case 2:
                viewProfileStaff(_ID);
                break;
            case 3:
				system("cls");
                changePassStaff(_ID);
                break;
            default:
                break;
        }
    }while(choose != 4);
}

void Semester::StudentOption(string _username){
    string _ID = _username;
    int choose;
    do{
        cout << "\n1. Show menu \n"
            << "2. View profile info \n"
            << "3. Change password \n"
            << "4. Logout \n\n" ;
        cout << "Choose an option: ";
        cin >> choose;
        switch (choose) {
            case 1:
                StudentMenu(_ID);
                break;
            case 2:
                viewProfileStudent(_ID);
                break;
            case 3:
                changePassStudent(_ID);
                break;
            default:
                break;
        }
    }while(choose != 4);
}

void Semester::LecturerOption(string _username){
    string _ID = _username;
    int choose;
    do{
        cout << "\n1. Show menu \n"
            << "2. View profile info \n"
            << "3. Change password \n"
            << "4. Logout \n\n" ;
        cout << "Choose an option: ";
        cin >> choose;
        switch (choose) {
            case 1:
                LecturerMenu();
                break;
            case 2:
                viewProfileLecturer(_ID);
                break;
            case 3:
                changePassLecturer(_ID);
                break;
            default:
                break;
        }
    }while(choose != 4);
}

void Semester::changePassStaff(string _username){
    string _newPassword, _confirmPass;
    for (int i = 0; i < total_staff; ++i){
        if(arrStaff[i].getUser() == _username){
            do{
                cout << "New Password: ";
                cin.ignore();
                getline(cin, _newPassword, '\n');
                cout << "Confirm Password: ";
                getline(cin, _confirmPass, '\n');
                if (_newPassword != _confirmPass)
                    cout << "Wrong confirm Password. Please try again! \n";
                else
                    arrStaff[i].setPass(_newPassword);
                }while(_newPassword != _confirmPass);
            return;
        }
    }
}

void Semester::changePassStudent(string _username){
    string _newPassword, _confirmPass;
    for (int i = 0; i < total_class; ++i){
        for (int j = 0; j < arrClass[i].totalStudent; ++j){
            if (arrClass[i].student[j].getID() == _username){
                do{
                    cout << "New Password: ";
                    cin.ignore();
                    getline(cin, _newPassword, '\n');
                    cout << "Confirm Password: ";
                    getline(cin, _confirmPass, '\n');
                    if (_newPassword != _confirmPass)
                        cout << "Wrong confirm Password. Please try again! \n";
                    else
                        arrClass[i].student[j].setPass(_newPassword);
                }while(_newPassword != _confirmPass);
                return;
            }
        }
    }
}

void Semester::changePassLecturer(string _username){
    string _newPassword, _confirmPass;
    for (int i = 0; i < total_lecturer; ++i){
        if (arrLecturer[i].getUserName() == _username){
            do{
                cout << "New Password: ";
                cin.ignore();
                getline(cin, _newPassword, '\n');
                cout << "Confirm Password: ";
                getline(cin, _confirmPass, '\n');
                if (_newPassword != _confirmPass)
                    cout << "Wrong confirm Password. Please try again! \n";
                else
                    arrLecturer[i].setPassword(_newPassword);
            }while(_newPassword != _confirmPass);
            return;
        }
    }
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

void Semester::viewProfileStudent(string _studentID){
    string _ID = _studentID;
    Student a = getStudent(_studentID);
    cout << "\nYour profile: \n" ;
    cout << "Name: " << a.getFullName() << endl;
    cout << "ID: " << a.getID() << endl;
    cout << "Class: " << getClassOfStudent(_ID) << endl;
    cout << "Day of birth: " << a.getDoB() << endl;
    cout << "Gender: " << a.getGender() << endl;
}

string Semester::getClassOfStudent(string _studentID){
    for (int i = 0; i < total_class; ++i){
        for (int j = 0; j < arrClass[i].totalStudent; ++j){
            if (arrClass[i].student[j].getID() == _studentID)
                return arrClass[i].getClassName();
        }
    }
    return "None";
}

void Semester::viewProfileLecturer(string _lecturerID){
    string _ID = _lecturerID;
    Lecturer a = getLecturer(_ID);
    cout << "\nName: " << a.getName() << endl;
    cout << "Degree: " << a.getDegree() << endl;
    cout << "Username: " << a.getUserName() << endl;
    cout << "Gender: " << a.getGender() << endl;
}

Lecturer Semester::getLecturer(string _LecturerUser){
    Lecturer a;
    for (int i = 0; i < total_lecturer; ++i){
        if (arrLecturer[i].getUserName() == _LecturerUser){
            a = arrLecturer[i];
            return a;
        }
    }
    return a;
}

void Semester::viewProfileStaff(string _staffUser){
    string _ID = _staffUser;
    Staff a = getStaff(_ID);
    cout << "\nYour profile: \n";
    cout << "Name: " << a.getName() << endl;
    cout << "Username: " << a.getUser() << endl;
    cout << "Gender: " << a.getGender() << endl;
	system("pause");
}

Staff Semester::getStaff(string _StaffUser){
    Staff a;
    for (int i = 0 ; i < total_staff; ++ i){
        if(arrStaff[i].getUser() == _StaffUser){
            a = arrStaff[i];
            return a;
        }
    }
    return a;
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

void Semester::loadScoreBoard(ifstream& fin)
{
    string* ptr;
    ptr = new string[3];
    int index = 0;

    cin.ignore(100, '\n');
    cout << "Input name of the class you want to import scoreboard: ";
    getline(cin, ptr[0]);
    cout << "Input name of the course you want to import scoreboard: ";
    getline(cin, ptr[1]);

    for (int i = 0; i < total_course; ++i)
        if (arrCourse[i].getID() == ptr[1] && arrCourse[i].getClass() == ptr[0]) index = i;

    int ind = 0;

    fin.open(ptr[0] + "-" + ptr[1] + "-" + "Scoreboard.csv");
    if (fin.is_open())
    {
        getline(fin, ptr[2], '\n');

        string line, No, id, name, mid, final, bonus, total;
        while (getline(fin, line))
        {
            stringstream ss(line);
            getline(ss, No, ',');
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, mid, ',');
            getline(ss, final, ',');
            getline(ss, bonus, ',');
            getline(ss, total, '\n');

            arrCourse[index].Check[ind].score[0] = mid;
            arrCourse[index].Check[ind].score[1] = final;
            arrCourse[index].Check[ind].score[2] = bonus;
            arrCourse[index].Check[ind].score[3] = total;

            ++ind;
        }
        fin.close();
    }
    else cout << "Cannot open file input! ";
    
    arrCourse[index].point = true;
    
    delete [] ptr;
}

void Semester::viewScoreOfACourse()
{
    string* ptr;
    ptr = new string[2];
    int index;
    bool exist = false;

    cin.ignore(100, '\n');
    cout << "Which course do you want to view score of? ";
    getline(cin, ptr[0]);
    cout << "Of which class? ";
    getline(cin, ptr[1]);

    for (int i = 0; i < total_course; ++i)
    {
        if (arrCourse[i].getID() == ptr[0] && arrCourse[i].getClass() == ptr[1])
        {
            index = i;
            exist = true;
        }
    }

    if (exist == false)
    {
        cout << "There is no such course! ";
        return;
    }

    if (arrCourse[index].point == false)
    {
        cout << "This course has no scoreboard yet! ";
        return;
    }

    for (int i = 0; i < arrCourse[index].c_totalStudent; ++i)
    {
        cout << arrCourse[index].c_ListStudent[i] << " " << arrCourse[index].Check[i].score[0] << " "
            << arrCourse[index].Check[i].score[1] << " " << arrCourse[index].Check[i].score[2] << " "
            << arrCourse[index].Check[i].score[3] << endl;
    }
}

void Semester::resizeArrClass() {
	max_class += 5;
	Class* new_arrClass = new Class[max_class];
	for (int i = 0; i < total_class; ++i) 
		new_arrClass[i] = arrClass[i];
	delete[] arrClass;
	arrClass = new_arrClass;
}
void Semester::resizeArrCourse() {
	max_course += 5;
	Course* new_arrCourse = new Course[max_course];
	for (int i = 0; i < total_course; ++i)
		new_arrCourse[i] = arrCourse[i];
	delete[] arrCourse;
	arrCourse = new_arrCourse;
}
void Semester::resizeArrStaff() {
	max_staff += 5;
	Staff* new_arrStaff = new Staff[max_staff];
	for (int i = 0; i < total_staff; ++i)
		new_arrStaff[i] = arrStaff[i];
	delete[] arrStaff;
	arrStaff = new_arrStaff;
}
void Semester::resizeArrLecturer() {
	max_lecturer += 5;
	Lecturer* new_arrLecturer = new Lecturer[max_lecturer];
	for (int i = 0; i < total_lecturer; ++i)
		new_arrLecturer[i] = arrLecturer[i];
	delete[] arrLecturer;
	arrLecturer = new_arrLecturer;
}