#ifndef course_h
#define course_h

#include "include.h"

class Course{
private:
    int c_No;
    string c_ID, c_CName, c_Room, c_LUsername, c_LName, c_LDegree, c_Class;
    bool c_LGender, c_status; // 1 is active, 0 is inactive
    int c_year, c_month, c_day, c_sHour, c_sMin, c_eHour, c_eMin;
    string c_DoW;
public:
    
    int c_totalStudent;
    string c_ListStudent[100];
    
    void setStatus(bool _status);
    void setNo(int _No);
    void setID(int _ID);
    void setLUsername(string _LUsername);
    void setLName(string _LName);
    void setClass(string _Class);
    void setLDegree(string _LDegree);
    void setRoom(string _Room);
    void setLGender(bool _LGender);
    void setYear(int _year);
    void setMonth(int _month);
    void setday(int _day);
    void setsHour(int _sHour);
    void setsMin(int _sMin);
    void seteHour(int _eHour);
    void seteMin(int _eMin);
    void sedDoW(string _DoW);
    void setTime(int _year, int _month, int _day, int _sHour, int _sMin, int _eHour, int _eMin, string _DoW);
    void setTotalStudent(int _totalStudent);
    bool getStatus();
    int getNo();
    string getID();
    string getUsername();
    string getLName();
    string getClass();
    string getLDegree();
    bool getLGender();
    int getYear();
    int getMonth();
    int getDay();
    int getsHour();
    int getsMin();
    int geteHour();
    int geteMin();
    string getDoW();
    int getTotalStudent();

    Course(){
        c_totalStudent = 0;
    }
};

#endif
