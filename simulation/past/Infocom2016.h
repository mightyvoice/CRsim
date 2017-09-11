//
// Created by Ji Li on 2017/9/10.
//

#ifndef CRSIM_ENERGY_SAVE_REND_H
#define CRSIM_ENERGY_SAVE_REND_H
//
//  April0426.h
//  CRsim
//
//  Created by Ji on 15/4/27.
//  Copyright (c) 2015年 lj. All rights reserved.
// The basic algorithm to reduce the number of sent RTSs.

#include "../../chan_hop/all_chan_hop.h"
#include "../../network/network.h"

class Infocom2016 : public CRNetwork {
public:
    Infocom2016();

    void initAllSU();

    void initSimulation();

    void startSimulation();

private:
    const int SEND_REV_STR_LEN = 20;
    const double VALID_RATIO = 0.9;
    const double RTS_RATIO_SU0 = 0.3;
    const double RTS_RATIO_SU1 = 0.3;
    int VALID_NUM;
    int VALID_NUM2;
    const int MTTR_TO_INIT = 30;
    string sendRevStr1;
    string sendRevStr2;
    string pastStr0;
    string pastStr2;
    int rendTimeRound[22];
    int timeCount2;
    int rendTimeEqualCount[22];
    int bStrStartPos0;
    int bStrStartPos1;
    int RTScount[22];
    int RTSroundcount0;
    int RTSroundcount1;
    int RTSroundcount2;
    bool rendSuc2;
    int shiftIncrement;

    void enJsRend(int t);

    void sendOrNotRend(int t);

    void randomSendOrNotRend(int t);

    void energySavingSameSeq(int t);

    void energySavingSameSeqImprove(int t);

    void initSendOrRevString();

    void energySavingRandomSend(int t);

    ////////////////////////////////////////////Infocom16///////////////////////////////////////
    int rendSucCount[20];

    void mySeqAndTransSeqRend(int t);

    void SendRevSeqRend(int t);

    void pureRandomRend(int t);
    ////////////////////////////////////////////Infocom16///////////////////////////////////////

};

#endif //CRSIM_ENERGY_SAVE_REND_H
