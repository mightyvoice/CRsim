//
// Created by Ji Li on 2017/9/10.
//

#ifndef CRSIM_DIRECTIONALANTENNAIMPROVE_H
#define CRSIM_DIRECTIONALANTENNAIMPROVE_H
//
//  DirectionalAntennaImprove.hpp
//  CRsim
//
//  Created by Ji Li on 2017/9/9.
//  Copyright © 2017年 lj. All rights reserved.
//

#include "../network/network.h"
#include "../chan_hop/all_chan_hop.h"

class DirectionalAntennaImprove: public CRNetwork{
public:
    //considering directional antenna
    DirectionalAntennaImprove();
    void initAllSU();
    void initSimulation();
    void startSimulation();

private:
    const double ALL_CHANNEL_RATIO = 0.5;
    bool rendSuc0;
    bool rendSuc1;
    bool rendSuc2;
    pair<int, int> rendPair;
    void initSuNeighborSector(MySU &su);
    void initSuNeighborPU(MySU &su);
    void getAvaiChanEachSector(MySU &su, int t, int _sector);
    void getAvaiChanEachSectorNewSU(MySU &su, int t, int _sector);
    void getRendPair(const MySU &su0, const MySU &su1);
    void sectorRendOnly();
    void initChannelAndSectorRend();
    void channelAndSectorRend(int t);
    void initChannelAndSectorRendRandom();
    void channelAndSectorRendRandom(int t);

};


#endif //CRSIM_DIRECTIONALANTENNAIMPROVE_H
