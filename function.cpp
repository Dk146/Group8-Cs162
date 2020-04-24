#include "include.h"
#include "student.h"
#include "course.h"
#include "lecturer.h"
#include "class.h"

void addStudentToCourse(int _studentID, string _courseID, Class aClass[], Course course[], string class_name, int total_class, int total_course){
    int temp = 0;
    for(int i = 0; i < total_class; ++i){
        if(aClass[i].getClassName() == class_name){
            for (int j = 0; j < aClass[i].gettotalStudent(); ++j){
                if(aClass[i].getStudent(j).getID() == _studentID){
                    int k = aClass[i].getStudent(j).getNumberofCourse();
                    aClass[i].getStudent(j).s_ListCourse[k] = _courseID;
                    ++k;
                    aClass[i].getStudent(j).setNumberofCourse(k);
                    temp++;
                    break;
                }
            }
            if (temp != 0)
                break;
        }
    }
    for (int i = 0; i < total_course; ++i){
        if(course[i].getID() == _courseID){
            int k = course[i].getTotalStudent();
            course[i].c_ListStudent[k] = _studentID;
            break;
        }
    }
}

void addCourseToClass(string _courseID, Class aClass[], Course course[], string class_name, int total_class, int total_course){
    int s_InClass = 0;
    int pos_class = 0;
    for(int i = 0; i < total_class; ++i){
        if(aClass[i].getClassName() == class_name){
            pos_class = i;
            for (int j = 0; j < aClass[j].gettotalStudent(); ++j){
                int k = aClass[i].getStudent(j).getNumberofCourse();
                aClass[i].getStudent(j).s_ListCourse[k] = _courseID;
                ++k;
                aClass[i].getStudent(j).setNumberofCourse(k);
            }
            s_InClass = aClass[i].gettotalStudent();
        }
    }
    for (int i = 0; i < total_course; ++i){
        int s_InCourse = 0;
        if(course[i].getID() == _courseID){
            s_InCourse = course[i].getTotalStudent();
            int temp = 0;
            for (int j = s_InCourse; j < s_InCourse + s_InClass; ++j){
                course[i].c_ListStudent[j] = aClass[pos_class].getStudent(temp++).getID();
            }
            course[i].setTotalStudent(s_InCourse + s_InClass);
        }
    }
}

