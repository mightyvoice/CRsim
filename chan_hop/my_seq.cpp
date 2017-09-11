//
//  my_seq.cpp
//  CRsim
//
//  Created by Ji on 14-10-3.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "my_seq.h"

MyHop::MyHop(int _st_time) : ChanHop() {
    init_seq();
    startHopTime = _st_time;
    sequenceLen = 2 * M;
    startIndex = CRmath::randIntDiff(1, sequenceLen);
    curRoundStartIndex = startIndex;
}

MyHop::MyHop(int cur_chan_n, int _st_time) : ChanHop(cur_chan_n) {
    startHopTime = _st_time;
    init_seq();
    sequenceLen = 2 * M;
    startIndex = CRmath::randIntDiff(1, sequenceLen);
    curRoundStartIndex = startIndex;
}

MyHop::MyHop(int cur_chan_n, int _st_time, vI &avai) : ChanHop(cur_chan_n) {
    startHopTime = _st_time;
    this->avai_chan = avai;
    init_seq();
    sequenceLen = 2 * M;
    startIndex = CRmath::randIntDiff(1, sequenceLen);
    curRoundStartIndex = startIndex;
}

vector<pI> generate_4m_pairs(int x) {
    vector<pI> n_pair;
    int m = x / 4;
    for (int r = 0; r < 2 * m; r++) {
        n_pair.push_back(make_pair(4 * m + r, 8 * m - r));
    }
    n_pair.push_back(make_pair(2 * m + 1, 6 * m));
    n_pair.push_back(make_pair(2 * m, 4 * m - 1));
    for (int r = 1; r < m; r++) {
        n_pair.push_back(make_pair(r, 4 * m - 1 - r));
    }
    n_pair.push_back(make_pair(m, m + 1));
    for (int r = 0; r < m - 2; r++) {
        n_pair.push_back(make_pair(m + 2 + r, 3 * m - 1 - r));
    }
    return n_pair;
}

vector<pI> generate_4m1_pairs(int x) {
    vector<pI> n_pair;
    int m = x / 4;
    for (int r = 0; r < 2 * m; r++) {
        n_pair.push_back(make_pair(4 * m + r + 2, 8 * m + 2 - r));
    }
    n_pair.push_back(make_pair(2 * m + 1, 6 * m + 2));
    n_pair.push_back(make_pair(2 * m + 2, 4 * m + 1));
    for (int r = 1; r < m + 1; r++) {
        n_pair.push_back(make_pair(r, 4 * m + 1 - r));
    }
    n_pair.push_back(make_pair(m + 1, m + 2));
    for (int r = 1; r < m - 1; r++) {
        n_pair.push_back(make_pair(m + 2 + r, 3 * m + 1 - r));
    }
    return n_pair;
}

void MyHop::init_seq() {
    hopSequence.clear();
    if (M == 0 || M % 4 == 2 || M % 4 == 3) {
        return;
    }
    if (M == 4) {
        int b[9] = {0, 1, 1, 4, 2, 3, 2, 4, 3};
        hopSequence.resize(10);
        vecFromArrayIndex1(hopSequence, b, 8);
        return;
    }
    hopSequence.resize(2 * M + 1);
    vector<pI> n_pairs;
    if (M % 4 == 0) {
        n_pairs = generate_4m_pairs(M);
    }
    if (M % 4 == 1) {
        n_pairs = generate_4m1_pairs(M);
    }
    for (int i = 0; i < n_pairs.size(); i++) {
        hopSequence[n_pairs[i].first] = n_pairs[i].second - n_pairs[i].first;
        hopSequence[n_pairs[i].second] = n_pairs[i].second - n_pairs[i].first;
    }
}

int MyHop::getChanAtTimeT(int t) {
    int l = sequenceLen;
    roundCount = (t - startHopTime) / l;
    curRoundStartIndex = startIndex + roundCount;
    if (curRoundStartIndex % l == 0) curRoundStartIndex = l;
    else curRoundStartIndex = curRoundStartIndex % l;
    int rnd_st_t = startHopTime + roundCount * l;
    int cur = curRoundStartIndex + t - rnd_st_t;
    if (cur % l == 0) cur = l;
    else cur = cur % l;
    curChan = hopSequence[cur];
    return curChan;
}

int MyHop::getChanAtTimeT(int t, const vI &avai) {
    curChan = getChanAtTimeT(t);
    if (!vectorFind(avai, curChan)) {
        curChan = avai[CRmath::randIntDiff(0, (int) avai.size() - 1)];
    }
    return curChan;
}

int MyHop::getChanAtTimeTBeforeReplace(int t) {
    return getChanAtTimeT(t);
}

void MyHop::resetChanHop() {
    return;
}
