#include <iostream>
#include <string>
#include "SystemManager.h"
#include "User.h"
#include "Order.h"
#include "Resource.h"
#include "Multi-threading.h" 

using namespace std;

int main() {
    SystemManager sys;

   
    
    // ==========================================

    cout << "=======================================" << endl;
    cout << "   Welcome to Smart Campus Ecosystem   " << endl;
    cout << "=======================================\n" << endl;

    // --- 1. User Identity Setup ---
    int userType;
    cout << "Are you a:\n1. Staff Member (10% Discount)\n2. Student\nChoice: ";
    cin >> userType;
    bool isStaff = (userType == 1);

    // --- 2. Delivery Setup ---
    int deliveryType;
    cout << "\nChoose Delivery Method:\n1. Dorm Delivery (+30 EGP Surcharge)\n2. Campus Pickup (Free)\nChoice: ";
    cin >> deliveryType;
    bool isDelivery = (deliveryType == 1);

    // Create the Order based on user choices
   // ...  اختيار نوع اليوزر والدليفري ...

    Order currentOrder(isStaff, isDelivery);

    // ---Multi-threading---
    atomic<bool> keepRunning(true);
    thread monitorThread(runStockMonitor, ref(sys), ref(keepRunning));
    monitorThread.detach(); 
    // ---------------------------

    int choice = 0;
    while (choice != 5) {
        //  إظهار المخزن المحدث في كل لفة
        sys.displayInventory();

        cout << "--- Main Menu ---" << endl;
        cout << "1. Refresh Inventory View" << endl;
        cout << "2. Add Item to Cart (Select by ID)" << endl;
        cout << "3. Compare Two Items (Cost Logic Test)" << endl;
        cout << "4. Checkout & Pay" << endl;
        cout << "5. Exit System" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Inventory Refreshed." << endl;
            break;

        case 2: {
            int id, qty;
            cout << "Looking at the list above, enter Resource ID: ";
            cin >> id;
            Resource* item = sys.findResource(id);

            if (item) {
                cout << "Enter Quantity: ";
                cin >> qty;
                currentOrder.addItem(item, qty); // This checks stock automatically
            }
            else {
                cout << "Error: ID [" << id << "] not found!" << endl;
            }
            break;
        }

        case 3: {
            int id1, id2;
            cout << "Enter First Resource ID: ";
            cin >> id1;
            cout << "Enter Second Resource ID: ";
            cin >> id2;

            Resource* r1 = sys.findResource(id1);
            Resource* r2 = sys.findResource(id2);

            if (r1 && r2) {
                if (*r1 > *r2) {
                    cout << "\nResult: " << r1->getName() << " is more expensive than " << r2->getName() << endl;
                }
                else {
                    cout << "\nResult: " << r2->getName() << " is more expensive or equal to " << r1->getName() << endl;
                }
            }
            else {
                cout << "Error: One or both IDs not found!" << endl;
            }
            break;
        }

        case 4: {
            int payChoice;
            cout << "\n1. Pay with Cash\n2. Pay with Card (16 Digits)\nChoice: ";
            cin >> payChoice;

            if (payChoice == 1) {
                currentOrder.processPayment("Cash");
            }
            else if (payChoice == 2) {
                string cardNum;
                cout << "Enter 16-Digit Card Number: ";
                cin >> cardNum;
                currentOrder.processPayment("Card", cardNum);
            }

            currentOrder.generateInvoice();
            cout << "\nThank you for your order! Closing cart..." << endl;
            choice = 5;
            break;
        }

        case 5:
            cout << "Exiting... Saving data..." << endl;
            keepRunning = false; 
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}