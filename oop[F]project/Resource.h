#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>
#include <string>

using namespace std;

// 1. Base Class: Resource
class Resource {
protected:
    int id;
    string name;
    double price;
    int stock;

public:
    // Constructor
    Resource(int r_id, string r_name, double r_price, int r_stock);

    // Virtual Destructor (Crucial for Polymorphism)
    virtual ~Resource() {}

    // Core Functions (Virtual so derived classes can override them)
    virtual void display() const;
    virtual void restock(int amount);
    virtual bool purchase(int amount);

    // Operator Overloading (Cost Comparison Logic)
    bool operator>(const Resource& other) const;

    // Getters for accessing data later
    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }
};

// 2. Derived Class 1: LabHardware
class LabHardware : public Resource {
private:
    int warrantyMonths;

public:
    LabHardware(int r_id, string r_name, double r_price, int r_stock, int warranty);
    void display() const override;
};

// 3. Derived Class 2: CafeteriaPerishables
class CafeteriaPerishables : public Resource {
private:
    string expiryDate;

public:
    CafeteriaPerishables(int r_id, string r_name, double r_price, int r_stock, string expiry);
    void display() const override;
};

// 4. Derived Class 3: BookstoreMedia
class BookstoreMedia : public Resource {
private:
    string author;

public:
    BookstoreMedia(int r_id, string r_name, double r_price, int r_stock, string auth);
    void display() const override;
};

#endif // RESOURCE_H