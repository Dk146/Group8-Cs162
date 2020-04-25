#include "student.h"

    void Student::setID(int _ID){
        ID = _ID;
    }
    void Student::setNo(int _No){
        No = _No;
    }
    void Student::setLastName(string _lastname){
        lastname = _lastname;
    }
    void Student::setFirstName(string _firstname){
        firstname = _firstname;
    }
    void Student::setDoB(string _doB){
        doB = _doB;
    }
    void Student::setGender(bool _gender){
        gender = _gender;
    }
    void Student::setNumberofCourse(int _number){
        numberofCourse = _number;
    }
    void Student::setUsername(string _name){
        username = _name;
    }
    void Student::setPass(string _pass){
        password = _pass;
    }
    string Student::getUsername(){
        return username;
    }
    string Student::getPass(){
        return password;
    }
    int Student::getID(){
        return ID;
    }
    int Student::getNo(){
        return No;
    }
    string Student::getLastName(){
        return lastname;
    }
    string Student::getFirstName(){
        return firstname;
    }
    string Student::getDoB(){
        return doB;
    }
    bool Student::getGender(bool _gender){
        return gender;
    }
    int Student::getNumberofCourse(){
        return numberofCourse;
    }
    void Student::createAccount(){
        username = ID;
        password = doB;
    }
    