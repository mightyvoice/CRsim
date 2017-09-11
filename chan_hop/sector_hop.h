//
// Created by Ji Li on 2017/9/9.
//

#ifndef CRSIM_SECTOR_HOP_H
#define CRSIM_SECTOR_HOP_H
//
//  sector_hop.h
//  CRsim
//
//  Created by Ji on 15/3/24.
//  Copyright (c) 2015年 lj. All rights reserved.
//

#include "../lib/lib.h"
#include "chan_hop.h"

class SectorHop {
public:
    global::SEND_OR_RECEIVE sendOrRev;
    int sectorNum;
    int startIndex;
    int hopCount;
    int curIndex;

    int getIndexAtTimeT(int t);

    int getCurIndex();

    int senderGetCurIndex();

    int receiverGetCurIndex();

    SectorHop(int n);

    SectorHop(int n, global::SEND_OR_RECEIVE _role);

    SectorHop();

};

#endif //CRSIM_SECTOR_HOP_H
