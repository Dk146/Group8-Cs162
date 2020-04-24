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
