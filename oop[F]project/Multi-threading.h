#pragma once
#ifndef MULTI_THREADING_H
#define MULTI_THREADING_H

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include "SystemManager.h"

using namespace std;

// استخدمنا inline عشان نقدر نكتب الـ implementation جوه الـ Header من غير ما الكومبايلر يزعل
inline void runStockMonitor(SystemManager& sys, atomic<bool>& keepRunning) {
    while (keepRunning) {
        // المراقب بينام 15 ثانية عشان ميهلكش الجهاز
        this_thread::sleep_for(chrono::seconds(15));

        // لو اليوزر اختار Exit، المراقب بيقف فوراً
        if (!keepRunning) break;

        cout << "\n[Monitor]: Checking inventory health in background..." << endl;

        // هنا بيطبع رسالة بس.. لو حابب تخليه يلف على المخزن ويطلع تحذير حقيقي تقدر تكتب اللوجيك هنا
    }
}

#endif