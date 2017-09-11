//
// Created by Ji Li on 2017/9/9.
//

#ifndef CRSIM_DEBUG_H
#define CRSIM_DEBUG_H
//
//  debug.h
//  CRsim
//
//  Created by Ji on 14-10-3.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "../global/include.h"

template<class T>
void printArrayFrom0(T x[], const int &n) {
    for (int i = 0; i < n; i++) cout << x[i] << ' ';
    cout << endl;
}

template<class T>
void printArrayFrom1(T x[], const int &n) {
    for (int i = 1; i <= n; i++) cout << x[i] << ' ';
    cout << endl;
}

template<class T>
void printSingle(T x) {
    cout << "#x: " << x << endl;
}

template<class T>
void printVector(vector<T> x) {
    if (x.size() <= 0) {
        cout << "The vector is empty\n";
    }
    for (auto p : x) {
        cout << p << ' ';
    }
    cout << endl;
}

#endif //CRSIM_DEBUG_H
