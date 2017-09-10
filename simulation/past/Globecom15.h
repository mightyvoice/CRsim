//
// Created by Ji Li on 2017/9/10.
//

#ifndef CRSIM_GLOBECOM15_H
#define CRSIM_GLOBECOM15_H
//
//  Globecom15.h
//  CRsim
//
//  Created by Ji on 15/4/28.
//  Copyright (c) 2015年 lj. All rights reserved.
//

#include "../../network/network.h"
#include "../../chan_hop/en_jump_stay.h"

class Globecom15: public CRNetwork{
public:
    //considering directional antenna
    Globecom15();
    void initAllSU();
    void initSimulation();
    void startSimulation();

private:

    bool rendSuc0;
    bool rendSuc1;
    pair<int, int> rendPair;
    void initSuNeighborSector(MySU &su);
    void initSuNeighborPU(MySU &su);
    void getAvaiChanEachSector(MySU &su, int t, int _sector);
    void getRendPair(const MySU &su0, const MySU &su1);
    void sectorRendOnly();
    void initChannelAndSectorRend();
    void channelAndSectorRend(int t);
    void initChannelAndSectorRendRandom();
    void channelAndSectorRendRandom(int t);

};


#endif //CRSIM_GLOBECOM15_H
