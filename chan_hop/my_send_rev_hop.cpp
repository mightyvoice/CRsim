//
//  my_send_rev_hop.cpp
//  CRsim
//
//  Created by Ji on 15/7/30.
//  Copyright (c) 2015年 lj. All rights reserved.
//

#include "my_send_rev_hop.h"

//total channel number
MySendRevHop:: MySendRevHop(int cur_chan_n, int _st_time) : MyHop(2*cur_chan_n, _st_time), realChanNum(cur_chan_n)
{
    getSendRevHopSeq();
}

//total channel number, available channel set
MySendRevHop:: MySendRevHop(int cur_chan_n, int _st_time, vI &avai) : MyHop(2*cur_chan_n, _st_time, avai), realChanNum(cur_chan_n)
{
    getSendRevHopSeq();
}

void MySendRevHop:: getSendRevHopSeq()
{
    for(int i = 1; i <= 2*realChanNum; i++){
        for(int j = 4*realChanNum; j > 0; j--){
            if(hopSequence[j] == i){
                cout<<i<<' '<<j<<endl;
                if(i > realChanNum) hopSequence[j] -= realChanNum;
                else hopSequence[j] += realChanNum;
                break;
            }
        }
    }
}
