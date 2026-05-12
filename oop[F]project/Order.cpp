#include "Order.h"
#include <iostream>
#include <stdexcept>
#include <cctype>

using namespace std;

Order::Order(bool staffStatus, bool deliveryStatus) {
    isStaff = staffStatus;
    isDelivery = deliveryStatus;
}

void Order::addItem(Resource* res, int quantity) {
    // We check if the purchase is valid first (stock check)
    if (res->purchase(quantity)) {
        for (int i = 0; i < quantity; i++) {
            items.push_back(res);
        }
        cout << "Success: " << quantity << "x " << res->getName() << " added to order." << endl;
    }
}

double Order::calculateSubtotal() const {
    double subtotal = 0.0;
    for (const auto& item : items) {
        subtotal += item->getPrice();
    }
    return subtotal;
}

double Order::calculateTotal() const {
    double total = calculateSubtotal();

    // Applying staff discount to the subtotal
    if (isStaff) {
        total -= (total * staffDiscount);
    }

    // Adding delivery surcharge
    if (isDelivery) {
        total += deliveryFee;
    }

    return total;
}

bool Order::processPayment(string method, string cardNumber) {
    if (method == "Cash") {
        cout << "Payment successful via Cash." << endl;
        return true; // الدفع نجح
    }

    if (method == "Card") {
        try {
            // Check for exact 16 digits length
            if (cardNumber.length() != 16) {
                throw invalid_argument("Card number must be exactly 16 digits.");
            }

            // Check if all characters are numeric
            for (char c : cardNumber) {
                if (!isdigit(c)) {
                    throw invalid_argument("Card number must contain only numeric digits.");
                }
            }

            cout << "Payment successful via Card." << endl;
            return true; // الدفع نجح

        }
        catch (const exception& e) {
            cout << "Exception Caught: " << e.what() << endl;
            cout << "Transaction Failed!" << endl;
            return false; // الدفع فشل
        }
    }
    return false;
}

void Order::generateInvoice() const {
    cout << "\n=== Order Invoice ===" << endl;
    for (const auto& item : items) {
        cout << "- " << item->getName() << " : $" << item->getPrice() << endl;
    }

    double subtotal = calculateSubtotal();
    cout << "Subtotal: $" << subtotal << endl;

    if (isStaff) {
        cout << "Staff Discount (10%): -$" << (subtotal * staffDiscount) << endl;
    }

    if (isDelivery) {
        cout << "Delivery Surcharge: +$" << deliveryFee << endl;
    }

    cout << "Total to Pay: $" << calculateTotal() << endl;
    cout << "=====================\n" << endl;
}