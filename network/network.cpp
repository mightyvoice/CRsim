//
//  network.cpp
//  CRsim
//
//  Created by Ji on 14-10-6.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "network.h"

CRNetwork::CRNetwork()
{
    avaiChanNumForPU = global::TOTAL_CHAN_NUM;
    memset(chanAllocToPuCount, 0, sizeof(chanAllocToPuCount));
    initAllPU();
    initAllPuTrafficEachTime();
}

void CRNetwork:: initAllPU()
{
    allPU.clear();
    for(int i = 0; i < global::PU_NUM; i++){
        PU p;
        allPU.push_back(p);
//        cout<<p.location.first<<' '<<p.location.second<<endl;
    }
}

void CRNetwork:: initAllPuTrafficEachTime()
{
    for(int i = 0; i < global::PU_NUM; i++){
        PU &pu = allPU[i];
        pu.ifTransmitting = false;
        pu.curComePktID = 0;
        while(!pu.pktTransQueue.empty()){
            pu.pktTransQueue.pop();
        }
        for(int j = 0; j < global::TOTAL_TIME_SLOT+2; j++){
            pu.chanOfEachTimeSlot[j] = -1;
        }
    }
    for(int t = 0; t < global::TOTAL_TIME_SLOT+1; t++){
        for(int i = 0; i < global::PU_NUM; i++){
            PU &pu = allPU[i];
            pu.chanOfEachTimeSlot[t] = pu.curStayChan;
            if(pu.curComePktID < pu.allDataPkt.size() && t >= pu.allDataPkt[pu.curComePktID].arrivalTimeSlot){
                pu.pktTransQueue.push(pu.allDataPkt[pu.curComePktID]);
                pu.curComePktID++;
            }
            if(pu.ifTransmitting == false && !pu.pktTransQueue.empty()){
                int tmp_chan;
#ifdef ALLOC_RANDOM_CHAN_PU
                tmp_chan = allocChanRandomToPU();
#endif
#ifdef ALLOC_UNUSED_CHAN_PU
                tmp_chan = allocChanUnUsedToPU();
#endif
                if(tmp_chan > 0){
                    pu.ifTransmitting = true;
                    pu.pktTransQueue.front().startTransTimeSlot = t;
                    pu.pktTransQueue.front().onWhichChan = tmp_chan;
                    pu.chanOfEachTimeSlot[t] = tmp_chan;
                    pu.curStayChan = tmp_chan;
                }
            }
            if(pu.ifTransmitting == true && t - pu.pktTransQueue.front().startTransTimeSlot >= pu.pktTransQueue.front().len - 1){
                pu.ifTransmitting = false;
                pu.pktTransQueue.pop();
                puReturnAllocChan(pu.curStayChan);
                pu.curStayChan  = -1;
            }
        }
    }
}

int CRNetwork:: allocChanRandomToPU()
{
    int tmp_chan;
#ifdef SAME_NET_PARAMETERS_EACH_SIM
    tmp_chan = CRmath::randInt(1, global::TOTAL_CHAN_NUM);
#endif

#ifdef DIFF_NET_PARAMETERS_EACH_SIM
    tmp_chan = CRmath::randIntDiff(1, TOTAL_CHAN_NUM);
#endif
    chanAllocToPuCount[tmp_chan]++;
    avaiChanNumForPU--;
    return tmp_chan;
}

int CRNetwork:: allocChanUnUsedToPU()
{
    if(avaiChanNumForPU > 0){
        while(true){
            int tmp;
#ifdef SAME_NET_PARAMETERS_EACH_SIM
            tmp = CRmath::randInt(1, global::TOTAL_CHAN_NUM);
#endif
#ifdef DIFF_NET_PARAMETERS_EACH_SIM
            tmp = CRmath::randIntDiff(1, TOTAL_CHAN_NUM);
#endif
            if(chanAllocToPuCount[tmp] == 0){
                chanAllocToPuCount[tmp]++;
                avaiChanNumForPU--;
                return tmp;
            }
        }
    }
    return 0;
}

void CRNetwork:: puReturnAllocChan(int _chan_id)
{
    chanAllocToPuCount[_chan_id]--;
    avaiChanNumForPU++;
}

void CRNetwork:: initSuNeighborPU(MySU &su)
{
    su.neighborPU.clear();
    for(int j = 0; j < global::PU_NUM; j++){
        if(CRmath::twoPointsDistanceSquare(su.location.first, su.location.second,
                                           allPU[j].location.first, allPU[j].location.second)
           <= global::SENSE_RANGE_SU * global::SENSE_RANGE_SU){
            su.neighborPU.push_back(j);
        }
    }
}

void CRNetwork:: getSUsCurAvaiChan(int t)
{
    ////////////get available channels of each SU on current time////////
    if( t >= global::TOTAL_TIME_SLOT) return;
    for(int i = 0; i < global::SU_NUM; i++){
        MySU &su = allSU[i];
        su.avaiChan.clear();
        bool avai[global::TOTAL_CHAN_NUM+5] = {0};
        for(int j = 1; j <= global::TOTAL_CHAN_NUM; j++){
            avai[j] = true;
        }
        for(int j = 0; j < su.neighborPU.size(); j++){
            int n = su.neighborPU[j];
            int c = allPU[n].chanOfEachTimeSlot[t];
            if(c > 0 && c <= global::TOTAL_CHAN_NUM){
                avai[c] = false;
            }
        }
        for(int j = 1; j <= global::TOTAL_CHAN_NUM; j++){
            if(avai[j]){
                su.avaiChan.push_back(j);
                su.allChanObj[j].ifAvai = true;
            }
            else{
                su.allChanObj[j].ifAvai = false;
            }
        }
    }
}

void CRNetwork:: getCurConAvaiChan()
{
    cout<<"Con avai chan: ";
    vI ans = getComFromTwoVector(allSU[0].avaiChan, allSU[1].avaiChan);
    printVector(ans);
}

void CRNetwork:: getCurAllChanConAvaiTime()
{
    for(int i  = 0; i < global::SU_NUM; i++){
        MySU &su = allSU[i];
        for(int j = 1; j <= global::TOTAL_CHAN_NUM; j++){
            if(su.allChanObj[j].ifAvai){
                su.allChanObj[j].curConAvaiTime++;
            }
            else{
                if(su.allChanObj[j].curConAvaiTime > 0){
                    su.allChanObj[j].allConAvaiTime.push_back(su.allChanObj[j].curConAvaiTime);
                    su.allChanObj[j].curConAvaiTime = 0;
                }
            }
        }
    }
}

void CRNetwork:: getCommonAvaiRatio()
{
    MySU &su0 = allSU[0];
    MySU &su1 = allSU[1];
    for(int x : su0.avaiChan){
        chanAvaiCountSu0[x]++;
        if(vectorFind(su1.avaiChan, x)){
            chanComAvaiCountSu0Su1[x]++;
        }
    }
}

double CRNetwork:: calAverConAvaiTime()
{
    double p_act = global::PKT_ARR_RATE_PU*global::PKT_MAX_LEN_PU*global::TIME_SLOT_LEN/global::PKT_MAX_LEN_PU;
    int n = (int)allSU[0].neighborPU.size();
    int m = global::TOTAL_CHAN_NUM;
    double ans = 0;
    for(int k = 0; k <= n; k++){
        ans += CRmath::nChooseM(n, k) * pow(p_act*(1.0*m-1)/m, k) * pow(1-p_act, n-k);
    }
    return 1.0/(1.0-ans);
}

double CRNetwork:: calConAvaiChanAverConAvaiTime()
{
    double p_act = global::PKT_ARR_RATE_PU*global::PKT_MAX_LEN_PU*global::TIME_SLOT_LEN/global::PKT_MAX_LEN_PU;
    vI tmp = getComFromTwoVector(allSU[0].neighborPU, allSU[1].neighborPU);
    int n = (int)tmp.size();
    cout<<"Common number: "<<n<<endl;
    int m = global::TOTAL_CHAN_NUM;
    double ans = 0;
    for(int k = 0; k <= n; k++){
        ans += CRmath::nChooseM(n, k) * pow(p_act*(1.0*m-1)/m, k) * pow(1-p_act, n-k);
    }
    cout<<"Available at a time slot: "<<ans<<endl;
    cout<<"Exp length: "<<1.0/(1-ans)<<endl;
    //    cout<<"P_avai: "<<ans<<endl;
    //    cout<<"Aver_avai_len: "<<1.0/(1-ans)<<endl;
//    total_cal += 1.0/(1.0-ans);
    return 1.0/(1.0-ans);
}
