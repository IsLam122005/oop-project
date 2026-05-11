#include "User.h"

// User Constructor
User::User(string u_name, string u_id) {
    name = u_name;
    campusID = u_id;
}

// Student Implementation
Student::Student(string u_name, string u_id) : User(u_name, u_id) {}

bool Student::isStaffMember() const {
    return false; // Students don't get the staff discount
}

// Staff Implementation
Staff::Staff(string u_name, string u_id) : User(u_name, u_id) {}

bool Staff::isStaffMember() const {
    return true; // Staff gets the discount
}