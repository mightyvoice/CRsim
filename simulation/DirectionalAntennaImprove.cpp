//
//  Globecom15.cpp
//  CRsim
//
//  Created by Ji on 15/4/28.
//  Copyright (c) 2015年 lj. All rights reserved.
//

#include "DirectionalAntennaImprove.h"

static int total0 = 0;
static int rend_count0 = 0;
static int total1 = 0;
static int rend_count1 = 0;
static int total2 = 0;
static int rend_count2 = 0;

DirectionalAntennaImprove::DirectionalAntennaImprove() : CRNetwork() {
    initAllSU();
}

void DirectionalAntennaImprove::initAllSU() {
    for (int i = 0; i < 2; i++) {
        MySU tmp;
        tmp.location = make_pair(global::SIDE_LENGTH * (i + 1) / 3.0, global::SIDE_LENGTH * (i + 1) / 3.0);
        tmp.curSysTimeSlot = CRmath::randInt(1, 10000000);
        tmp.ID = i;
        global::SEND_OR_RECEIVE sendOrRev = global::SEND;
        if (i == 0) {
            tmp.transSectorNum = global::SEND_SECTOR_NUM;
            sendOrRev = global::SEND;
        } else {
            tmp.transSectorNum = global::REV_SECTOR_NUM;
            sendOrRev = global::RECEIVE;
        }
        tmp.curSectorID = -1;
        tmp.secHop = new SectorHop(tmp.transSectorNum, sendOrRev);
        tmp.chanHop = new EnJsHop();
        initSuNeighborSector(tmp);
        allSU.push_back(tmp);
    }
    getRendPair(allSU[0], allSU[1]);
    // second pair
    allSU.push_back(allSU[0]);
    allSU.push_back(allSU[1]);
    // third pair
    allSU.push_back(allSU[0]);
    allSU.push_back(allSU[1]);

    // randomly init all the channels for the scheme with selected channels
    for (int i = 4; i < 6; i++) {
        MySU &su = allSU[i];
        su.allChannelNum = (int) (global::TOTAL_CHAN_NUM * this->SELECT_CHANNEL_RATIO);
        su.chanHop = new EnJsHop(su.allChannelNum);
//        su.allChannelToHop = initSelectedChanFromRange(1, su.allChannelNum);
        su.allChannelToHop = initSelectedChanRandomly(su.allChannelNum);
        sort(su.allChannelToHop.begin(), su.allChannelToHop.end());
    }
}

vI DirectionalAntennaImprove::initSelectedChanFromRange(const int &st, const int &ed) {
    assert(st <= ed);
    vector<int> res;
    for (int i = st; i <= ed; i++) res.push_back(i);
    return res;
}

vI DirectionalAntennaImprove::initSelectedChanRandomly(const int &num) {
    return CRmath::generateDiffRandIntDiffSeed(num, 1, global::TOTAL_CHAN_NUM);
}

void DirectionalAntennaImprove::initSuNeighborSector(MySU &su) {
    su.initSectorSplit();
    memset(su.sectorNeighborPU, 0, sizeof(su.sectorNeighborPU));
    for (int i = 0; i < su.transSectorNum; i++) {
        for (int j = 0; j < global::PU_NUM; j++) {
            if (CRmath::twoPointsDistanceSquare(su.location.first, su.location.second, allPU[j].location.first,
                                                allPU[j].location.second) <=
                global::SENSE_RANGE_SU * global::SENSE_RANGE_SU &&
                CRmath::pointInsideAngle(su.location, su.sectorSplit[i], su.sectorSplit[i + 1], allPU[j].location)) {
                su.sectorNeighborPU[i][++su.sectorNeighborPU[i][0]] = j;
            }
        }
    }
}

void DirectionalAntennaImprove::getRendPair(const MySU &su0, const MySU &su1) {
    int n0 = su0.transSectorNum, n1 = su1.transSectorNum;
    int ans1 = -1, ans2 = -1;
    for (int i = 0; i < n0; i++) {
        if (CRmath::pointInsideAngle(su0.location, su0.sectorSplit[i], su0.sectorSplit[i + 1], su1.location)) {
            ans1 = i;
            break;
        }
    }
    for (int i = 0; i < n1; i++) {
        if (CRmath::pointInsideAngle(su1.location, su1.sectorSplit[i], su1.sectorSplit[i + 1], su0.location)) {
            ans2 = i;
            break;
        }
    }
    this->rendPair = {ans1, ans2};
}

void DirectionalAntennaImprove::getAvaiChanEachSector(MySU &su, int t, int _sector) {
    su.avaiChan.clear();
    bool not_avai[global::TOTAL_CHAN_NUM + 5] = {0};
    for (int i = 1; i <= global::TOTAL_CHAN_NUM; i++) {
        int n = su.sectorNeighborPU[_sector][0];
        for (int k = 1; k <= n; k++) {
            int p = su.sectorNeighborPU[_sector][k];
            int c = allPU[p].chanOfEachTimeSlot[t];
            if (c > 0 && c <= global::TOTAL_CHAN_NUM) {
                not_avai[c] = true;
            }
        }
    }
    for (int i = 1; i <= global::TOTAL_CHAN_NUM; i++) {
        if (!not_avai[i]) {
            su.avaiChan.push_back(i);
        }
    }
    std::sort(su.avaiChan.begin(), su.avaiChan.end());
}

void DirectionalAntennaImprove::getAvaiChanEachSectorSeletcedChannelSU(MySU &su, int t, int _sector) {
    su.avaiChan.clear();
    bool avai[global::TOTAL_CHAN_NUM + 5] = {0};
    for (auto channel: su.allChannelToHop) {
        avai[channel] = true;
    }
    for (int i = 1; i <= global::TOTAL_CHAN_NUM; i++) {
        int n = su.sectorNeighborPU[_sector][0];
        for (int k = 1; k <= n; k++) {
            int p = su.sectorNeighborPU[_sector][k];
            int c = allPU[p].chanOfEachTimeSlot[t];
            if (vectorSortedFind(su.allChannelToHop, c) != -1) {
                avai[c] = false;
            }
        }
    }
    for (int i = 1; i <= global::TOTAL_CHAN_NUM; i++) {
        if (avai[i]) {
            su.avaiChan.push_back(i);
        }
    }
    std::sort(su.avaiChan.begin(), su.avaiChan.end());
}

void DirectionalAntennaImprove::sectorRendOnly() {
    SectorHop s0(global::SEND_SECTOR_NUM, global::SEND);
    SectorHop s1(global::REV_SECTOR_NUM, global::RECEIVE);
    rendPair = {CRmath::randInt(0, global::SEND_SECTOR_NUM - 1), CRmath::randInt(0, global::REV_SECTOR_NUM - 1)};
    //    cout<<rendPair.first<<' '<<rendPair.second<<endl;
    int n = global::SEND_SECTOR_NUM * global::SEND_SECTOR_NUM + global::SEND_SECTOR_NUM * global::REV_SECTOR_NUM;
    for (int i = 0; i < n; i++) {
        int t0 = s0.getCurIndex();
        int t1 = s1.getCurIndex();
        if (t0 == rendPair.first && t1 == rendPair.second) {
            rend_count0++;
            total0 += i;
            break;
        }
    }
    for (int i = 0; i < n; i++) {
        int t0 = CRmath::randInt(0, global::SEND_SECTOR_NUM - 1);
        int t1 = CRmath::randInt(0, global::REV_SECTOR_NUM - 1);
        if (t0 == rendPair.first && t1 == rendPair.second) {
            rend_count1++;
            total1 += i;
            break;
        }
    }
}

void DirectionalAntennaImprove::initChannelAndSectorRend() {
    MySU &su0 = allSU[0];
    MySU &su1 = allSU[1];
    su0.secHop = new SectorHop(su0.transSectorNum, global::SEND);
    su1.secHop = new SectorHop(su1.transSectorNum, global::RECEIVE);
    su0.curSectorID = su0.secHop->getCurIndex();
    su1.curSectorID = su1.secHop->getCurIndex();
    su0.channelHopCount = 0;
    su1.channelHopCount = 0;
    rendSuc0 = 0;
}

void DirectionalAntennaImprove::initChannelAndSectorRendSelectedChannels() {
    MySU &su0 = allSU[0];
    MySU &su1 = allSU[1];
    // copy info for another pair with selected channels
    allSU[4].secHop = su0.secHop;
    allSU[4].curSectorID = su0.curSectorID;
    allSU[4].channelHopCount = su0.channelHopCount;
    allSU[5].secHop = su1.secHop;
    allSU[5].curSectorID = su1.curSectorID;
    allSU[5].channelHopCount = su1.channelHopCount;
    rendSuc2 = 0;
}


void DirectionalAntennaImprove::channelAndSectorRend(int t) {
    MySU &su0 = allSU[0];
    MySU &su1 = allSU[1];
    su0.channelHopCount++;
    su1.channelHopCount++;
    //    cout<<su0.curSectorID<<' '<<su1.curSectorID<<endl;
    if (su0.curSectorID == rendPair.first && su1.curSectorID == rendPair.second) {
        getAvaiChanEachSector(su0, t, su0.curSectorID);
        getAvaiChanEachSector(su1, t, su1.curSectorID);
        int c0 = su0.chanHop->getChanAtTimeT(t + su0.curSysTimeSlot, su0.avaiChan);
        int c1 = su1.chanHop->getChanAtTimeT(t + su1.curSysTimeSlot, su1.avaiChan);
        //        cout<<"my: "<<c0<<' '<<c1<<endl;
        if (c1 == c0) {
            rendSuc0 = 1;
            total0 += t - START_REND_TIME;
            rend_count0++;
#ifdef PRINT_EACH_REND_TIME
            cout << "first: " << t - START_REND_TIME << endl;
#endif
            return;
        }
    } else {
        if (su0.channelHopCount >= global::MTTR) {
            su0.curSectorID = su0.secHop->getCurIndex();
            su0.channelHopCount = 0;
        }
        if (su1.channelHopCount >= global::MTTR) {
            su1.curSectorID = su1.secHop->getCurIndex();
            su1.channelHopCount = 0;
        }
    }
}

void DirectionalAntennaImprove::channelAndSectorRendSelectedChannels(int t) {
    MySU &su0 = allSU[4];
    MySU &su1 = allSU[5];
    su0.channelHopCount++;
    su1.channelHopCount++;
    //    cout<<su0.curSectorID<<' '<<su1.curSectorID<<endl;
    if (su0.curSectorID == rendPair.first && su1.curSectorID == rendPair.second) {
        getAvaiChanEachSectorSeletcedChannelSU(su0, t, su0.curSectorID);
        getAvaiChanEachSectorSeletcedChannelSU(su1, t, su1.curSectorID);
        int index0 = su0.chanHop->getChanAtTimeT(t + su0.curSysTimeSlot);
        int index1 = su1.chanHop->getChanAtTimeT(t + su1.curSysTimeSlot);
        int c0 = su0.allChannelToHop[index0];
        int c1 = su1.allChannelToHop[index1];
        c0 = su0.replaceNotAvaiWithAvai(c0);
        c1 = su1.replaceNotAvaiWithAvai(c1);
        //        cout<<"my: "<<c0<<' '<<c1<<endl;
        if (c1 == c0) {
            rendSuc2 = 1;
            total2 += t - START_REND_TIME;
            rend_count2++;
#ifdef PRINT_EACH_REND_TIME
            cout<<"improved: "<<t - START_REND_TIME<<endl;
#endif
            return;
        }
    } else {
        if (su0.channelHopCount >= 4 * su0.allChannelNum) {
            su0.curSectorID = su0.secHop->getCurIndex();
            su0.channelHopCount = 0;
        }
        if (su1.channelHopCount >= 4 * su1.allChannelNum) {
            su1.curSectorID = su1.secHop->getCurIndex();
            su1.channelHopCount = 0;
        }
    }
}

void DirectionalAntennaImprove::channelAndSectorRendRandom(int t) {
    MySU &su0 = allSU[2];
    MySU &su1 = allSU[3];
    int c0, c1;
    su0.channelHopCount++;
    su1.channelHopCount++;
    if (su0.curSectorID == rendPair.first && su1.curSectorID == rendPair.second) {
        getAvaiChanEachSector(su0, t, su0.curSectorID);
        getAvaiChanEachSector(su1, t, su1.curSectorID);
        //        cout<<su0.avaiChan.size()<<' '<<su1.avaiChan.size()<<endl;
        c0 = su0.chanHop->getChanAtTimeT(t + su0.curSysTimeSlot, su0.avaiChan);
        c1 = su1.chanHop->getChanAtTimeT(t + su1.curSysTimeSlot, su1.avaiChan);
        //        cout<<"random: "<<c0<<' '<<c1<<endl;
        if (c1 == c0) {
            rendSuc1 = 1;
            total1 += t - START_REND_TIME;
            rend_count1++;
#ifdef PRINT_EACH_REND_TIME
            cout << "Random: " << t - START_REND_TIME << endl;
#endif
            return;
        }
    } else {
        if (su0.channelHopCount >= global::MTTR) {
            su0.curSectorID = CRmath::randInt(0, su0.transSectorNum - 1);
            su0.channelHopCount = 0;
        }
        if (su1.channelHopCount >= global::MTTR) {
            su1.curSectorID = CRmath::randInt(0, su1.transSectorNum - 1);
            su1.channelHopCount = 0;
        }
    }
}

void DirectionalAntennaImprove::initChannelAndSectorRendRandom() {
    MySU &su0 = allSU[2];
    MySU &su1 = allSU[3];
    su0.channelHopCount = 0;
    su1.channelHopCount = 0;
    su0.curSectorID = CRmath::randInt(0, su0.transSectorNum - 1);
    su1.curSectorID = CRmath::randInt(0, su1.transSectorNum - 1);
    rendSuc1 = 0;
}

void DirectionalAntennaImprove::initSimulation() {
    rendSuc0 = rendSuc1 = false;
    for (int i = 0; i < global::SU_NUM; i++) {
        SU &su = allSU[i];
        for (int j = 1; j <= global::TOTAL_CHAN_NUM; j++) {
            su.allChanObj[j].ifAvai = 0;
            su.allChanObj[j].curConAvaiTime = 0;
        }
    }
}

void DirectionalAntennaImprove::startSimulation() {
    /*******************Sector Rendezvous Only********************************/
    //    for(int i = 0; i < SIMULATION_REPEAT_TIME; i++){
    ////        START_REND_TIME = my_randint(TOTAL_TIME_SLOT/5, TOTAL_TIME_SLOT/2);
    //        sectorRendOnly();
    //    }
    //    cout<<"Aver time: "<<total0*1.0/rend_count0<<endl;
    //    cout<<"rend times: "<<rend_count0*100.0/SIMULATION_REPEAT_TIME<<endl;
    //    cout<<"Aver time: "<<total1*1.0/rend_count1<<endl;
    //    cout<<"rend times: "<<rend_count1*100.0/SIMULATION_REPEAT_TIME<<endl;
    /*******************Sector Rendezvous Only********************************/

    /*******************Channel and sector rendezvous ***************************/
    total0 = total1 = 0;
    rend_count0 = rend_count1 = 0;
    for (int i = 0; i < global::SIMULATION_REPEAT_TIME; i++) {
        START_REND_TIME = CRmath::randInt(global::TOTAL_TIME_SLOT / 5, global::TOTAL_TIME_SLOT / 4);
        initChannelAndSectorRend();
        initChannelAndSectorRendRandom();
        initChannelAndSectorRendSelectedChannels();
        for (int t = 0; t < global::TOTAL_TIME_SLOT; t++) {
            if (t >= START_REND_TIME) {
                if (!rendSuc0) channelAndSectorRend(t);
                if (!rendSuc1) channelAndSectorRendRandom(t);
                if (!rendSuc2) channelAndSectorRendSelectedChannels(t);
            }
        }
//        cout<<endl;
    }
    cout << "avg my rend times: " << total0 / rend_count0 << endl;
    cout << "avg random rend times: " << total1 / rend_count1 << endl;
    cout << "avg selected channel rend times: " << total2 / rend_count2 << endl;
    cout << "my rend count: " << rend_count0 << endl;
    cout << "random rend count: " << rend_count1 << endl;
    cout << "selected channel scheme rend count: " << rend_count2 << endl;
    /*******************Channel and sector rendezvous ***************************/
}
