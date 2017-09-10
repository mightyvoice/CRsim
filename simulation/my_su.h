//
// Created by Ji Li on 2017/9/10.
//

#ifndef CRSIM_MY_SU_H
#define CRSIM_MY_SU_H
//
//  my_su.h
//  CRsim
//
//  Created by Ji on 14-10-7.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "../lib/lib.h"
#include "../user/su.h"
#include "../chan_hop/all_chan_hop.h"

class MySU: public SU{
private:
    void binaryRepresent(int n, int ans[]);
public:
    int curState;
    int usedChanNum;
    int notUsedCrNum;
    int allChannelNum;
    vI usedChan;
    vI stillAvaiChan;
    vI newAllocChan;
    vI newAllocChanRandom;
    int sendOrReceiveAlloc[global::CR_NUM+2];
    vector<vI> avaiChanOnSs;

    vector<int> allChannelToHop;

    ////////////////////////////////////////////Infocom16///////////////////////////////////////
    string transSeq;
    vI chanHopSeq;
    int transSeqLen;
    int seqLen;
    int curRendIndex;
    int curTransSeqIndex;
    int countInRound;
    int rendTime;
    vI allStartIndexes;
    ////////////////////////////////////////////Infocom16///////////////////////////////////////

    MySU();
    void getMyHopSeq();
    void getMySendRevHopSeq();
    void getTransSeq();
    void initAllStartIndexes();

};

#endif //CRSIM_MY_SU_H
