//
// Created by Ji Li on 2017/9/10.
//

#ifndef CRSIM_PU_H
#define CRSIM_PU_H
//
//  pu.h
//  CRsim
//
//  Created by Ji on 14-10-6.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "../lib/lib.h"
#include "user.h"

class PU: public User{
public:
    int licensedChan;
    int curComePktID;
    int chanOfEachTimeSlot[global::TOTAL_TIME_SLOT+10];//equal to -1 if pu is inactive
    bool ifTransmitting;


    void initLocationRandom();

    PU();
};

#endif //CRSIM_PU_H
