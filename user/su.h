//
// Created by Ji Li on 2017/9/10.
//

#ifndef CRSIM_SU_H
#define CRSIM_SU_H
//
//  su.h
//  CRsim
//
//  Created by Ji on 14-10-6.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "../lib/lib.h"
#include "user.h"
#include "cognitive_radio.h"

class SU: public User{
public:
    vector<CognitiveRadio> allCR;
    vI channelToSense;
    int chanAvaiTimeCount[global::TOTAL_CHAN_NUM+5];
    int chanAvaiTimeTotal[global::TOTAL_CHAN_NUM+5];
    int chanCurTotalAvaiTime[global::TOTAL_CHAN_NUM+5];
    int chanAvaiRoundCount[global::TOTAL_CHAN_NUM+5];
    int chanUsedTimeCount[global::TOTAL_CHAN_NUM+5];
    int allChanConAvaiTime[global::TOTAL_CHAN_NUM+2];
    int lastStayChan;
    int alreadyStayTime;

    vI getAvaiChanRandom(int _chan_n);
    vI getAvaiChanRandom();


    SU();
    void getNeighRandom();
    void initAllCognitiveRadio(int n);
};

#endif //CRSIM_SU_H
