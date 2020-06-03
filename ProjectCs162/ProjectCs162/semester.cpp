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
                    if (arrClass[i].totalStudent == arrClass[i].max_student) arrClass[i].resizeClass();
                    arrClass[i].addStudent(A);
                    exist = 1;
                }
            }

            if (exist == 0)
            {
                if (total_class == max_class) resizeArrClass();
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
void Semester::addCourseToClass(string _courseID, string _className)
{
    int pos_Course = 0;
    int pos_Class = 0;
    int pos_Lecturer = 0;

    for (int i = 0; i < total_course; ++i){
        if (arrCourse[i].getID() == _courseID && arrCourse[i].getClass() == _className){
            pos_Course = i;
            break;
        }
    }
   
    for (int i = 0; i < total_class; ++i){
        if (arrClass[i].getClassName() == _className ){
            pos_Class = i;
            break;
        }
    }
    
    Course &_course(arrCourse[pos_Course]);
    Class &_class(arrClass[pos_Class]);
    
    for (int i = 0; i < total_lecturer; ++i)
    {
        if (arrLecturer[i].getName() == _course.getLName())
        {
            for (int i = 0; i < total_lecturer; ++i) {
                if (arrLecturer[i].getUserName() == _course.getUsername()) {
                    pos_Lecturer = i;
                    break;
                }
            }
        }
    }

    Lecturer &_lecturer(arrLecturer[pos_Lecturer]);

    if (_lecturer.L_totalCourse == _lecturer.L_maxCourse) _lecturer.resizeLecturer(); 

	if (_lecturer.L_totalCourse == _lecturer.L_maxCourse)
		_lecturer.resizeLecturer();
    _lecturer.L_ListCourse[_lecturer.L_totalCourse].courseID = _courseID;
	_lecturer.L_ListCourse[_lecturer.L_totalCourse++].className = _className;

    for (int i = 0; i < _class.totalStudent; ++i){
        _class.student[i].s_ListCourse[_class.student[i].numberofCourse].ID = _courseID;
		_class.student[i].s_ListCourse[_class.student[i].numberofCourse].className = _className;
		++_class.student[i].numberofCourse;
	}

    for (int i = 0; i < _class.totalStudent; ++i){
        _course.c_ListStudent[i] = _class.student[i].getID();
    }
    _course.c_totalStudent = _class.totalStudent;
}

// 7
void Semester::ManuallyaddStudentToClass()
{
    string _ID, _fullname, _DoB;
    string _userName, _password;
    bool _gender;
    string _className;

    Student a;
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
			if (arrClass[i].totalStudent == arrClass[i].max_student)
				arrClass[i].resizeClass();
            arrClass[i].addStudent(a);
            arrClass[i].student[arrClass[i].totalStudent - 1].numberofCourse = arrClass[i].student[0].numberofCourse;
            for (int j = 0; j < arrClass[i].student[0].numberofCourse; ++j)
            {
                arrClass[i].student[arrClass[i].totalStudent - 1].s_ListCourse[j] = arrClass[i].student[0].s_ListCourse[j]; 
            }
        }
    }

    for (int i = 0; i < total_course; ++i)
    {
        if (arrCourse[i].getClass() == _className)
        {
            if (arrCourse[i].c_totalStudent == arrCourse[i].c_maxStudent) arrCourse[i].resizeCourse();
            arrCourse[i].c_ListStudent[arrCourse[i].getTotalStudent()] = _ID;
            ++arrCourse[i].c_totalStudent;
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
                } while (choose != 3);
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
        if (k == 1)
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

    if (isStudentActive(_ID) == false) {
        cout << "This ID does not exist!" << endl;
        return;
    }

    string _newclass;
    int x = 0, y = 0, newc = 0;
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
						if (arrClass[z].totalStudent == arrClass[z].max_student)
							arrClass[z].resizeClass();
                        arrClass[z].addStudent(arrClass[i].student[j]);
                        k = 1;
                        newc = z;
                        break;
                    }
                }
                break;
            }
        }
        if (k == 1)
            break;
    }

    arrClass[x].totalStudent -= 1;
    while (y < arrClass[x].totalStudent)
    {
        arrClass[x].student[y] = arrClass[x].student[y + 1];
        ++y;
    }

    for (int i = 0; i < total_course; ++i)
    {
        int index;
        if (arrCourse[i].getClass() == arrClass[x].getClassName())
        {
            for (int j = 0; j < arrCourse[i].c_totalStudent; ++j)
				if (arrCourse[i].c_ListStudent[j] == _ID) {
					index = j;
					arrCourse[i].c_totalStudent -= 1;
					while (index < arrCourse[i].c_totalStudent)
					{
						arrCourse[i].c_ListStudent[index] = arrCourse[i].c_ListStudent[index + 1];
						++index;
					}
				}
        }

        if (arrCourse[i].getClass() == arrClass[newc].getClassName())
        {
            arrCourse[i].c_ListStudent[arrCourse[i].c_totalStudent] = _ID;
            ++arrCourse[i].c_totalStudent;
        }
    }

    for (int i = 0; i < total_class; ++i)
    {
        if (arrClass[i].getClassName() == _newclass)
            for (int j = 0; j < arrClass[i].student[arrClass[i].totalStudent - 2].numberofCourse; ++j)
                arrClass[i].student[arrClass[i].totalStudent - 1].s_ListCourse[j] = arrClass[i].student[arrClass[i].totalStudent - 2].s_ListCourse[j];
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
    do {
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
    } while(choose);
}

//12
void Semester::viewListOfStudent(int _pos)
{
	cout << "ID           " <<static_cast<char>(179)<< "Full Name             " << static_cast<char>(179)<< "Gender      " << static_cast<char>(179)<< "Day of birth" << endl;
	for (int i = 0; i < arrClass[_pos].totalStudent; i++) {
		if (arrClass[_pos].student[i].getStatus() == true)
			cout << setw(13) << left << arrClass[_pos].student[i].getID() << static_cast<char>(179) << setw(22) << left << arrClass[_pos].student[i].getFullName() << static_cast<char>(179) << setw(12) << left << arrClass[_pos].student[i].getGender() << static_cast<char>(179) << setw(13) << left << arrClass[_pos].student[i].getDoB() << endl;
	}
}

//15
void Semester::ManuallyAddNewCourse(){

    if (total_course == max_course) resizeArrCourse();
    Course &new_course = arrCourse[total_course++];
    
    string _No;
    string _ID, _CourseName, _Room, _LUsername, _LName, _LDegree, _Class;
    bool _LGender, _status; // 1 is active, 0 is inactive
    string _startDate, _endDate;
    string _sHour, _sMin, _eHour, _eMin;
    string _DoW;

    cin.ignore();
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
    if (isCourseActive(_courseID, _classCourse) == false){
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
            } while(choose);
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
        cout << "This student does not exist! \n" ;
        return;
    }
    cout << "Course ID: ";
    cin >> _courseID;
    cout << "Class's Course: ";
    cin >> _classCourse;
	if (isCourseActive(_courseID, _classCourse) == false) {
		cout << "This course does not exist! \n";
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

    for (int i = 0; i < k; ++i)
    {
        if (arrClass[pos_c].student[pos_s].s_ListCourse[i].ID == _courseID && arrClass[pos_c].student[pos_s].s_ListCourse[i].className == _classCourse){
            for (int j = i; j < k-1; ++j){
                arrClass[pos_c].student[pos_s].s_ListCourse[j].ID = arrClass[pos_c].student[pos_s].s_ListCourse[j+1].ID;
				arrClass[pos_c].student[pos_s].s_ListCourse[j].className = arrClass[pos_c].student[pos_s].s_ListCourse[j + 1].className;
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
        if (arrClass[i].getClassName() == class_name){
            for (int j = 0; j < arrClass[i].totalStudent; ++j){
                if (arrClass[i].student[j].getID() == _studentID){
                    int k = arrClass[i].student[j].numberofCourse;
                    arrClass[i].student[j].s_ListCourse[k].ID = _courseID;
					arrClass[i].student[j].s_ListCourse[k].className = _classCourse;
                    k++;
                    arrClass[i].student[j].numberofCourse = k;
                    break;
                }
            }
            break;
        }
    }
    
    for (int i = 0; i < total_course; ++i){
        if (arrCourse[i].getID() == _courseID && arrCourse[i].getClass() == _classCourse){
			if (arrCourse[i].c_totalStudent == arrCourse[i].c_maxStudent)
				arrCourse[i].resizeCourse();
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
            
            if (total_lecturer == max_lecturer) resizeArrLecturer();
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

            if (total_staff == max_staff) resizeArrStaff();

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

    if (total_class == max_class) resizeArrClass();
    arrClass[total_class].setClassName(name);
    
    fin.open(name + ".csv");
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

            if (arrClass[total_class].totalStudent == arrClass[total_class].max_student) arrClass[total_class].resizeClass();

            arrClass[total_class].addStudent(A);
        }
        fin.close();
    }
    else cout << "Can not open file!" << endl;
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
	cout << "Name                     " << "Gender      " << "Degree      " << "Username" << endl;
	for (int i = 0; i < total_lecturer; ++i)
		cout << setw(25) << left << arrLecturer[i].getName() << setw(12) << left << arrLecturer[i].getGender() << setw(12) << left << arrLecturer[i].getDegree() << setw(16) << left << arrLecturer[i].getUserName() << endl;
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

Course Semester::getCourse(string _courseID, string _className){
    Course a;
    for (int i = 0; i < total_course; ++i){
        if (arrCourse[i].getID() == _courseID && arrCourse[i].getClass() == _className){
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
	fin.ignore();
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
            if (total_course == max_course) resizeArrCourse();

            arrCourse[total_course] = a;
            ++total_course;
            addCourseToClass(id, _class);
        }
        fin.close();
    }
    else
        cout << "Cannot open file!" << endl;
}

void Semester::loadClassesToTxt(ofstream& fout)
{
    fout.open("Classes.txt"); // khai quat
    if (fout.is_open())
    {
        fout << total_class << '\n';
        for (int i = 0; i < total_class; ++i)
        {
            fout << arrClass[i].getClassName() << ',';
            fout << arrClass[i].totalStudent << '\n';
        }
        fout.close();
    }
    else cout << "Cannot open file output!";
}

void Semester::loadEachClassToTxt(ofstream& fout)
{
    for (int i = 0; i < total_class; ++i)
    {
        fout.open(arrClass[i].getClassName() + "-Students.txt");
        if (fout.is_open())
        {
            for (int j = 0; j < arrClass[i].totalStudent; ++j)
            {
                fout << arrClass[i].student[j].getID() << ',';
                fout << arrClass[i].student[j].getFullName() << ',';
                if (arrClass[i].student[j].getGender() == true) fout << "Male" << ',';
                else fout << "Female" << ',';
                fout << arrClass[i].student[j].getDoB() << ',';
                fout << arrClass[i].student[j].getUsername() << ',';
                fout << arrClass[i].student[j].getPass() << ',';
                if (arrClass[i].student[j].getStatus() == true) fout << "1" << ',';
                else fout << "0" << ',';
                if (arrClass[i].student[j].getNumberofCourse() == 0) fout << "0";
                else
                {
                    fout << arrClass[i].student[j].getNumberofCourse() << ',';
                    for (int z = 0; z < arrClass[i].student[j].getNumberofCourse() - 1; ++z)
                    {
                        fout << arrClass[i].student[j].s_ListCourse[z].ID << ',';
                        fout << arrClass[i].student[j].s_ListCourse[z].className << ',';
                    }
                    fout << arrClass[i].student[j].s_ListCourse[arrClass[i].student[j].getNumberofCourse() - 1].ID << ',';
                    fout << arrClass[i].student[j].s_ListCourse[arrClass[i].student[j].getNumberofCourse() - 1].className;
                }
                fout << endl;
            }
            fout.close();
        }
        else cout << "Cannot open file output! ";
    }
	system("pause");
}

void Semester::loadClassesFromTxt(ifstream& fin)
{
    fin.open("Classes.txt");
    int num;
    string _name, _totalstudent, line, n;

    if (fin.is_open())
    {
        getline(fin, n);
        total_class = stoi(n);
		while (total_class > max_class)
			resizeArrClass();
        for (int i = 0; i < total_class; ++i)
        {
            getline(fin, line);
            stringstream ss(line);
            getline(ss, _name, ',');
            getline(ss, _totalstudent, ',');
      
            arrClass[i].setClassName(_name);
            num = stoi(_totalstudent);
            arrClass[i].settotalStudent(num);
        }
        fin.close();
    }
    else cout << "Cannot open file input! ";
}

void Semester::loadEachClassFromTxt(ifstream& fin)
{
    string line, id, name, dob, gen, user, pass, stat, num, course, _class;
    int number;
    bool gender, status;

    for (int i = 0; i < total_class; ++i)
    {
        while (arrClass[i].totalStudent >= arrClass[i].max_student)
            arrClass[i].resizeClass();
        fin.open(arrClass[i].getClassName() + "-Students.txt");
        for (int j = 0; j < arrClass[i].totalStudent; ++j)
        {
            getline(fin, line);
            stringstream ss(line);
            getline(ss, id, ',');
            getline(ss, name, ',');
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
            number = stoi(num);

            Student a;
            a.setID(id);
            a.setFullName(name);
            a.setGender(gender);
            a.setDoB(dob);
            a.setUsername(user);
            a.setPass(pass);
            a.setStatus(status);
            a.setNumberofCourse(number);

            if (a.getNumberofCourse() > 0)
            {
                for (int z = 0; z < a.getNumberofCourse(); ++z)
                {
                    getline(ss, course, ',');
                    a.s_ListCourse[z].ID = course;
                    getline(ss, _class, ',');
                    a.s_ListCourse[z].className = _class;
                }
            }
            arrClass[i].student[j] = a;
        }
        fin.close();
    }
	for (int i = 0; i < total_class; ++i)
	{
		fin.open(arrClass[i].getClassName() + "-Students.txt");
		while (arrClass[i].totalStudent > arrClass[i].max_student)
			arrClass[i].resizeClass();
		for (int j = 0; j < arrClass[i].totalStudent; ++j)
		{
			getline(fin, line);
			stringstream ss(line);
			getline(ss, id, ',');
			getline(ss, name, ',');
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
			number = stoi(num);

			Student a;
			a.setID(id);
			a.setFullName(name);
			a.setGender(gender);
			a.setDoB(dob);
			a.setUsername(user);
			a.setPass(pass);
			a.setStatus(status);
			a.setNumberofCourse(number);

			if (a.getNumberofCourse() > 0)
			{
				for (int z = 0; z < a.getNumberofCourse(); ++z) {
					getline(ss, course, ',');
					a.s_ListCourse[z].ID = course;
					getline(ss, _class, ',');
					a.s_ListCourse[z].className = _class;
				}
			}
			arrClass[i].student[j] = a;
		}
		fin.close();
	}
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
                    fout << arrLecturer[i].L_ListCourse[j].courseID << ',';
					fout << arrLecturer[i].L_ListCourse[j].className << ',';
                }
				if (arrLecturer[i].L_totalCourse >= 1) {
					fout << arrLecturer[i].L_ListCourse[arrLecturer[i].L_totalCourse - 1].courseID << ',';
					fout << arrLecturer[i].L_ListCourse[arrLecturer[i].L_totalCourse - 1].className << '\n';
				}
            }
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
		while (total_lecturer > max_lecturer)
			resizeArrLecturer();
		
        fin.ignore();
        
        string line, user, pass, name, degree, gen, course, num, _class;
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

            while (a.L_totalCourse >= a.L_maxCourse) a.resizeLecturer();

            for (int i = 0; i < a.L_totalCourse; ++i)
            {
                getline(ss, course, ',');
                a.L_ListCourse[i].courseID = course; // co the bug o day
				getline(ss, _class, ',');
				a.L_ListCourse[i].className = _class; // co the bug o day
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

		while (total_course >= max_course) resizeArrCourse();
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
        _coursename = arrCourse[i].getID();
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
                        << ',' << arrCourse[i].Check[j].score[2] << ',' << arrCourse[i].Check[j].score[3] << ',';
                    for (int z = 0; z < 9; ++z)
                    {
                        fout << arrCourse[i].Check[j].attendance[z] << ',';
                    }
                    fout << arrCourse[i].Check[j].attendance[9] << '\n';
                }
            }
            else
            {
                for (int j = 0; j < arrCourse[i].c_totalStudent; ++j)
                {
                    fout << arrCourse[i].c_ListStudent[j] << ',';
                    for (int z = 0; z < 9; ++z)
                    {
                        fout << arrCourse[i].Check[j].attendance[z] << ',';
                    }
                    fout << arrCourse[i].Check[j].attendance[9] << '\n';
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
        fin.open(arrCourse[i].getID() + "-" + arrCourse[i].getClass() + ".txt");
        if (fin.is_open())
        {
            fin >> arrCourse[i].c_totalStudent;
			while (arrCourse[i].c_totalStudent >= arrCourse[i].c_maxStudent)
				arrCourse[i].resizeCourse();
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
                    getline(ss, arrCourse[i].Check[j].score[3], ',');
                    for (int z = 0; z < 10; ++z)
                    {
                        getline(ss, arrCourse[i].Check[j].attendance[z], ',');
                    }
                }
            }
            else
            {
                for (int j = 0; j < arrCourse[i].c_totalStudent; ++j)
                {
                    getline(fin, line);
                    stringstream ss (line);
                    getline(ss, arrCourse[i].c_ListStudent[j], ',');
                    for (int z = 0; z < 10; ++z)
                    {
                        getline(ss, arrCourse[i].Check[j].attendance[z], ',');
                    }
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
				system("pause");
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
            case 9:
                break;
            default:
                break;
        }
		}while(choose);
}

void Semester::ScoreboardOption(){
    ifstream fin;
    ofstream fout;
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
        exportScore(fout);
        system("pause");
        break;
    }
}
void Semester::AttendenceListOption(){
	int choose;
	ofstream fout;
	string _courseID, _className;
	do {
		system("cls");
		cout << "0. Exit\n"
			<< "1. View attendance list\n"
			<< "2. Export a attendance list to a csv file\n";
		cout << "Choose an option: ";
		cin >> choose;
		if (choose == 1) {
			cout << "Which course do you want to view score of? ";
			cin >> _courseID;
			cout << "Of Class? ";
			cin >> _className;
			viewAttendanceListOfACourse(_courseID, _className);
			system("pause");
		}
		else if (choose == 2) {
			exportAttendanceList(fout);
			system("pause");
		}
	} while (choose);
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
				system("cls");
				CheckIn(_ID);
				system("pause");
				break;
			case 2:
				system("cls");
				viewCheckInResult(_ID);
				system("pause");
                break;
            case 3:
				system("cls");
				viewScheduleOfStudent(_ID);
                break;
            case 4:
                //viewScore(string _ID);
                break;
            default:
                break;
        }
    }while(choose);
}

void Semester::LecturerMenu(string _LUsername){
    int choose;
    do{
		system("cls");
        cout << "\nLecturer Menu: \n"
            << "0. Exit \n"
            << "1. View list of courses in the current semester \n"
            << "2. View attendance list of a course \n"
            << "3. Import scoreboard of a course (midterm, final, lab, bonus) from a csv file \n"
            << "4. Edit grade of a student \n"
            << "5. View a scoreboard \n";
        cout << "Choose an option: ";
        cin >> choose;
        switch (choose) {
            case 1:
				system("cls");
                viewCoursesofLecturer(_LUsername);
				system("pause");
                break;
            case 2:
				system("cls");
                viewAttendanceList(_LUsername);
				system("pause");
                break;
            case 3:
                //
                break;
            case 4:
                //editGradeOfAStudent();
                break;
            case 5:
                //viewAScoreBoard();
                break;
            default:
                break;
        }
    }while(choose);
}

void Semester::viewCoursesofLecturer(string _LUsername) {
	Lecturer L = getLecturer(_LUsername);
	int choose;
	do {
		system("cls");
		cout << "NO  " << "Course ID    " << "Class     " << "Day of week    " << "Time start    " << "Time finish" << endl;
		for (int i = 0; i < L.L_totalCourse; ++i) {
			Course c = getCourseOfLecturer(L.L_ListCourse[i].courseID, _LUsername);
			if (c.getStatus() == true) {
				cout << setw(4) << left << i + 1 << setw(13) << left << c.getID() << setw(10) << left << c.getClass() << setw(15) << left << c.getDoW() << c.getsHour() << ":" << setw(11) << left << c.getsMin() << c.geteHour() << ":" << c.geteMin() << endl;
			}
		}
		cout << "\n0. Exit\n";
		cout << "\nChoose a course to view list of student: ";
		cin >> choose;
		if(choose == 1)
		if (choose) {
			Course c = getCourseOfLecturer(L.L_ListCourse[choose - 1].courseID, _LUsername);
			for (int i = 0; i < c.c_totalStudent; ++i) {
				Student s = getStudent(c.c_ListStudent[i]);
				if (s.getStatus() == true)
					cout << s.getID() << " - " << s.getFullName() << endl;
			}
		}
		if (choose)
			system("pause");
	} while (choose);
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

void Semester::viewAttendanceList(string _LUsername) {
	Lecturer L = getLecturer(_LUsername);
	int choose;
	do {
		system("cls");
		cout << "No   " << "Course ID    " << "Class" << endl;
		for (int i = 0; i < L.L_totalCourse; ++i) {
			Course c = getCourseOfLecturer(L.L_ListCourse[i].courseID, _LUsername);
			if (c.getStatus() == true)
				cout << setw(5) << left << i + 1 << setw(13) << left << c.getID() << c.getClass() << endl;
		}
		cout << "\n0. Exit\n";
		cout << "\nChoose a course to view attendance list: ";
		cin >> choose;
		if (choose) {
			Course realC = getCourseOfLecturer(L.L_ListCourse[choose - 1].courseID, _LUsername);
			cout << endl;
			viewAttendanceListOfACourse(realC.getID(), realC.getClass());
			system("pause");
		}
	} while (choose);
}

void Semester::viewAttendanceListOfACourse(string _courseID, string _className) {
	if (isCourseActive(_courseID, _className) == false) {
		cout << "This course does not exist!" << endl;
		return;
	}
	Course c = getCourse(_courseID, _className);
	int s_Day, s_Month, s_Year;
	int length = lengthCourse(_courseID, _className);
	int days = length / 7;
	days++;
	stringstream ss(c.getStartDate());
	int startDate = 0;
	ss >> startDate;
	s_Day = startDate % 100;
	startDate /= 100;
	s_Month = startDate % 100;
	startDate /= 100;
	s_Year = startDate;  
	stringstream convert(c.getDoW());
	int DoW = 2;
	convert >> DoW;
	int between = DoW - 2;
	for (int j = 0; j < between; ++j)
		getTomorow(s_Day, s_Month, s_Year);
	cout << c.getID() << " - " << c.getClass() << endl;
	cout << "\nStudent ID   ";
	for (int j = 0; j < days; ++j) {
		if (s_Day >= 10)
			cout << s_Day << "/";
		else
			cout << "0" << s_Day << "/";
		if (s_Month >= 10)
			cout << s_Month << "/";
		else
			cout << "0" << s_Month << "/";
		cout << s_Year << "   ";
		getWeekAfter(s_Day, s_Month, s_Year);
	}
	cout << endl;
	for (int i = 0; i < c.c_totalStudent; ++i) {
		Student s = getStudent(c.c_ListStudent[i]);
		if (s.getStatus() == true) {
			cout << setw(13) << left << s.getID();
			for (int j = 0; j < days; ++j) {
				cout << setw(13) << left << c.Check[i].attendance[j];
			}
			cout << endl;
		}
	}
	int choose;
	cout << "\n0. Exit\n";
	cout << "1. Edit An attendance\n";
	cout << "\nChoose an option: ";
	cin >> choose;
	string EditID;
	if (choose == 1) {
		cout << "Choose a student to edit\n"
			<< "Student ID: ";
		cin >> EditID;
		if (isStudentActive(EditID) == true)
			editAnAttendance(c.getID(), c.getClass(), EditID);
	}
}

void Semester::editAnAttendance(string _courseID, string _className, string _studentID) {
	int k = 0;
	for (int i = 0; i < total_course; ++i) {
		if (arrCourse[i].getID() == _courseID && arrCourse[i].getClass() == _className) {
			int s_Day, s_Month, s_Year;
			int length = lengthCourse(_courseID, _className);
			int days = length / 7;
			days++;
			stringstream ss(arrCourse[i].getStartDate());
			int startDate = 0;
			ss >> startDate;
			s_Day = startDate % 100;
			startDate /= 100;
			s_Month = startDate % 100;
			startDate /= 100;
			s_Year = startDate;
			stringstream convert(arrCourse[i].getDoW());
			int DoW = 2;
			convert >> DoW;
			int between = DoW - 2;
			for (int j = 0; j < between; ++j)
				getTomorow(s_Day, s_Month, s_Year);
			for (int j = 0; j < days; ++j) {
				cout << j+1 << ": " << s_Day << "/" << s_Month << "/" << s_Year << endl;
				getWeekAfter(s_Day, s_Month, s_Year);
			}
			cout << "Choose the date to edit: ";
			int date;
			cin >> date;
			cout << "\n0: Absent\n1: Attended\n2: Exit\n\n";
			int edit;
			cin >> edit;
			if (edit == 0) {
				arrCourse[i].Check[i].attendance[date - 1] = "0";
				cout << "Edit successful\n";
				system("pause");
			}
			else if (edit == 1) {
				arrCourse[i].Check[i].attendance[date - 1] = "1";
				cout << "Edit successful\n";
				system("pause");
			}
			break;
		}
	}

}

void Semester::DeallocateAll() {
	for (int i = 0; i < total_class; ++i)
		delete[] arrClass[i].student;
	for (int i = 0; i < total_course; ++i) {
		delete[] arrCourse[i].c_ListStudent;
		delete[] arrCourse[i].Check;
	}
	for (int i = 0; i < total_lecturer; ++i) {
		delete[] arrLecturer[i].L_ListCourse;
	}
	delete[] arrClass;
	delete[] arrCourse;
	delete[] arrLecturer;
	delete[] arrStaff;
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
		system("cls");
        cout << "\n1. Show menu \n"
            << "2. View profile info \n"
            << "3. Change password \n"
            << "4. Logout \n\n" ;
        cout << "Choose an option: ";
        cin >> choose;
        switch (choose) {
            case 1:
                LecturerMenu(_ID);
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

Course Semester::getCourseOfLecturer(string _courseID, string _LUsername) {
	for (int i = 0; i < total_course; ++i) {
		if (arrCourse[i].getID() == _courseID && arrCourse[i].getUsername() == _LUsername)
			return arrCourse[i];
	}
	return arrCourse[0];
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
		while (total_staff > max_staff)
			resizeArrStaff();
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

    delete[] ptr;
}

void Semester::resizeArrClass() {
	max_class += 5;
	Class* new_arrClass = new Class[max_class];
	for (int i = 0; i < max_class - 5; ++i) 
		new_arrClass[i] = arrClass[i];
	delete[] arrClass;
	arrClass = new_arrClass;
}

void Semester::resizeArrCourse() {
	max_course += 5;
	Course* new_arrCourse = new Course[max_course];
	for (int i = 0; i < max_course - 5; ++i)
		new_arrCourse[i] = arrCourse[i];
	delete[] arrCourse;
	arrCourse = new_arrCourse;
}
void Semester::resizeArrStaff() {
	max_staff += 5;
	Staff* new_arrStaff = new Staff[max_staff];
	for (int i = 0; i < max_staff - 5; ++i)
		new_arrStaff[i] = arrStaff[i];
	delete[] arrStaff;
	arrStaff = new_arrStaff;
}
void Semester::resizeArrLecturer() {
	max_lecturer += 5;
	Lecturer* new_arrLecturer = new Lecturer[max_lecturer];
	for (int i = 0; i < max_lecturer - 5; ++i)
		new_arrLecturer[i] = arrLecturer[i];
	delete[] arrLecturer;
	arrLecturer = new_arrLecturer;
}

bool Semester::isCourseNow(string _courseID, string _classCourse) {
	int s_Day, e_Day, s_Month, e_Month, s_Year, e_Year, s_Hour, e_Hour, s_Min, e_Min, DoW;
	for (int i = 0; i < total_course; ++i) {
		if (arrCourse[i].getID() == _courseID && arrCourse[i].getClass() == _classCourse) {
			stringstream ss(arrCourse[i].getStartDate());
			int startDate = 0;
			ss >> startDate;
			s_Day = startDate % 100;
			startDate /= 100;
			s_Month = startDate % 100;
			startDate /= 100;
			s_Year = startDate;
			
			ss.clear();
			ss << arrCourse[i].getEndDate();
			int endDate = 0;
			ss >> endDate;
			e_Day = endDate % 100;
			endDate /= 100;
			e_Month = endDate % 100;
			endDate /= 100;
			e_Year = endDate;

			ss.clear();
			ss << arrCourse[i].getsHour();
			ss >> s_Hour;
			ss.clear();
			ss << arrCourse[i].geteHour();
			ss >> e_Hour;
			ss.clear();
			ss << arrCourse[i].getsMin();
			ss >> s_Min;
			ss.clear();
			ss << arrCourse[i].geteMin();
			ss >> e_Min;
			ss.clear();
			ss << arrCourse[i].getDoW();
			ss >> DoW;
			
			time_t t = time(0);   // get time now
			tm* now = localtime(&t);
			int n = rdn(now->tm_year + 1900, now->tm_mon + 1, now->tm_mday) - rdn(s_Year, s_Month, s_Day) - DoW + 2;
			if (n % 7 == 0) {
				if (now->tm_hour > s_Hour && now->tm_hour < e_Hour)
					return true;
				else if (now->tm_hour > s_Hour&& now->tm_hour == e_Hour) {
					if (now->tm_min <= e_Min)
						return true;
					return false;
				}
				else if (now->tm_hour == s_Hour && now->tm_hour < e_Hour) {
					if (now->tm_min >= s_Min)
						return true;
					return false;
				}
				else if (now->tm_hour == s_Hour && now->tm_hour == e_Hour) {
					if (now->tm_min >= s_Min && now->tm_min <= e_Min)
						return true;
					return false;
				}
			}
			return false;
		}
	}
	return false;
}

int Semester::rdn(int y, int m, int d) {
	if (m < 3)
		y--, m += 12;
	return 365 * y + y / 4 - y / 100 + y / 400 + (153 * m - 457) / 5 + d - 306;
}

int Semester::getDaysBetween(string sDate, string _Dow) {
	int s_Day, s_Month, s_Year, DoW = 0;
	stringstream ss(sDate);
	int startDate = 0;
	ss >> startDate;
	s_Day = startDate % 100;
	startDate /= 100;
	s_Month = startDate % 100;
	startDate /= 100;
	s_Year = startDate;
	stringstream convert(_Dow);
	convert >> DoW;
	time_t t = time(0);   // get time now
	tm* now = localtime(&t);
	int n = (rdn(now->tm_year + 1900, now->tm_mon + 1, now->tm_mday) - rdn(s_Year, s_Month, s_Day) - DoW + 2);
	return n;
}

int Semester::lengthCourse(string _courseID, string _className) {
	int s_Day, e_Day, s_Month, e_Month, s_Year, e_Year;
	for (int i = 0; i < total_course; ++i) {
		if (arrCourse[i].getID() == _courseID && arrCourse[i].getClass() == _className) {
			stringstream ss(arrCourse[i].getStartDate());
			int startDate = 0;
			ss >> startDate;
			s_Day = startDate % 100;
			startDate /= 100;
			s_Month = startDate % 100;
			startDate /= 100;
			s_Year = startDate;

			stringstream convert(arrCourse[i].getEndDate());
			int endDate = 0;
			convert >> endDate;
			e_Day = endDate % 100;
			endDate /= 100;
			e_Month = endDate % 100;
			endDate /= 100;
			e_Year = endDate;

			return rdn(e_Year, e_Month, e_Day) - rdn(s_Year, s_Month, s_Day);
		}
	}
	return 0;
}

void Semester::getTomorow(int& day, int& month, int& year) {
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{
		if (day >= 1 && day <= 30)
			day++;
		else if (day == 31 && month == 12) {
			day = 1;
			month = 1;
			year++;
		}
		else if (day == 31 && month != 12) {
			day = 1;
			month++;
		}
	}
	else if(month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day >= 1 && day <= 29)
			day++;
		else if (day == 30)
			month++;
	}
	else if (month == 2) {
		if (year % 4 == 0)
			if (year % 100 == 0 and year % 400 != 0)
				if (day >= 1 and day <= 27)
					day++;
				else
					month++;
			else
				if (day >= 1 and day <= 28)
					day++;
				else
					month++;
		else
			if (day >= 1 and day <= 27)
				day++;
			else {
				day = 1;
				month++;
			}
	}
}

void Semester::getWeekAfter(int& day, int& month, int& year) {
	for (int i = 0; i < 7; ++i)
		getTomorow(day, month, year);
}


void Semester::viewStudentCourseNow(string _studentID) {
	int choose;
	Student a = getStudent(_studentID);
	int k = 0;
	for (int i = 0; i < a.getNumberofCourse(); ++i) {
		if (isCourseActive(a.s_ListCourse[i].ID, a.s_ListCourse[i].className) == true) {
			if (isCourseNow(a.s_ListCourse[i].ID, a.s_ListCourse[i].className) == true) {
				Course c = getCourse(a.s_ListCourse[i].ID, a.s_ListCourse[i].className);
				++k;
				cout << k << ": " <<  c.getID() << " - " << c.getClass() << ": " << c.getsHour() << "h" << c.getsMin() << " to " << c.geteHour() << "h" << c.geteMin() << endl;
			}
		}
	}
	if (k == 0)
		cout << "You do not have any classtime right now \n";
	else {
		int k = 0;
		cout << "Choose a course to check in: ";
		cin >> choose;
		for (int i = 0; i < a.getNumberofCourse(); ++i) {
			if (isCourseActive(a.s_ListCourse[i].ID, a.s_ListCourse[i].className) == true) {
				if (isCourseNow(a.s_ListCourse[i].ID, a.s_ListCourse[i].className) == true) {
					Course c = getCourse(a.s_ListCourse[i].ID, a.s_ListCourse[i].className);
					++k;
					if (k == choose) {
						for (int x = 0; x < total_course; ++x) {
							if (arrCourse[x].getID() == a.s_ListCourse[i].ID && arrCourse[x].getClass() == a.s_ListCourse[i].className) {
								int days = getDaysBetween(arrCourse[x].getStartDate(), arrCourse[x].getDoW());
								int pos = days / 7;
								for (int y = 0; y < arrCourse[x].c_totalStudent; ++y)
									if (arrCourse[x].c_ListStudent[y] == _studentID)
										arrCourse[x].Check[y].attendance[pos] = "1";
							}
						}
						break;
					}
				}
			}
		}

	}
}

void Semester::CheckIn(string _ID) {
	viewStudentCourseNow(_ID);
	system("pause");
}

void Semester::viewCheckInResult(string _studentID) {
	Student s = getStudent(_studentID);
	for (int i = 0; i < s.numberofCourse; ++i) {
		if (isCourseActive(s.s_ListCourse[i].ID, s.s_ListCourse[i].className))
			cout << i+1 << ". " << s.s_ListCourse[i].ID << " - " << s.s_ListCourse[i].className << endl;
		else
			cout << i+1 << ". This course has been removed" << endl;
	}
	int choose;
	cout << "Choose a course to view attendance status: ";
	cin >> choose;
	choose--;
	viewAStudentAttendanceOfACourse(_studentID, s.s_ListCourse[choose].ID, s.s_ListCourse[choose].className);
}

void Semester::viewAStudentAttendanceOfACourse(string _studentID, string _courseID, string _className){
	Course c = getCourse(_courseID, _className);
	int s_Day, s_Month, s_Year;
	for (int i = 0; i < c.c_totalStudent; ++i) {
		if (c.c_ListStudent[i] == _studentID) {
			int length = lengthCourse(_courseID, _className);
			int days = length / 7;
			days++;
			stringstream ss(c.getStartDate());
			int startDate = 0;
			ss >> startDate;
			s_Day = startDate % 100;
			startDate /= 100;
			s_Month = startDate % 100;
			startDate /= 100;
			s_Year = startDate;
			stringstream convert(c.getDoW());
			int DoW = 2;
			convert >> DoW;
			int between = DoW - 2;
			for (int j = 0; j < between; ++j)
				getTomorow(s_Day, s_Month, s_Year);
			for (int j = 0; j < days; ++j) {
				cout << s_Day << "/" << s_Month << "/" << s_Year << ": " << c.Check[i].attendance[j] << endl;
				getWeekAfter(s_Day, s_Month, s_Year);
			}
		}
	}
}


void Semester::viewScheduleOfStudent(string _ID) {
	Student s = getStudent(_ID);
	cout << "NO  " << "Course ID    " << "Course name             " << "Start Date    " << "End Date    " << "Day of week    " << "Time start    " << "Time finish" << endl;
	for (int i = 0; i < s.numberofCourse; ++i) {
		if (isCourseActive(s.s_ListCourse[i].ID, s.s_ListCourse[i].className) == true) {
			Course c = getCourse(s.s_ListCourse[i].ID, s.s_ListCourse[i].className);
			cout << setw(4) << left << i+1 << setw(13) << left << c.getID() << setw(24) << left << c.getCourseName() << setw(14) << left << c.getStartDate() << setw(12) << left << c.getEndDate() << setw(15) << left << c.getDoW() <<  c.getsHour() << ":" << setw(11) << left << c.getsMin() << c.geteHour() << ":" << c.geteMin() << endl;
		}
	}
}


void Semester::exportScore(ofstream& fout)
{
    string _class, course;
    cin.ignore(100, '\n');
    cout << "Which class do you want to export scoreboard? ";
    getline(cin, _class);
    cout << "Of which course? ";
    getline(cin, course);
    int exist = 0;

    for (int i = 0; i < total_course; ++i)
    {
        if (arrCourse[i].getID() == course && arrCourse[i].getClass() == _class && arrCourse[i].point == true)
        {
            exist = 1;
            fout.open("Scoreboard.csv");
            if (fout.is_open())
            {
                fout << "ID, Midterm, Final, Bonus, Total\n";
                for (int j = 0; j < arrCourse[i].c_totalStudent; ++j)
                {
                    fout << arrCourse[i].c_ListStudent[j] << ',' << arrCourse[i].Check[j].score[0] << ','
                        << arrCourse[i].Check[j].score[1] << ',' << arrCourse[i].Check[j].score[2] << ','
                        << arrCourse[i].Check[j].score[3] << '\n';
                }
                fout.close();
                cout << "Export succesfully\n";
            }
            else cout << "Cannot open file csv to output! ";
        }
    }
    if (exist == 0) cout << "This course has no scoreboard yet! ";
}

void Semester::exportAttendanceList(ofstream& fout) {
	string _courseID, _className;
	cout << "Which course do you want to export scoreboard? ";
	cin >> _courseID;
	cout << "Of which class? ";
	cin >> _className;
	Course c = getCourse(_courseID, _className);
	if (c.getStatus() == false) {
		cout << "This course does not exist!" << endl;
		return;
	}
	string link = _courseID + "-" + _className + "-attendance.csv";
	fout.open(link);
	fout << " ", ",";
	int s_Day, s_Month, s_Year;
	int length = lengthCourse(_courseID, _className);
	int days = length / 7;
	days++;
	stringstream ss(c.getStartDate());
	int startDate = 0;
	ss >> startDate;
	s_Day = startDate % 100;
	startDate /= 100;
	s_Month = startDate % 100;
	startDate /= 100;
	s_Year = startDate;
	stringstream convert(c.getDoW());
	int DoW = 2;
	convert >> DoW;
	int between = DoW - 2;
	for (int j = 0; j < between; ++j)
		getTomorow(s_Day, s_Month, s_Year);
	fout << "Student ID " << ",";
	for (int j = 0; j < days; ++j) {
		if (s_Day >= 10)
			fout << s_Day << "/";
		else
			fout << "0" << s_Day << "/";
		if (s_Month >= 10)
			fout << s_Month << "/";
		else
			fout << "0" << s_Month << "/";
		if (j == days - 1) {
			fout << s_Year << "\n";
			break;
		}
		fout << s_Year << ",";
		getWeekAfter(s_Day, s_Month, s_Year);
	}
	for (int i = 0; i < c.c_totalStudent; ++i) {
		fout << c.c_ListStudent[i] << ",";
		for (int j = 0; j < days; ++j) {
			if (j == days - 1) {
				fout << c.Check[i].attendance[j] << "\n";
				break;
			}
			fout << c.Check[i].attendance[j] << ",";
		}
	}
	fout.close();
}

void Semester::runProgram(ifstream& fin, ofstream& fout) {
	ifstream f1;
	ofstream f2;
	f1.open("-.txt");
	string check;
	if (f1.is_open() == false) cout << "Can not open file to check!\n";
	else {
		f1 >> check;
		if (check == "0") {
			loadStudentsFromCSV(fin);
			loadLecturersFromCSV(fin);
			loadCoursesFromCSV(fin);
			loadStaffsFromCSV(fin);
		}
		else {
			loadLecturersFromTxt(fin);
			loadClassesFromTxt(fin);
			loadEachClassFromTxt(fin);
			loadAllCoursesFromTxt(fin);
			loadEachCourseFromTxt(fin);
			loadStaffsFromTxt(fin);
		}
		Login();
		loadClassesToTxt(fout);
		loadEachClassToTxt(fout);
		loadAllCoursesToTxt(fout);
		loadEachCourseToTxt(fout);
		loadLecturersToTxt(fout);
		loadStaffsToTxt(fout);

		DeallocateAll();

		f1.close();
		f2.open("-.txt");
		f2 << "1";
		f2.close();

		cout << "\nSucceeded\n" << endl;
	}
}
