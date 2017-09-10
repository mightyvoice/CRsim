//
// Created by Ji Li on 2017/9/10.
//

#ifndef CRSIM_USER_H
#define CRSIM_USER_H
//
//  user.h
//  CRsim
//
//  Created by Ji on 14-10-5.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "../lib/lib.h"
#include "../chan_hop/all_chan_hop.h"
#include "../network/packet.h"
#include "../network/channel.h"

class User{
public:
    int totalAccessChan;
    pair<double, double> location;
    vI allChan;
    vI avaiChan;
    vector<DataPacket> allDataPkt;
    queue<DataPacket> pktTransQueue;
    CRchannel allChanObj[global::TOTAL_CHAN_NUM+2];

    int avaiChanNum;
    int curStayChan;
    int ID; //from 1 to the number of total SUs
    global::SEND_OR_RECEIVE sendOrReceive;

    double init_sys_t; // the initial time of each user
    double init_sys_slot; //the initial time slot of each user
    double st_sys_t; //the time to start simulation
    double st_sys_slot; // the time slot to start simu
    double cur_sys_t;//current system time
    double pktArrivalRate;
    int curSysTimeSlot;//current system time slot
    vI neighborPU; //neighbors
    vI neighborSU; //neighbors
    double transRange; //transmission range
    double transPower; //power,

    /*** Considering directional antennas ***/
    int transSectorNum;
    double transSectorAngle;
    int curSectorID;
    pair<double, double> sectorSplit[global::TOTAL_CHAN_NUM*2];
    int sectorNeighborPU[35][global::PU_NUM+2];
    int channelHopCount;
    SectorHop *secHop;
    void initSectorSplit();
    /*** Considering directional antennas ***/

    ChanHop *chanHop;
    vI chanHopSeq;

    User();
    void printPktInterval();
    void initAllPktArrivalTime(double arrRate);
    void initAllPkt(double arrRate, int pkt_max_len);
};

#endif //CRSIM_USER_H
