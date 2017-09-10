//
//  en_jump_stay.cpp
//  CRsim
//
//  Created by Ji on 14-10-3.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "en_jump_stay.h"

EnJsHop:: EnJsHop():JsHop()
{
    init_seq();
}

EnJsHop:: EnJsHop(int cur_avai_n):JsHop(cur_avai_n)
{
    init_seq();
}

EnJsHop:: EnJsHop(int cur_chan_n, vI &avai):JsHop(cur_chan_n)
{
    avai = avai;
    init_seq();
}

void EnJsHop::  init_seq()
{
    init_prime_num();
    for(int i = global::TOTAL_CHAN_NUM; i < global::TOTAL_CHAN_NUM*2; i++){
        if(prime[i] == 0) {
            P = i;
            return ;
        }
    }
//    i0 = CRmath::randIntDiff(1, avai_chan_n);
//    r0 = CRmath::randIntDiff(1, P);
#ifdef SAME_NET_PARAMETERS_EACH_SIM
    i0 = CRmath::randInt(1, avai_chan_n);
#endif
#ifdef DIFF_NET_PARAMETERS_EACH_SIM
    i0 = CRmath::randIntDiff(1, avai_chan_n);
#endif
#ifdef SAME_NET_PARAMETERS_EACH_SIM
    r0 = CRmath::randInt(1, P);
#endif
#ifdef DIFF_NET_PARAMETERS_EACH_SIM
    r0 = CRmath::randIntDiff(1, P);
#endif
}

void EnJsHop:: resetChanHop()
{
    i0 = CRmath::randIntDiff(1, M);
    r0 = CRmath::randIntDiff(1, P);
}

int EnJsHop:: getChanAtTimeT(int t)
{
    return 0;
}

int EnJsHop:: getChanAtTimeT(int t, const vI &avai)
{
    int j;
    int n = t / (4*P);
    int i00 = (i0 + n -1) % P + 1;// update the i0
    t %= (4*P);
    if(t < 3*P){
        j = (i00 + t*r0 - 1) % P + 1;
    }
    else{
        j = r0;
    }
    if(j > M){
        j = (j-1)%M + 1;
    }
    if(!vectorFind(avai, j)){
        j = avai[(j - 1) % avai.size()];
    }
    curChan  = j;
    return j;
}

int EnJsHop:: getChanAtTimeTBeforeReplace(int t)
{
    int j;
    int n = t / (4*P);
    int i00 = (i0 + n -1) % P + 1;// update the i0
    t %= (4*P);
    if(t < 3*P){
        j = (i00 + t*r0 - 1) % P + 1;
    }
    else{
        j = r0;
    }
    if(j > M){
        j = (j-1)%M + 1;
    }
//    if(!vectorFind(avai, j)){
//        j = avai[(j - 1) % avai.size()];
//    }
//    curChan  = j;
    return j;
}
