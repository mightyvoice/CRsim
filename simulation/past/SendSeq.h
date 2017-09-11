//
// Created by Ji Li on 2017/9/10.
//

#ifndef CRSIM_SENDSEQ_H
#define CRSIM_SENDSEQ_H
//
//  June061015.h
//  CRsim
//
//  Created by Ji on 15/6/10.
//  Copyright (c) 2015年 lj. All rights reserved.
//

#include "../../lib/lib.h"

class SendSeq {
public:
    static const int MaxTotalLength = 60;
    static const int MaxSegLength = 30;

    static void processbitNum(int x);

    static int getValidNumStr(const string &s, int shift);

    static int getRtsNumStr(const string &s, int shift);

    static int getAverageValidNumStr(const string &s);

    static int getAverageRtsNumStr(const string &s);

    static int getAverageValidNum(int len, int n);

    static int getAllRtsNum(int len, int n);

    static void getAllRtsNumMaxLength(int len, int n);

    static void getAllEfficiency(double _ratio);

    static void getAllRendNumBasedOnRatio(double _ratio, int segLen);

    static void getAllRendNumBasedOnNum(int segLen, int _RTS);

    static double getMiniRTSNum(int _totalLen, int _rend);
};

#endif //CRSIM_SENDSEQ_H
