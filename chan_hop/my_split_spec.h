//
// Created by Ji Li on 2017/9/9.
//

#ifndef CRSIM_MY_SPLIT_SPEC_H_H
#define CRSIM_MY_SPLIT_SPEC_H_H

//
//  my_split_spec.h
//  CRsim
//
//  Created by Ji on 14-10-5.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "../lib/lib.h"

/* Get the ssl based on my original splitting scheme based on Theta and the
 exsitence of my hopping sequence that a sequence with n channels only exists
 when n % 4 == 0 or n % 4 == 1, put the results into ssl; index from 1;
 */
void my_orig_split_ssl(int cur_chan_n, vI &ssl);


#endif //CRSIM_MY_SPLIT_SPEC_H_H
