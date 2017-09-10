//
//  April0426.cpp
//  CRsim
//
//  Created by Ji on 15/4/27.
//  Copyright (c) 2015年 lj. All rights reserved.
//

/* Compare the original enhanced js with the one considering send or receive RTS packets
 * Use the virtual channel to represent sending or receiving RTS packets. For channel i <= M, if it is
 * available, if a SU hops to it, it should send RTS packets, if a SU hops to i+M, it should not send
 * RTS packets.
 */
#include "Infocom2016.h"

Infocom2016:: Infocom2016(): CRNetwork()
{
    totalChanNum = global::TOTAL_CHAN_NUM;
    suNum = 4;
    initAllSU();
}

void Infocom2016:: initAllSU()
{
    allSU.clear();
    for(int i = 0; i < suNum; i++){
        MySU tmp;
        if(i > 1) tmp.getMySendRevHopSeq();
//        cout<<tmp.transSeq<<endl;
//        printVector(tmp.chanHopSeq);

        if(i < 2) tmp.location = make_pair(global::SIDE_LENGTH*(i+1) / 3.0, global::SIDE_LENGTH*(i+1)/3.0);
        else tmp.location = make_pair(global::SIDE_LENGTH*(i-1) / 3.0, global::SIDE_LENGTH*(i-1)/3.0);

        tmp.curSysTimeSlot = CRmath::randIntDiff(1, 10000000);
        if(i > 1) tmp.curSysTimeSlot = allSU[i-2].curSysTimeSlot;

//        if(i < 2) tmp.totalAccessChan = totalChanNum;
//        else tmp.totalAccessChan = totalChanNum*2;

//        tmp.chanHop = new EnJsHop(tmp.totalAccessChan);

        initSuNeighborPU(tmp);
        for(int j = 1; j <= global::TOTAL_CHAN_NUM; j++){
            tmp.allChanObj[j].ID = j;
            tmp.allChanObj[j].ifAvai = 0;
            tmp.allChanObj[j].curConAvaiTime = 0;
        }

        allSU.push_back(tmp);
    }
}

int rts0, rts1;

double calCost(int _rendTime, int _RTScount)
{
    return _RTScount*1.0 * _rendTime;
}

void Infocom2016:: enJsRend(int t)
{
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    int c0 = su0.chanHop->getChanAtTimeT(su0.curSysTimeSlot + t, su0.avaiChan);
    int c1 = su1.chanHop->getChanAtTimeT(su1.curSysTimeSlot + t, su1.avaiChan);
    su0.curStayChan = c0;
    su1.curStayChan = c1;
    if(!rendSuc[0]){
        RTScount[0] += 2;
    }
    if(c0 == c1 && !rendSuc[0]){
        rendSuc[0] = 1;
        totalAnswer[0] += t-START_REND_TIME;
        rendTimeRound[0] = t - START_REND_TIME;
        cout<<"JS: "<< t- START_REND_TIME<<endl;
    }
}

void updateAvaiChan(vI &_avaiChan, int _totalChan)
{
    int n = (int)_avaiChan.size();
    for(int i = 0; i < n; i++){
        _avaiChan.push_back(_avaiChan[i]+_totalChan);
    }
}

void Infocom2016:: sendOrNotRend(int t)
{
    SU &su0 = allSU[2];
    SU &su1 = allSU[3];
    updateAvaiChan(su0.avaiChan, totalChanNum);
    updateAvaiChan(su1.avaiChan, totalChanNum);
    int c0 = su0.chanHop->getChanAtTimeT(su0.curSysTimeSlot + t, su0.avaiChan);
    int c1 = su1.chanHop->getChanAtTimeT(su1.curSysTimeSlot + t, su1.avaiChan);
    su0.curStayChan = c0;
    su1.curStayChan = c1;
    if(c0 <= totalChanNum){
        RTScount[1]++;
        RTSroundcount1++;
        rts1++;
    }
    else{
        rts0++;
    }
    if(c1 <= totalChanNum){
        RTScount[1]++;
        RTSroundcount1++;
        rts1++;
    }
    else{
        rts0++;
    }
    if( (c0 == c1 && c0 <= totalChanNum) || abs(c0-c1) == totalChanNum){
        rendSuc[1] = 1;
        totalAnswer[1] += calCost(t-START_REND_TIME, RTSroundcount1);
//        cout<<"JS send or rev: "<< (t - START_REND_TIME) * RTSroundcount1<<' '<<(t - START_REND_TIME)<<' '<<RTSroundcount1<<endl;
//        cout<<c0<<' '<<c1<<endl;

    }
}

void Infocom2016:: randomSendOrNotRend(int t)
{
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    int c1, c0;
    c0 = su0.curStayChan;
    c1 = su1.curStayChan;
    int t0 = CRmath::randIntDiff(0, 1);
    int t1 = CRmath::randIntDiff(0, 1);
    if(t0){
        RTScount[1]++;
    }
    if(t1){
        RTScount[1]++;
    }
    if( c0 == c1 && (t0 || t1)){
        rendSuc[1] = 1;
        totalAnswer[1] += t-START_REND_TIME;
//        cout<<"JS random: "<< t- START_REND_TIME<<endl;
        //        cout<<c0<<' '<<c1<<endl;
    }
}

void Infocom2016:: energySavingSameSeq(int t)
{
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    int c1, c0;
    c0 = su0.curStayChan;
    c1 = su1.curStayChan;
    int t0 = sendRevStr1[bStrStartPos0] - '0';
    int t1 = sendRevStr2[bStrStartPos1] - '0';
    timeCount2++;
    if(t0){
        RTScount[2]++;
    }
    if(t1){
        RTScount[2]++;
    }
    if( c0 == c1 && (t0 || t1)){
        rendSuc[2] = 1;
        totalAnswer[2] += t-START_REND_TIME;
        cout<<"JS save energy: "<< t- START_REND_TIME<<endl;
        rendTimeRound[2] = t - START_REND_TIME;
        //        cout<<c0<<' '<<c1<<endl;
    }
    bStrStartPos0++; if(bStrStartPos0 == SEND_REV_STR_LEN) bStrStartPos0 = 0;
    bStrStartPos1++; if(bStrStartPos1 == SEND_REV_STR_LEN) bStrStartPos1 = 0;
}

void Infocom2016:: energySavingSameSeqImprove(int t)
{
    SU &su0 = allSU[2];
    SU &su1 = allSU[3];
    int c1, c0;
    c0 = su0.chanHop->getChanAtTimeT(su0.curSysTimeSlot + t, su0.avaiChan);
    c1 = su1.chanHop->getChanAtTimeT(su1.curSysTimeSlot + t, su1.avaiChan);
    int t0 = sendRevStr1[bStrStartPos0] - '0';
    int t1 = sendRevStr2[bStrStartPos1] - '0';
    timeCount2++;
    if(t0){
        RTScount[2]++;
    }
    if(t1){
        RTScount[2]++;
    }
    if( c0 == c1 && (t0 || t1)){
        rendSuc2 = 1;
        totalAnswer[2] += t-START_REND_TIME;
        cout<<"JS save energy: "<< t- START_REND_TIME<<endl;
        rendTimeRound[2] = t - START_REND_TIME;
        //        cout<<c0<<' '<<c1<<endl;
    }
    if(!rendSuc2 && timeCount2 >= MTTR_TO_INIT){
        su0.chanHop->resetChanHop();
        su1.chanHop->resetChanHop();
        timeCount2 = 0;
    }
    bStrStartPos0++; if(bStrStartPos0 == SEND_REV_STR_LEN) bStrStartPos0 = 0;
    bStrStartPos1++; if(bStrStartPos1 == SEND_REV_STR_LEN) bStrStartPos1 = 0;
}

void Infocom2016:: energySavingRandomSend(int t)
{
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    int c1, c0;
    c0 = su0.curStayChan;
    c1 = su1.curStayChan;
    int t0 = CRmath:: get1or0BasedOnPro(RTS_RATIO_SU0);
    int t1 = CRmath:: get1or0BasedOnPro(RTS_RATIO_SU0);
    timeCount2++;
    if(t0){
        RTScount[3]++;
    }
    if(t1){
        RTScount[3]++;
    }
    if( c0 == c1 && (t0 || t1)){
        rendSuc[3] = 1;
        totalAnswer[3] += t-START_REND_TIME;
        cout<<"Save energy random send: "<< t- START_REND_TIME<<endl;
        rendTimeRound[3] = t - START_REND_TIME;
        //        cout<<c0<<' '<<c1<<endl;
    }
}

void Infocom2016:: initSendOrRevString()
{
//    VALID_NUM = (int)(SEND_REV_STR_LEN * VALID_RATIO);
//    int RTSn = SendSeq:: getMiniRTSNum(SEND_REV_STR_LEN, VALID_NUM);
//    sendRevStr = CRmath:: randBinaryStrWithOnes(SEND_REV_STR_LEN, RTSn);
//    VALID_NUM2 = (int)(SEND_REV_STR_LEN * VALID_RATIO);
//    int RTSn2 = SendSeq:: getMiniRTSNum(SEND_REV_STR_LEN, VALID_NUM2);
//    sendRevStr2 = CRmath:: randBinaryStrWithOnes(SEND_REV_STR_LEN, RTSn2);
//    sendRevStr = "01110111010110101111";
//    sendRevStr = "1101101101";
}

void Infocom2016:: SendRevSeqRend(int t)
{
    MySU &su0 = allSU[2];
    MySU &su1 = allSU[3];
    int c0 = su0.chanHopSeq[su0.curRendIndex];
    int c1 = su1.chanHopSeq[su1.curRendIndex];
    if(abs(c0-c1) == global::TOTAL_CHAN_NUM && vectorSortedFind(su0.avaiChan, min(c0,c1)) != -1 && vectorSortedFind(su1.avaiChan, min(c0,c1)) != -1){
        rendSuc[1] = 1;
        totalAnswer[1] += t - START_REND_TIME;
        su0.rendTime = su1.rendTime = t - START_REND_TIME;
        cout<<"enhance time: "<<t-START_REND_TIME<<endl;
    }
    for(int i = 2; i < 4; i++){
        MySU &su = allSU[i];
        su.curRendIndex++;
        su.countInRound++;
        if( su.countInRound >= su.chanHopSeq.size()){
            su.curRendIndex = CRmath:: randIntDiff(1, su.seqLen);
            su.countInRound = 0;
        }
        if(su.curRendIndex > su.chanHopSeq.size()){
            su.curRendIndex -= su.seqLen;
        }
    }

}

void Infocom2016:: mySeqAndTransSeqRend(int t)
{
    MySU &su0 = allSU[0];
    MySU &su1 = allSU[1];
    int c0 = su0.chanHopSeq[su0.curRendIndex];
    int c1 = su1.chanHopSeq[su1.curRendIndex];
    if(c1 == c0 && vectorSortedFind(su0.avaiChan, c0) != -1 && vectorSortedFind(su1.avaiChan, c1) != -1){
        int t0 = su0.transSeq[su0.curTransSeqIndex] -'0';
        int t1 = su1.transSeq[su1.curTransSeqIndex] -'0';
        if(t0 ^ t1){
            rendSuc[0] = 1;
            totalAnswer[0] += t - START_REND_TIME;
            su0.rendTime = su1.rendTime = t - START_REND_TIME;
            cout<<"simple time: "<<t-START_REND_TIME<<endl;
        }
    }
    for(int i = 0; i < 2; i++){
        MySU &su = allSU[i];
        su.curTransSeqIndex++;
        if( su.curTransSeqIndex >= su.transSeqLen){
            su.curTransSeqIndex = 0;
        }
        su.curRendIndex++;
        su.countInRound++;
        if( su.countInRound >= su.chanHopSeq.size()){
            su.curRendIndex += 2;
            su.countInRound = 0;
        }
        if(su.curRendIndex > su.chanHopSeq.size()){
            su.curRendIndex -= su.chanHopSeq.size();
        }
    }
}

void Infocom2016:: pureRandomRend(int t)
{
    MySU &su0 = allSU[0];
    MySU &su1 = allSU[1];
    int c0 = CRmath:: randIntDiff(1, global::TOTAL_CHAN_NUM);
    int c1 = CRmath:: randIntDiff(1, global::TOTAL_CHAN_NUM);
    int t0 = CRmath:: randIntDiff(0, 1);
    int t1 = CRmath:: randIntDiff(0, 1);
    if(c1 == c0 && (t1 ^ t0) == 1 && vectorSortedFind(su0.avaiChan, c0) != -1 && vectorSortedFind(su1.avaiChan, c1) != -1){
        rendSuc[2] = 1;
        totalAnswer[2] += t - START_REND_TIME;
        cout<<"random time: "<<t-START_REND_TIME<<endl;
    }
}

void Infocom2016:: initSimulation()
{
    memset(rendSuc, 0, sizeof(rendSuc));

    RTSroundcount0 = RTSroundcount1 = RTSroundcount2 = 0;
    rts0 = rts1 = 0;
#ifdef SAME_NET_PARAMETERS_EACH_SIM
    START_REND_TIME = CRmath::randInt(global::TOTAL_TIME_SLOT/5, global::TOTAL_TIME_SLOT/2);
#endif
#ifdef DIFF_NET_PARAMETERS_EACH_SIM
    START_REND_TIME = CRmath::randIntDiff(TOTAL_TIME_SLOT/5, TOTAL_TIME_SLOT/2);
#endif

    memset(rendTimeRound, 0, sizeof(rendTimeRound));

    for(int i = 0; i < suNum; i++){
        MySU &su = allSU[i];
        su.curRendIndex = CRmath:: randIntDiff(1, su.seqLen);
        su.curTransSeqIndex = CRmath:: randIntDiff(0, su.transSeqLen-1);
        su.countInRound = 0;
        su.initAllStartIndexes();
        for(int j = 1; j <= su.totalAccessChan; j++){
            su.allChanObj[j].ifAvai = 0;
            su.allChanObj[j].curConAvaiTime = 0;
        }
    }
}

void Infocom2016:: startSimulation()
{
    memset(RTScount, 0, sizeof(RTScount));
    memset(totalAnswer, 0, sizeof(totalAnswer));
    memset(rendSucCount, 0, sizeof(rendSucCount));
    initSendOrRevString();
    shiftIncrement = 0;
    bStrStartPos0 = 0;
    memset(rendTimeEqualCount, 0, sizeof(rendTimeEqualCount));
    for(int i = 0; i < global::SIMULATION_REPEAT_TIME; i++){
        cout<<i<<endl;
        initSimulation();
        for(int t = 0; t < global::TOTAL_TIME_SLOT; t++){
            if(rendSuc[0] && rendSuc[1] ){
                if(allSU[0].rendTime <= 4 * global::TOTAL_CHAN_NUM){
                    rendSucCount[0]++;
                }
                if(allSU[2].rendTime <= 4 * global::TOTAL_CHAN_NUM){
                    rendSucCount[1]++;
                }
                break;
            }
//            getSUsCurAvaiChan(t);
            if(t > START_REND_TIME){
                getSUsCurAvaiChan(t);
                if(!rendSuc[0]) mySeqAndTransSeqRend(t);
                if(!rendSuc[1]) SendRevSeqRend(t);
            }
        }
    }
    cout<<endl;
    cout<<"simple time: "<<totalAnswer[0]/global::SIMULATION_REPEAT_TIME<<endl;
    cout<<"enhance time: "<<totalAnswer[1]/global::SIMULATION_REPEAT_TIME<<endl;
    cout<<"simple ratio: "<<rendSucCount[0]*1.0/global::SIMULATION_REPEAT_TIME*100<<endl;
    cout<<"enhance ratio: "<<rendSucCount[1]*1.0/global::SIMULATION_REPEAT_TIME*100<<endl;
}
