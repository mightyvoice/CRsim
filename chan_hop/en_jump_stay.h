//
// Created by Ji Li on 2017/9/9.
//

#ifndef CRSIM_EN_JUMP_STAY_H
#define CRSIM_EN_JUMP_STAY_H

#include "../lib/lib.h"
#include "jump_stay.h"

class EnJsHop : public JsHop{
public:
    EnJsHop();
    EnJsHop(int cur_avai_n);
    EnJsHop(int cur_chan_n, vI &avai);
    void init_seq();// Init the channel hopping sequence
    void resetChanHop();
    int getChanAtTimeT(int t); //Get the channel to hop to at time t if it needs the available set;
    int getChanAtTimeT(int t, const vI &avai); //Get the channel to hop to at time t;
    int getChanAtTimeTBeforeReplace(int t);
};

#endif //CRSIM_EN_JUMP_STAY_H
