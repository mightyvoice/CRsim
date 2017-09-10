//
//  sector_hop.cpp
//  CRsim
//
//  Created by Ji on 15/3/24.
//  Copyright (c) 2015年 lj. All rights reserved.
//

#include "sector_hop.h"

SectorHop:: SectorHop(int n)
{
    sectorNum = n;
    curIndex = startIndex = -1;
    hopCount = 0;
}

SectorHop:: SectorHop(int n, global::SEND_OR_RECEIVE _role)
{
    sectorNum = n;
    curIndex = startIndex = -1;
    hopCount = 0;
    sendOrRev = _role;
}

SectorHop:: SectorHop()
{
    curIndex = startIndex = -1;
    hopCount = 0;
}

int SectorHop:: getIndexAtTimeT(int t)
{
    return 0;
}

int SectorHop:: senderGetCurIndex()
{
    if(curIndex < 0 ){
        curIndex = startIndex = CRmath::randIntDiff(0, sectorNum-1);
        hopCount = 1;
        return curIndex;
    }
    if(hopCount <= sectorNum*sectorNum){
        if(hopCount % sectorNum == 0) curIndex += 2;
        else curIndex++;
        hopCount++;
    }
    else{
        curIndex++;
        hopCount++;
    }
    if(curIndex > sectorNum-1){
        curIndex -= sectorNum;
    }
    return curIndex;
}

int SectorHop:: receiverGetCurIndex()
{
    if(curIndex < 0){
        curIndex = startIndex = CRmath::randIntDiff(0, sectorNum-1);
        hopCount = 1;
        return curIndex;
    }
    else{
        curIndex++;
        hopCount++;
        if(curIndex > sectorNum-1){
            curIndex -= sectorNum;
        }
    }
    return curIndex;
}

int SectorHop:: getCurIndex()
{
    if(sendOrRev == global::SEND) return senderGetCurIndex();
    else return receiverGetCurIndex();
}
