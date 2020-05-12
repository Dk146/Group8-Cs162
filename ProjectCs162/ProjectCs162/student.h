#ifndef student_h
#define student_h

#include "include.h"

class Student{
private:
    int No;
    string ID, fullname, doB;
    string username, password;
    bool gender; //1 is male; 0 is female
    bool status;
    
public:
    
    int numberofCourse;
    string s_ListCourse[10];
    
    void setID(string _ID);
    void setNo(int _No);
    void setFullName(string _fullname);
    void setDoB(string _doB);
    void setGender(bool _gender);
    void setStatus(bool _status);
    void setNumberofCourse(int _number);
    void setUsername(string _name);
    void setPass(string _pass);
    string getUsername();
    string getPass();
    string getID();
    int getNo();
    string getFullName();
    string getDoB();
    bool getGender();
    bool getStatus();
    int getNumberofCourse();
    void createAccount();
    
    Student(){
        status = true;
        numberofCourse = 0;
    }
};


#endif
