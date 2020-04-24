#ifndef lecturer_h
#define lecturer_h

#include "include.h"

class Lecturer{
    private:
        string l_name, l_degree, l_userName, l_password;
        bool l_gender;
    public:
    string L_ListCourse[10];
    void setName(string _name){
        l_name = _name;
    }
    void setDegree(string _degree){
        l_degree = _degree;
    }
    void setUserName(string _userName){
        l_userName = _userName;
    }
    void setPassword(string _password){
        l_password = _password;
    }
    string gerDegree(){
        return l_degree;
    }
};

#endif
