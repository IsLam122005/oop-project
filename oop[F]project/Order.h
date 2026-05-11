#ifndef ORDER_H
#define ORDER_H

#include "Resource.h"
#include <vector>
#include <vector>

// Order
class Order {
private:
    vector<Resource*> items;
    bool isStaff;
    bool isDelivery;
    const double deliveryFee = 30.0;
    const double staffDiscount = 0.10;

public:
    Order(bool staffStatus, bool deliveryStatus);

    // Core Functions
    void addItem(Resource* res, int quantity);
    double calculateSubtotal() const;
    double calculateTotal() const;
    void processPayment(string method, string cardNumber = "");
    void generateInvoice() const;
};

#endif