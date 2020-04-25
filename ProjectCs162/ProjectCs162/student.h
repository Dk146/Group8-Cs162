#ifndef student_h
#define student_h

#include "include.h"

class Student{
private:
    
    int No, ID;
    string lastname, firstname, doB;
    string username, password;
    bool gender; //1 is male; 0 is female
    
public:
    
    int numberofCourse;
    string s_ListCourse[10];
    void setID(int _ID);
    void setNo(int _No);
    void setLastName(string _lastname);
    void setFirstName(string _firstname);
    void setDoB(string _doB);
    void setGender(bool _gender);
    void setNumberofCourse(int _number);
    void setUsername(string _name);
    void setPass(string _pass);
    string getUsername();
    string getPass();
    int getID();
    int getNo();
    string getLastName();
    string getFirstName();
    string getDoB();
    bool getGender(bool _gender);
    int getNumberofCourse();
    void createAccount();
    
};


#endif
