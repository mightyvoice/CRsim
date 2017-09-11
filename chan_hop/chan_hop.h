//
// Created by Ji Li on 2017/9/9.
//

#ifndef CRSIM_CHAN_HOP_H
#define CRSIM_CHAN_HOP_H

#include "../global/include.h"

class ChanHop {
public:
    int M;
    int totalChan;
    int avai_chan_n; //The number of the available channels
    int curChan; //current channel to hop
    int startHopTime;//The time to start the hopping
    int sequenceLen;
    vI avai_chan; //Available channel set
    vI hopSequence;//Hopping sequence, index from 1

    ChanHop();

    ChanHop(int chan_n);

    ChanHop(int chan_n, vI &avai);

    virtual void init_seq() = 0;// Init the channel hopping sequence
    virtual void resetChanHop() = 0;

    virtual int getChanAtTimeT(int t) = 0; //Get the channel to hop to at time t;
    virtual int getChanAtTimeT(int t, const vI &avai) = 0; //Get the channel to hop to at time t;
    virtual int getChanAtTimeTBeforeReplace(int t) = 0;
};

#endif //CRSIM_CHAN_HOP_H
