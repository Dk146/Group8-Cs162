#include "course.h"

void Course::setStatus(bool _status){
    c_status = _status;
}
void Course::setNo(int _No){
    c_No = _No;
}
void Course::setID(string _ID){
    c_ID = _ID;
}
void Course::setCourseName(string _CourseName){
    c_CourseName = _CourseName;
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
void Course::setStartDate(string _startDate){
    c_startDate = _startDate;
}
void Course::setEndDate(string _endDate){
    c_endDate = _endDate;
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
void Course::setDoW(string _DoW){
    c_DoW = _DoW;
}
void Course::setTime(string _startDate, string _endDate, int _sHour, int _sMin, int _eHour, int _eMin, string _DoW){
    c_startDate = _startDate;
    c_endDate = _endDate;
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
string Course::getCourseName(){
    return c_CourseName;
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
string Course::getStartDate(){
    return c_startDate;
}
string Course::getEndDate(){
    return c_endDate;
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
