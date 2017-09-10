//
// Created by Ji Li on 2017/9/9.
//

#ifndef CRSIM_JUMP_STAY_H
#define CRSIM_JUMP_STAY_H
//
//  jump_stay.h
//  CRsim
//
//  Created by Ji on 14-10-3.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "../lib/lib.h"
#include "chan_hop.h"

class JsHop: public ChanHop{
private:

public:
    int P;
    int r0;
    int i0;
    int prime[global::TOTAL_CHAN_NUM*3];

    JsHop();
    JsHop(int chan_n);
    void init_prime_num();
    void init_seq();// Init the channel hopping sequence
    void resetChanHop();
    int getChanAtTimeT(int t); //Get the channel to hop to at time t;
    int getChanAtTimeT(int t, const vI &avai); //Get the channel to hop to at time t;
    int getChanAtTimeTBeforeReplace(int t);
};

#endif //CRSIM_JUMP_STAY_H
