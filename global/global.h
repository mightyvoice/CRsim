//
// Created by Ji Li on 2017/9/9.
//

#ifndef CRSIM_GLOBAL_H
#define CRSIM_GLOBAL_H

namespace global {

    const int TOTAL_CHAN_NUM = 30; // total number of channels in the whole spectrum

    const int MTTR = 4 * TOTAL_CHAN_NUM;

    const int SEND_SECTOR_NUM = 7;

    const int REV_SECTOR_NUM = 5;

    const int RAND_SEED_INIT_VAL = 100;

    const int SU_NUM = 4; //number of SUs

    const int PU_NUM = 30; //number of PUs

    const double PKT_ARR_RATE_PU = 10; // pu packet arrival rate

    const double MAX_SENSE_CHAN_RATIO = 5;//

    const int MAX_SENSE_CHAN_NUM = (int) (MAX_SENSE_CHAN_RATIO * TOTAL_CHAN_NUM);

    const int PKT_MAX_LEN_PU = 100; //packet size

    const int PKT_MIN_LEN_PU = 100; //packet size

    const int TOTAL_TIME_SLOT = 50000; //simulation time slots

    const int SIMULATION_REPEAT_TIME = 200; //Do how many simulations

    const double TIME_SLOT_LEN = 0.002; //length of each time slot

    const double CHAN_AVAI_RATIO = 0.5; //channel available ration of each SU

    const double NEIGHBOR_RATIO = 0.5; //channel available ration of each SU

    const double USED_CHAN_RATIO = 0.5; //channel available ration of each SU

    const double SENSE_RANGE_SU = 100; // sensing range of SU

    const int CR_NUM = 8; //number of cognitive radio of SU

    const double EPS = 1e-7; // Precision of double number

    const int PKT_MAX_LEN_SU = 10; //packet size

    const double PKT_ARR_RATE_SU = 10; // su packet arrival rate

    const int SIDE_LENGTH = 200; //area side length

    const int THETA_OF_SSL = 20;

    const int INT_MAX_VAL = 2147483647;

    enum SEND_OR_RECEIVE {
        SEND = 0, RECEIVE = 1
    };

}

#endif //CRSIM_GLOBAL_H
