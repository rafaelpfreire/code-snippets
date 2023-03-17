#include <iostream>
#include <cstring>

// When a class is manually managing at least one dynamically allocated resource.
// The Rule of Five states that if a type ever needs one of the following, then it must have all five.
// copy constructor
// copy assignment
// destructor
// move constructor
// move assignment

class Student {
private:
    int id;
    char* name;

public:
    Student() {
        this->id = 0;
        this->name = nullptr;
    }

    Student(const char* name, int id) {
        this->id = id;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    ~Student() {
        delete[] this->name;
    }
};

int main() {
    Student s1("John", 10);

    // This line will case a double free exception at the end of the program because
    // the default copy constructor provided will do a shallow copy, meaning
    // that s2.name and s1.name points to the same string object. When you destruct
    // one of them, the other will try to delete the name again causing the exception.
    // If the constructors and assigments of the rule of 5 were defined, this wouldn't
    // happen because one would define a deep copy of the name string.
    Student s2 = s1;

    return 0;
}
