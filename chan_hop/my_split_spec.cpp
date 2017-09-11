//
//  my_split_spec.cpp
//  CRsim
//
//  Created by Ji on 14-10-5.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "my_split_spec.h"

vector<int> divide_4m2(int x) {
    int t = x / 4;
    int q = t / 2;
    vector<int> ans;
    ans.resize(2);
    if (t % 2 == 0) {
        ans[0] = 4 * q + 1;
        ans[1] = 4 * q + 1;
    } else {
        ans[0] = 4 * (q + 1) + 1;
        ans[1] = 4 * q + 1;
    }
    return ans;
}

vector<int> divide_4m3(int x) {
    int t = x / 4;
    int q = t / 2;
    vector<int> ans;
    ans.resize(3);
    if (t % 2 == 0) {
        ans[0] = 4 * (q + 1);
        ans[1] = 4 * q + 1;
        ans[2] = 4 * q + 1;
    } else {
        ans[0] = 4 * (q + 1);
        ans[1] = 4 * (q + 1) + 1;
        ans[2] = 4 * q + 1;
    }
    return ans;
}

vector<int> divide_4m(int x) {
    int t = x / 4;
    int q = t / 2;
    vector<int> ans;
    ans.resize(2);
    if (t % 2 == 0) {
        ans[0] = 4 * q;
        ans[1] = 4 * q;
    } else {
        ans[0] = 4 * (q + 1);
        ans[1] = 4 * q;
    }
    return ans;
}

vector<int> divide_4m1(int x) {
    int t = x / 4;
    int q = t / 2;
    vector<int> ans;
    ans.resize(2);
    if (t % 2 == 0) {
        ans[0] = 4 * q;
        ans[1] = 4 * q + 1;
    } else {
        ans[0] = 4 * (q + 1);
        ans[1] = 4 * q + 1;
    }
    return ans;
}

vector<int> divide_int(int x) {
    if (x % 4 == 0) {
        return divide_4m(x);
    }
    if (x % 4 == 1) {
        return divide_4m1(x);
    }
    if (x % 4 == 2) {
        return divide_4m2(x);
    }
    if (x % 4 == 3) {
        return divide_4m3(x);
    }
    vector<int> ans;
    return ans;
}

void my_orig_split_ssl(int cur_chan_n, vI &ssl) {
    int m = cur_chan_n;
    ssl.clear();
    ssl.push_back(-1);
    queue<int> Q;
    Q.push(m);
    while (!Q.empty()) {
        int x = Q.front();
        Q.pop();
        vector<int> A = divide_int(x);
        bool flag = 1;
        for (int i = 0; i < A.size(); i++) {
            if (A[i] < global::THETA_OF_SSL) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            for (int i = 0; i < A.size(); i++) {
                Q.push(A[i]);
            }
        } else {
            ssl.push_back(x);
        }
    }
}