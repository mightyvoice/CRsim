//
// Created by Ji Li on 2017/9/9.
//


#include "chan_hop.h"

ChanHop:: ChanHop()
{
    M = global::TOTAL_CHAN_NUM;
}

ChanHop:: ChanHop(int chan_n)
{
    M = chan_n;
}

ChanHop:: ChanHop(int chan_n, vI &avai)
{
    M = chan_n;
    avai_chan = avai;
    avai_chan_n = (int)avai_chan.size();
}

