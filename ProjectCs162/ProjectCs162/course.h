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
        int c_totalStudent;
public:
    string c_ListStudent[100];
    void setStatus(bool _status){
        c_status = _status;
    }
    void setNo(int _No){
        c_No = _No;
    }
    void setID(int _ID){
        c_ID = _ID;
    }
    void setLUsername(string _LUsername){
        c_LUsername = _LUsername;
    }
    void setLName(string _LName){
        c_LName = _LName;
    }
    void setClass(string _Class){
        c_Class = _Class;
    }
    void setLDegree(string _LDegree){
        c_LDegree = _LDegree;
    }
    void setRoom(string _Room){
        c_Room = _Room;
    }
    void setLGender(bool _LGender){
        c_LGender = _LGender;
    }
    void setYear(int _year){
        c_year = _year;
    }
    void setMonth(int _month){
        c_month = _month;
    }
    void setday(int _day){
        c_day = _day;
    }
    void setsHour(int _sHour){
        c_sHour = _sHour;
    }
    void setsMin(int _sMin){
        c_sMin = _sMin;
    }
    void seteHour(int _eHour){
        c_eHour = _eHour;
    }
    void seteMin(int _eMin){
        c_eMin = _eMin;
    }
    void sedDoW(string _DoW){
        c_DoW = _DoW;
    }
    void setTime(int _year, int _month, int _day, int _sHour, int _sMin, int _eHour, int _eMin, string _DoW){
        c_year = _year;
        c_month = _month;
        c_day = _day;
        c_DoW = _DoW;
        c_sHour = _sHour;
        c_sMin = _sMin;
        c_eHour = _eHour;
        c_eMin = _eMin;
    }
    void setTotalStudent(int _totalStudent){
        c_totalStudent = _totalStudent;
    }
    bool getStatus(){
        return c_status;
    }
    int getNo(){
        return c_No;
    }
    string getID(){
        return c_ID;
    }
    string getUsername(){
        return c_LUsername;
    }
    string getLName(){
        return c_LName;
    }
    string getClass(){
        return c_Class;
    }
    string getLDegree(){
        return c_LDegree;
    }
    bool getLGender(){
        return c_LGender;
    }
    int getYear(){
        return c_year;
    }
    int getMonth(){
        return c_month;
    }
    int getDay(){
        return c_day;
    }
    int getsHour(){
        return c_sHour;
    }
    int getsMin(){
        return c_sMin;
    }
    int geteHour(){
        return c_eHour;
    }
    int geteMin(){
        return c_eMin;
    }
    string getDoW(){
        return c_DoW;
    }
    int getTotalStudent(){
        return c_totalStudent;
    }
    
    Course(){
        c_totalStudent = 0;
    }
};

#endif
