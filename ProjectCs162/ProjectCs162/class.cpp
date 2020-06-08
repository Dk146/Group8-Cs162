#include "class.h"

void Class::settotalStudent(int _totalStudent){
    totalStudent = _totalStudent;
}
void Class::setClassName(string _className){
    ClassName = _className;
}
string Class::getClassName(){
    return ClassName;
}
void Class::addStudent(Student new_student){
    student[totalStudent] = new_student;
    ++totalStudent;
}
void Class::resizeClass() {
	max_student += 5;
	cout << "Yes" << endl;
	Student* new_student = new Student[max_student];
	for (int i = 0; i < max_student - 5; ++i) {
		new_student[i] = student[i];
	}
	delete[] student;
	student = new_student;
}
