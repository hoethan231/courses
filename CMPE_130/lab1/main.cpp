#include <iostream>
#include <fstream>
#include <sstream>
#include "student.h"
#include "roster.h"

int main() {

    Roster r = Roster();
    
    r.printAll();

    Student student1(3333, "linear", "francisco", "senior");
    r.insert(student1);
    r.printAll();
    r.remove(student1);

    Student student2(1212, "ho", "ethan", "sophomore");
    r.insert(student2);
    r.update(student2, 1313, "so", "athan", "sophomore");
    r.printAll();

    return 0;

};