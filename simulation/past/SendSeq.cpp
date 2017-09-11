//
//  June061015.cpp
//  CRsim
//
//  Created by Ji on 15/6/10.
//  Copyright (c) 2015年 lj. All rights reserved.
//
#include "SendSeq.h"

void SendSeq::processbitNum(int x) {
    for (int i = 1; i < (1 << x) - 1; i++) {
        string curBinary = CRmath::intToBinaryString(i, x);
        string s1 = CRmath::repeatStringToLength(curBinary, MaxTotalLength);
        double total = 0;
        for (int j = 0; j < x; j++) {
            string rotateBinary = CRmath::circularLeftShift(curBinary, j);
            string s2 = CRmath::repeatStringToLength(rotateBinary, MaxTotalLength);
            int n1 = 0, n2 = 0;
            for (int k = 0; k < MaxTotalLength; k++) {
                if ((s1[k] - '0') || (s2[k] - '0')) {
                    n1++;
                }
                if (s1[k] - '0') {
                    n2++;
                }
                if (s2[k] - '0') {
                    n2++;
                }
            }
            total += n1 - n2;
            cout << "######################" << endl;
            cout << curBinary << "    " << rotateBinary << endl;
            cout << "num: " << x << ' ' << "Rend: " << n1 << ' ' << "RTS: " << n2 << ' ' << "Val: " << n1 * 2 - n2 * 4
                 << endl;
            cout << "######################" << endl << endl;
        }
        cout << "N: " << curBinary << "  " << "Average: " << total * 1.0 / x << endl;
    }
}

int SendSeq::getValidNumStr(const string &s, int shift) {
    string s1 = CRmath::circularLeftShift(s, shift);
    int ans = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '1' || s1[i] == '1') ans++;
    }
    return ans;
}

int SendSeq::getRtsNumStr(const string &s, int shift) {
    string s1 = CRmath::circularLeftShift(s, shift);
    int ans = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '1') ans++;
        if (s1[i] == '1') ans++;
    }
    return ans;
}

int SendSeq::getAverageValidNumStr(const string &s) {
    double ans = 0;
    int l = (int) s.length();
    for (int i = 0; i < s.length(); i++) {
        int tmp = getValidNumStr(s, i);
        ans += tmp;
    }
    cout << ans << ' ';
    ans /= 1.0 * l;
    return ans;
}

int SendSeq::getAverageRtsNumStr(const string &s) {
    double ans = 0;
    int l = (int) s.length();
    for (int i = 0; i < s.length(); i++) {
        int tmp = getRtsNumStr(s, i);
        ans += tmp;
    }
    ans /= 1.0 * l;
    return ans;
}

int SendSeq::getAverageValidNum(int len, int n) {
    string s(len, '0');
    for (int i = 0; i < n; i++) {
        s[i] = '1';
    }
    return getAverageValidNumStr(s);
}

int SendSeq::getAllRtsNum(int len, int n) {
    vector<string> s = CRmath::allBinaryStrWithOnes(len, n);
    for (auto ss: s) {
        cout << getAverageRtsNumStr(ss) << endl;
    }
    return 0;
}

void SendSeq::getAllRtsNumMaxLength(int len, int n) {
    vector<string> s = CRmath::allBinaryStrWithOnes(len, n);
    for (auto ss: s) {
        string s2 = CRmath::repeatStringToLength(ss, MaxTotalLength);
        cout << ss << ' ' << getAverageRtsNumStr(s2) << endl;
    }
}

void SendSeq::getAllEfficiency(double _ratio) {
    for (int len = 2; len <= MaxSegLength; len++) {
        int RTS = (int) round(len * _ratio);
        int rend = getAverageValidNum(len, RTS);
        cout << "Len: " << len << " RTS: " << RTS << " Rend: " << rend << " Effi: " << rend * 1.0 / RTS << endl;
    }
}

void SendSeq::getAllRendNumBasedOnRatio(double _ratio, int segLen) {
    int RTS = (int) round(segLen * _ratio);
    vector<string> s = CRmath::allBinaryStrWithOnes(segLen, RTS);
    for (auto ss: s) {
        string s1 = CRmath::repeatStringToLength(ss, MaxTotalLength);
        cout << getAverageValidNumStr(s1) << endl;
    }
}

void SendSeq::getAllRendNumBasedOnNum(int segLen, int _RTS) {
    vector<string> s = CRmath::allBinaryStrWithOnes(segLen, _RTS);
    for (auto ss: s) {
        cout << ss << ' ' << getAverageValidNumStr(ss) << endl;
    }
}

double SendSeq::getMiniRTSNum(int _totalLen, int _rend) {
    double n = _totalLen - sqrt(_totalLen * _totalLen - _totalLen * _rend);
    return ceil(n);
}


