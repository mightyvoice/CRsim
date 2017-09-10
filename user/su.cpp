//
//  su.cpp
//  CRsim
//
//  Created by Ji on 14-10-6.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "su.h"

SU:: SU(): User()
{
    return;
}

vI SU::getAvaiChanRandom(int _chan_n)
{
    vI ans;
    this->avaiChanNum = _chan_n * global::CHAN_AVAI_RATIO;
    int tmp = 0;
    while(tmp < avaiChanNum){
        int t1;
#ifdef SAME_NET_PARAMETERS_EACH_SIM
        t1 = CRmath::randInt(1, _chan_n);
#endif
#ifdef DIFF_NET_PARAMETERS_EACH_SIM
        t1 = CRmath::randIntDiff(1, _chan_n);
#endif
        if(!vectorFind(ans, t1)){
            ans.push_back(t1);
            tmp++;
        }
    }
    sort(ans.begin(), ans.end());
    return  ans;
}

vI SU::getAvaiChanRandom()
{
    return getAvaiChanRandom(global::TOTAL_CHAN_NUM);
}

void SU:: initAllCognitiveRadio(int numOfCR)
{
    for(int i = 0; i < numOfCR; i++){
        CognitiveRadio tmp;
        this->allCR.push_back(tmp);
    }
}
