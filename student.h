#ifndef student_h
#define student_h

#include "include.h"

class Student{
    private:
        int No, ID;
        string lastname, firstname, doB;
        string username, password;
        int numberofCourse;
        bool gender; //1 is male; 0 is female
    public:
        string s_ListCourse[10];
        void setID(int _ID){
            ID = _ID;
        }
        void setNo(int _No){
            No = _No;
        }
        void setLastName(string _lastname){
            lastname = _lastname;
        }
        void setFirstName(string _firstname){
            firstname = _firstname;
        }
        void setDoB(string _doB){
            doB = _doB;
        }
        void setGender(bool _gender){
            gender = _gender;
        }
        void setNumberofCourse(int _number){
            numberofCourse = _number;
        }
        void setUsername(string _name){
            username = _name;
        }
        void setPass(string _pass){
            password = _pass;
        }
        string getUsername(){
            return username;
        }
        string getPass(){
            return password;
        }
        int getID(){
            return ID;
        }
        int getNo(){
            return No;
        }
        string getLastName(){
            return lastname;
        }
        string getFirstName(){
            return firstname;
        }
        string getDoB(){
            return doB;
        }
        bool getGender(bool _gender){
            return gender;
        }
        int getNumberofCourse(){
            return numberofCourse;
        }
        
    
        Student(){
            numberofCourse = 0;
        }

        Student(int _No, int _ID, string _lastname, string _firstname, string _doB, bool _gender){
            setNo(_No);
            setID(_ID);
            setLastName(_lastname);
            setFirstName(_firstname);
            setDoB(_doB);
            setGender(_gender);
        }
        void createAccount(){
            username = ID;
            password = doB + "hcmus";
        }
};


#endif
