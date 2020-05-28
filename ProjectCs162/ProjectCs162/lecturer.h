#ifndef lecturer_h
#define lecturer_h

#include "include.h"

class Lecturer{
private:
    string l_name, l_degree, l_userName, l_password;
    bool l_gender;
public:
    int L_totalCourse;
	int L_maxCourse;
    string*L_ListCourse;
    
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
    
	void resizeLecturer();

    Lecturer(){
        L_totalCourse = 0;
		L_maxCourse = 10;
		L_ListCourse = new string[L_maxCourse];
    }
};

#endif
