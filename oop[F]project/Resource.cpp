#include "Resource.h"

// Resource
Resource::Resource(int r_id, string r_name, double r_price, int r_stock) {
    id = r_id;
    name = r_name;
    price = r_price;
    stock = r_stock;
}

void Resource::display() const {
    cout << "ID: " << id << " | Name: " << name
        << " | Price: " << price << " | Stock: " << stock << endl;
}

void Resource::restock(int amount) {
    stock += amount;
}

bool Resource::purchase(int amount) {
    if (amount > stock) {
        cout << "Error: Transaction blocked. Not enough stock!" << endl;
        return false;
    }
    stock -= amount;
    return true;
}

bool Resource::operator>(const Resource& other) const {
    return this->price > other.price;
}

// LabHardware
LabHardware::LabHardware(int r_id, string r_name, double r_price, int r_stock, int warranty)
    : Resource(r_id, r_name, r_price, r_stock) {
    warrantyMonths = warranty;
}

void LabHardware::display() const {
    Resource::display();
    cout << "Warranty: " << warrantyMonths << " months\n" << endl;
}

// CafeteriaPerishables
CafeteriaPerishables::CafeteriaPerishables(int r_id, string r_name, double r_price, int r_stock, string expiry)
    : Resource(r_id, r_name, r_price, r_stock) {
    expiryDate = expiry;
}

void CafeteriaPerishables::display() const {
    Resource::display();
    cout << "Expiry Date: " << expiryDate << "\n" << endl;
}

// BookstoreMedia
BookstoreMedia::BookstoreMedia(int r_id, string r_name, double r_price, int r_stock, string auth)
    : Resource(r_id, r_name, r_price, r_stock) {
    author = auth;
}

void BookstoreMedia::display() const {
    Resource::display();
    cout << "Author: " << author << "\n" << endl;
}