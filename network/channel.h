//
// Created by Ji Li on 2017/9/10.
//

#ifndef CRSIM_CHANNEL_H
#define CRSIM_CHANNEL_H
//
//  channel.h
//  CRsim
//
//  Created by Ji on 15/2/25.
//  Copyright (c) 2015年 lj. All rights reserved.
//

#include "../lib/lib.h"

class CRchannel{
public:
    int ID;
    int curConAvaiTime;
    bool ifAvai;
    bool ifAvaiPreTime;
    vector<int> allConAvaiTime;
    double averageConAvaiTime;

    void printSortedAllConAvaiTime();
    double getAverConAvaiTime();
};

extern bool cmpID(const CRchannel &x, const CRchannel &y);

extern bool cmpConAvaiTime(const CRchannel &x, const CRchannel &y);

extern bool cmpConAvaiTimeReverse(const CRchannel &x, const CRchannel &y);

#endif //CRSIM_CHANNEL_H
