//
//  my_su.cpp
//  CRsim
//
//  Created by Ji on 14-10-7.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "my_su.h"

MySU::MySU() : SU() {
    getMyHopSeq();
    getTransSeq();
    return;
}

void MySU::getTransSeq() {
    transSeq = "";
    int m = global::TOTAL_CHAN_NUM;
    for (int i = 0; i < m + 2; i++) transSeq += '0';
    vI tmp = CRmath::generateDiffRandIntDiffSeed(m / 2, 0, m - 1);
    for (auto x: tmp) {
        transSeq[x] = '1';
    }
    transSeqLen = m;
}

void MySU::getMyHopSeq() {
    int n = totalAccessChan;
    if (n % 4 == 2) n += 2;
    if (n % 4 == 3) n += 1;
    seqLen = 2 * n;
    MyHop tmp(n, 0);
    chanHopSeq.clear();
    for (auto x: tmp.hopSequence) {
        int x1 = x;
        if (x1 > totalAccessChan) x1 %= totalAccessChan;
        chanHopSeq.push_back(x1);
    }
}

void MySU::getMySendRevHopSeq() {
    int m = totalAccessChan * 2;
    int n = m;
    if (n % 4 == 2) n += 2;
    seqLen = 2 * n;
    MyHop tmp(n, 0);
    chanHopSeq.clear();
    for (auto x: tmp.hopSequence) {
        int x1 = x;
        if (x1 > m) x1 %= m;
        chanHopSeq.push_back(x1);
    }
    bool vis[1000] = {0};
    for (int j = 1; j <= seqLen; j++) {
        if (!vis[chanHopSeq[j]]) {
            vis[chanHopSeq[j]] = 1;
        } else {
            vis[chanHopSeq[j]] = 0;
            if (chanHopSeq[j] > totalAccessChan) chanHopSeq[j] -= totalAccessChan;
            else chanHopSeq[j] += totalAccessChan;
        }
    }
}

void MySU::initAllStartIndexes() {
    allStartIndexes = CRmath::generateDiffRandIntDiffSeed(seqLen, 1, seqLen);
}
