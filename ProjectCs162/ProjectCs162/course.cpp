#include "course.h"

void Course::setStatus(bool _status){
    c_status = _status;
}
void Course::setNo(int _No){
    c_No = _No;
}
void Course::setID(int _ID){
    c_ID = _ID;
}
void Course::setLUsername(string _LUsername){
    c_LUsername = _LUsername;
}
void Course::setLName(string _LName){
    c_LName = _LName;
}
void Course::setClass(string _Class){
    c_Class = _Class;
}
void Course::setLDegree(string _LDegree){
    c_LDegree = _LDegree;
}
void Course::setRoom(string _Room){
    c_Room = _Room;
}
void Course::setLGender(bool _LGender){
    c_LGender = _LGender;
}
void Course::setYear(int _year){
    c_year = _year;
}
void Course::setMonth(int _month){
    c_month = _month;
}
void Course::setday(int _day){
    c_day = _day;
}
void Course::setsHour(int _sHour){
    c_sHour = _sHour;
}
void Course::setsMin(int _sMin){
    c_sMin = _sMin;
}
void Course::seteHour(int _eHour){
    c_eHour = _eHour;
}
void Course::seteMin(int _eMin){
    c_eMin = _eMin;
}
void Course::sedDoW(string _DoW){
    c_DoW = _DoW;
}
void Course::setTime(int _year, int _month, int _day, int _sHour, int _sMin, int _eHour, int _eMin, string _DoW){
    c_year = _year;
    c_month = _month;
    c_day = _day;
    c_DoW = _DoW;
    c_sHour = _sHour;
    c_sMin = _sMin;
    c_eHour = _eHour;
    c_eMin = _eMin;
}
void Course::setTotalStudent(int _totalStudent){
    c_totalStudent = _totalStudent;
}
bool Course::getStatus(){
    return c_status;
}
int Course::getNo(){
    return c_No;
}
string Course::getID(){
    return c_ID;
}
string Course::getUsername(){
    return c_LUsername;
}
string Course::getLName(){
    return c_LName;
}
string Course::getClass(){
    return c_Class;
}
string Course::getLDegree(){
    return c_LDegree;
}
bool Course::getLGender(){
    return c_LGender;
}
int Course::getYear(){
    return c_year;
}
int Course::getMonth(){
    return c_month;
}
int Course::getDay(){
    return c_day;
}
int Course::getsHour(){
    return c_sHour;
}
int Course::getsMin(){
    return c_sMin;
}
int Course::geteHour(){
    return c_eHour;
}
int Course::geteMin(){
    return c_eMin;
}
string Course::getDoW(){
    return c_DoW;
}
int Course::getTotalStudent(){
    return c_totalStudent;
}
