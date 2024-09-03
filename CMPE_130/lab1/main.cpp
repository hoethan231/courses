#include <iostream>
#include <fstream>
#include <sstream>
#include "student.h"
#include "roster.h"

int main() {

    Roster r = Roster();

    std::ifstream classList("roster.txt");
    std::string line;

    while(getline(classList, line)) {
        std::stringstream ss(line);
        std::string field;

        getline(ss, field, ',');
        int studentId = stoi(field);

        getline(ss, field, ',');
        std::string firstName = field;

        getline(ss, field, ',');
        std::string lastName = field;

        getline(ss, field, ',');
        std::string academicLevel = field;

        Student student(studentId, firstName, lastName, academicLevel);
        r.insert(student);
    }
    classList.close();
    
    r.printAll();

    Student student1(3333, "linear", "francisco", "senior");
    r.remove(student1);
    r.printAll();

    Student student2(1212, "ho", "ethan", "sophmore");
    r.insert(student2);
    r.update(student2, 1313, "so", "athan", "sophmore");
    r.printAll();

    return 0;

};