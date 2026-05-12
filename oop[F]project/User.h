#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

// Base Class: User
// Design Defense: Made User an Abstract Class with a pure virtual function isStaffMember() to force runtime Polymorphism.
class User {
protected:
    string name;
    string campusID;

public:
    User(string u_name, string u_id);
    virtual ~User() {}

    // Getters
    string getName() const { return name; }
    string getCampusID() const { return campusID; }

    // Pure virtual function (Makes User an Abstract Class)
    virtual bool isStaffMember() const = 0;
};

// Derived Class 1: Student
class Student : public User {
public:
    Student(string u_name, string u_id);
    bool isStaffMember() const override;
};

// Derived Class 2: Staff
class Staff : public User {
public:
    Staff(string u_name, string u_id);
    bool isStaffMember() const override;
};

#endif