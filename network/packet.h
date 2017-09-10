//
// Created by Ji Li on 2017/9/10.
//

#ifndef CRSIM_PACKET_H
#define CRSIM_PACKET_H
//
//  packet.h
//  CRsim
//
//  Created by Ji on 15/1/20.
//  Copyright (c) 2015年 lj. All rights reserved.
//

#include "../lib/lib.h"

class DataPacket{
public:
    int ID; // id starts from 0
    int len; //length time slot
    double arrivalTime; //arrival time
    int arrivalTimeSlot; //arrival time slot;
    int startTransTimeSlot; //start transmission time slot;
    int onWhichChan;
};

#endif //CRSIM_PACKET_H
