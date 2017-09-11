//
//  pu.cpp
//  CRsim
//
//  Created by Ji on 14-10-6.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "pu.h"

PU::PU() {
    initLocationRandom();
    initAllPkt(global::PKT_ARR_RATE_PU, global::PKT_MAX_LEN_PU);
}

void PU::initLocationRandom() {
    int x, y;
#ifdef SAME_NET_PARAMETERS_EACH_SIM
    x = CRmath::randInt(0, global::SIDE_LENGTH);
    y = CRmath::randInt(0, global::SIDE_LENGTH);
#endif

#ifdef DIFF_NET_PARAMETERS_EACH_SIM
    x = CRmath::randIntDiff(0, SIDE_LENGTH);
    y = CRmath::randIntDiff(0, SIDE_LENGTH);
#endif

    location = make_pair((double) x, (double) y);
}
