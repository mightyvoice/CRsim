//
// Created by Ji Li on 2017/9/9.
//

#ifndef CRSIM_MY_SEQ_H
#define CRSIM_MY_SEQ_H
//
//  my_seq.h
//  CRsim
//
//  Created by Ji on 14-10-3.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "../lib/lib.h"
#include "chan_hop.h"

class MyHop: public ChanHop{
public:
    int curIndex;
    int startIndex; // The start seq index, starts with 1
    int hopCountInARound; //The start seq index in current round, starts with 1
    int curRoundStartIndex;
    int roundCount;

    MyHop(int _st_time);//the default total channel bumber in global.h
    MyHop(int cur_chan_n, int _st_time);//total channel number
    MyHop(int cur_chan_n, int _st_time, vI &avai);//total channel number, available channel set

    void init_my_hop(int t, int st_id); //t is the time start the hop, id is the index of seq to start
    void get_hop_para(int t);// get the parameters of my hopping at time t

    void init_seq();// Init the channel hopping sequence
    void resetChanHop();
    int getChanAtTimeT(int t); //Get the channel to hop to at time t if it needs the available set;
    int getChanAtTimeT(int t, const vI &avai); //Get the channel to hop to at time t;
    int getChanAtTimeTBeforeReplace(int t);
};

#endif //CRSIM_MY_SEQ_H
