#ifndef lecturer_h
#define lecturer_h

#include "include.h"

class Lecturer{
private:
    string l_name, l_degree, l_userName, l_password;
    bool l_gender;
public:
    string L_ListCourse[10];
    
    void setName(string _name);
    void setDegree(string _degree);
    void setUserName(string _userName);
    void setPassword(string _password);
    void setGender(bool _gender);
    string getName();
    string getDegree();
    string getUserName();
    string getPassword();
    bool getGender();
};

#endif
