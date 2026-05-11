#include "SystemManager.h"
#include <iostream>
#include <fstream> // Important for File I/O

using namespace std;

// Constructor
SystemManager::SystemManager() {
    // Automatically load data when the system starts
    loadData();
}

// Destructor
SystemManager::~SystemManager() {
    // Automatically save data and clean up memory when the system closes
    saveData();

    // Free the memory to prevent memory leaks
    for (auto res : inventory) {
        delete res;
    }
}

void SystemManager::addResource(Resource* res) {
    inventory.push_back(res);
    cout << res->getName() << " added to system." << endl;
}

Resource* SystemManager::findResource(int id) {
    for (auto res : inventory) {
        if (res->getId() == id) {
            return res; // Found it
        }
    }
    return nullptr; // Not found
}

void SystemManager::displayInventory() const {
    cout << "\n=== Smart Campus Inventory ===" << endl;
    for (const auto& res : inventory) {
        res->display();
    }
    cout << "==============================\n" << endl;
}

// Read from File
void SystemManager::loadData() {
    ifstream inFile(filename); // Open file for reading
    if (!inFile) {
        cout << "Notice: No existing inventory file found. Starting fresh." << endl;
        return;
    }

    int id, stock;
    string name;
    double price;

    // Simple loading loop
    while (inFile >> id >> name >> price >> stock) {
        inventory.push_back(new Resource(id, name, price, stock));
    }
    inFile.close();
    cout << "Success: Data loaded from file!" << endl;
}

// Write to File
void SystemManager::saveData() const {
    ofstream outFile(filename); // Open file for writing
    if (!outFile) {
        cout << "Error: Could not save data!" << endl;
        return;
    }

    // Write each resource on a new line
    for (const auto& res : inventory) {
        outFile << res->getId() << " "
            << res->getName() << " "
            << res->getPrice() << " "
            << res->getStock() << endl;
    }
    outFile.close();
    cout << "Success: Data saved safely to " << filename << endl;
}