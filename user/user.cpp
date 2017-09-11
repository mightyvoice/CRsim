//
//  user.cpp
//  CRsim
//
//  Created by Ji on 14-10-5.
//  Copyright (c) 2014年 lj. All rights reserved.//

#include "user.h"

User::User() : totalAccessChan(global::TOTAL_CHAN_NUM) {

}

void User::printPktInterval() {
    int sum = 0;
    for (int i = 1; i < allDataPkt.size(); i++) {
        int tmp = allDataPkt[i].arrivalTimeSlot - allDataPkt[i - 1].arrivalTimeSlot;
        sum += tmp;
        cout << tmp << ' ';
    }
    cout << endl << sum / (allDataPkt.size() - 1) << endl;
}

void User::initAllPkt(double arrRate, int pkt_max_len) {
    allDataPkt.clear();
    double st;
#ifdef SAME_NET_PARAMETERS_EACH_SIM
    st = CRmath::randExponential(arrRate);
#endif
#ifdef DIFF_NET_PARAMETERS_EACH_SIM
    st = CRmath::randExponentialDiff(arrRate);
#endif
    int curID = 0;
    while (true) {
        if (st - global::TOTAL_TIME_SLOT * global::TIME_SLOT_LEN > global::EPS) {
            break;
        }
        DataPacket p;
        p.ID = curID++;
        p.arrivalTime = st;
#ifdef SET_RANDOM_PU_PKT_LEN
#ifdef SAME_NET_PARAMETERS_EACH_SIM
        p.len = CRmath::randInt(PKT_MIN_LEN_PU, pkt_max_len);
#endif
#ifdef DIFF_NET_PARAMETERS_EACH_SIM
        p.len = CRmath::randIntDiff(PKT_MIN_LEN_PU, pkt_max_len);
#endif
#endif

#ifdef SET_STATIC_PU_PKT_LEN
        p.len = global::PKT_MAX_LEN_PU;
#endif
        allDataPkt.push_back(p);
        double tmp;
#ifdef SAME_NET_PARAMETERS_EACH_SIM
        tmp = CRmath::randExponential(arrRate);
#endif
#ifdef DIFF_NET_PARAMETERS_EACH_SIM
        tmp = CRmath::randExponentialDiff(arrRate);
#endif
        st += tmp;
    }
    for (int i = 0; i < allDataPkt.size(); i++) {
        allDataPkt[i].arrivalTimeSlot = (int) (allDataPkt[i].arrivalTime / global::TIME_SLOT_LEN);
//        cout<<allDataPkt[i].arrivalTimeSlot<<' ';
    }
//    cout<<endl<<endl;
//    printPktInterval();
}

void User::initSectorSplit() {
    transSectorAngle = 360.0 / transSectorNum / 180 * PI;
    double a = 0;
    for (int i = 0; i < transSectorNum; i++) {
        pair<double, double> p;
        p = make_pair(100 * cos(a), 100 * sin(a));// angle
        sectorSplit[i] = p;
        a += transSectorAngle;
    }
    sectorSplit[transSectorNum] = sectorSplit[0];
    for (int i = 0; i <= transSectorNum; i++) {
        sectorSplit[i].first += location.first;
        sectorSplit[i].second += location.second;
    }
}

