#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include "Resource.h"
#include <vector>
#include <string>

using namespace std;

class SystemManager {
private:
    vector<Resource*> inventory; // List of all resources
    string filename = "inventory.txt"; // File to save data

public:
    SystemManager();
    ~SystemManager();

    // Core Functions
    void addResource(Resource* res);
    Resource* findResource(int id);
    void displayInventory() const;

    // File I/O (Persistence)
    void loadData();
    void saveData() const;
};

#endif
#pragma once
