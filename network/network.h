//
// Created by Ji Li on 2017/9/10.
//

#ifndef CRSIM_NETWORK_H
#define CRSIM_NETWORK_H
//
//  network.h
//  CRsim
//
//  Created by Ji on 14-10-6.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "../lib/lib.h"
#include "../simulation/my_su.h"
#include "../user/pu.h"

class CRNetwork{
public:
    CRNetwork();
    virtual void initAllSU() = 0;
    virtual void initSimulation() = 0;
    virtual void startSimulation() = 0;

protected:
    int totalChanNum; //total number of channels;
    double simTime;
    double timeslotLength;
    int simTimeSlot;
    int suNum;
    int puNum;
    int chanAllocToPuCount[global::TOTAL_CHAN_NUM*2+5];
    int avaiChanNumForPU;
    int chanAvaiCountSu0[global::TOTAL_CHAN_NUM*2+5];
    int chanComAvaiCountSu0Su1[global::TOTAL_CHAN_NUM*2+5];

    bool rendSuc[22];
    double totalAnswer[22];
    int START_REND_TIME;

    vector<MySU> allSU;
    vector<PU> allPU;

    void initAllPU();
    void initAllPuTrafficEachTime();
    void initSuNeighborPU(MySU &su);
    int allocChanRandomToPU();
    int allocChanUnUsedToPU();
    void puReturnAllocChan(int _chan_id);

    void getSUsCurAvaiChan(int t);
    void getCurConAvaiChan();
    void getCommonAvaiRatio();
    void getCurAllChanConAvaiTime();

    double calAverConAvaiTime();
    double calConAvaiChanAverConAvaiTime();

};

#endif //CRSIM_NETWORK_H
