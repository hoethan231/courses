#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>

class Student {

    private: 
        int id;
        std::string first;
        std::string last;
        std::string grade;

    public:
        Student();
        Student(int, std::string, std::string, std::string);
        void setID(int);
        void setFirst(std::string);
        void setLast(std::string);
        void setGrade(std::string);
        int getID();
        std::string getFirst();
        std::string getLast();
        std::string getGrade();
        friend std::ostream& operator<<(std::ostream&, const Student&);

};

#endif