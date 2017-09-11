//
// Created by Ji Li on 2017/9/9.
//

#ifndef CRSIM_MY_SEND_REV_HOP_H
#define CRSIM_MY_SEND_REV_HOP_H
//
//  my_send_rev_hop.h
//  CRsim
//
//  Created by Ji on 15/7/30.
//  Copyright (c) 2015年 lj. All rights reserved.
//

#include "../lib/lib.h"
#include "my_seq.h"

class MySendRevHop : public MyHop {
private:
    int realChanNum;

    void getSendRevHopSeq();

public:
    //total  real channel number
    MySendRevHop(int cur_chan_n, int _st_time);

    //total real channel number, available channel set
    MySendRevHop(int cur_chan_n, int _st_time, vI &avai);

};

#endif //CRSIM_MY_SEND_REV_HOP_H
