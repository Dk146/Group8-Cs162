#include "lecturer.h"

void Lecturer::setName(string _name){
    l_name = _name;
}
void Lecturer::setDegree(string _degree){
    l_degree = _degree;
}
void Lecturer::setUserName(string _userName){
    l_userName = _userName;
}
void Lecturer::setPassword(string _password){
    l_password = _password;
}
void Lecturer::setGender(bool _gender){
    l_gender = _gender;
}
string Lecturer::getDegree(){
    return l_degree;
}
string Lecturer::getName(){
    return l_name;
}
string Lecturer::getUserName(){
    return l_userName;
}
string Lecturer::getPassword(){
    return l_password;
}
bool Lecturer::getGender(){
    return l_gender;
}
void Lecturer::resizeLecturer() {
	L_maxCourse += 5;
	string* new_ListCourse = new string[L_maxCourse];
	for (int i = 0; i < L_totalCourse; ++i) {
		new_ListCourse[i] = L_ListCourse[i];
	}
	delete[] L_ListCourse;
	L_ListCourse = new_ListCourse;
}