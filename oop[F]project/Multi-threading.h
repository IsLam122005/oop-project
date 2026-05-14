#ifndef MULTI_THREADING_H
#define MULTI_THREADING_H

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include "SystemManager.h"

using namespace std;

inline void runStockMonitor(SystemManager& sys, atomic<bool>& keepRunning) {
    while (keepRunning) {
        this_thread::sleep_for(chrono::seconds(20));

        if (!keepRunning) break;

        cout << "\n[Background Monitor]: Running automated stock check..." << endl;

        auto currentInv = sys.getInventory();
        bool allGood = true;

        for (auto item : currentInv) {
            if (item->getStock() < 5) {
                cout << "!!! LOW STOCK ALERT: " << item->getName()
                    << " (ID: " << item->getId() << ") has only "
                    << item->getStock() << " left!" << endl;
                allGood = false;
            }
        }

        if (allGood) {
            cout << "[Monitor]: All items are sufficiently stocked." << endl;
        }

        cout << "--- End of Check ---\n" << endl;
    }
}

#endif