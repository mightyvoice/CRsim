//
//  my_math.cpp
//  CRsim
//
//  Created by Ji on 14-10-4.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "math.h"
#include "debug.h"

unsigned int CRmath::randomSeed = (int) 100;

unsigned int CRmath::randomSeedDiff = (int) time(0);

int CRmath::CRrand() {
    srand(randomSeed);
    int tmp = rand();
    randomSeed += 2229; //a good number I choose
    return tmp;
}

int CRmath::CRrandDiff() {
    srand(randomSeedDiff);
    int tmp = 0;
    int t = 100;
    int t1 = rand() % t;
    for (int i = 0; i < t; i++) {
        tmp = rand();
        randomSeedDiff += tmp + (int) time(0);
        if (i == t1) break;
    }
    return tmp;
}

int CRmath::randIntDiff(int _start, int _end) {
    assert(_start <= _end);
    int len = _end - _start + 1;
    int ans = CRrandDiff() % len;
    return _start + ans;
}

int CRmath::randInt(int _start, int _end) {
    assert(_start <= _end);
    int len = _end - _start + 1;
    int ans = CRrand() % len;
    return _start + ans;
}

vI CRmath::generateDiffRandInt(int n, int st, int ed) {
    vI ans;
    set<int> s;
    //    cout<<st<<' '<<ed<<endl;
    while (s.size() < n) {
        int tmp = CRmath::randInt(st, ed);
        if (s.find(tmp) == s.end()) {
            s.insert(tmp);
        }
    }
    for (auto it = s.begin(); it != s.end(); it++) {
        ans.push_back(*it);
    }
    return ans;
}

vI CRmath::generateDiffRandIntDiffSeed(int n, int st, int ed) {
    assert(st <= ed);
    vI ans;
    set<int> s;
    //    cout<<st<<' '<<ed<<endl;
    while (s.size() < n) {
        int tmp = CRmath::randIntDiff(st, ed);
        if (s.find(tmp) == s.end()) {
            s.insert(tmp);
        }
    }
    for (auto it = s.begin(); it != s.end(); it++) {
        ans.push_back(*it);
    }
    return ans;

}

double CRmath::randExponential(double _lambda) {
    assert(_lambda > global::EPS);
    if (_lambda <= global::EPS) return global::INT_MAX_VAL;
    double u = 0.0;
    while (1) {
        u = (double) CRrand() / (double) RAND_MAX;
        if (1.0 - u >= 1e-6) {
            break;
        }
    }
    u = (-1.0 / _lambda) * log(1.0 - u);
    return u;
}

double CRmath::randExponentialDiff(double _lambda) {
    assert(_lambda > global::EPS);
    if (_lambda <= global::EPS) return global::INT_MAX_VAL;
    double u = 0.0;
    while (1) {
        u = (double) CRrandDiff() / (double) RAND_MAX;
        if (1.0 - u >= 1e-6) {
            break;
        }
    }
    u = (-1.0 / _lambda) * log(1.0 - u);
    return u;
}

double CRmath::nChooseMnum[105][105] = {0};

double CRmath::nChooseM(int n, int m) {
    if (n < 0 || m < 0) return 0;
    if (m > n) return 0;
    if (m == 0 || n == m) return 1;
    if (m == 1) return n;
    if (nChooseMnum[n][m] > global::EPS) return nChooseMnum[n][m];
    nChooseMnum[n][m] = nChooseM(n - 1, m) + nChooseM(n - 1, m - 1);
    return nChooseMnum[n][m];
}

int CRmath::binaryStringToInt(string x) {
    int ans = 0;
    for (int i = 0; i < x.length(); i++) {
        if (x[i] == '0') {
            ans += 1 << (i);
        }
    }
    return ans;
}

string CRmath::rightShift(const string &x, int n) {
    string tmp(x.length(), '0');
    for (int i = 0; i < x.length(); i++) {
        int cur = i + n;
        if (cur >= x.length()) cur -= x.length();
        tmp[cur] = x[i];
    }
    return tmp;
}

string CRmath::intToBinaryString(int x, int len) {
    string ans(len, '0');
    while (x > 0) {
        int tmp = x % 2;
        ans[--len] = (char) (tmp + '0');
        x >>= 1;
    }
    return ans;
}

string CRmath::circularLeftShift(const string &x, int n) {
    int l = (int) x.length();
    string ans = x;
    for (int i = 0; i < l; i++) {
        int j = (i - n + l) % l;
        ans[j] = x[i];
    }
    return ans;
}

string CRmath::circularRightShift(const string &x, int n) {
    int l = (int) x.length();
    string ans = x;
    for (int i = 0; i < l; i++) {
        int j = (i + n) % l;
        ans[j] = x[i];
    }
    return ans;
}

string CRmath::repeatString(const string &x, int n) {
    string ans = x;
    for (int i = 1; i < n; i++) {
        ans += x;
    }
    return ans;
}

string CRmath::repeatStringToLength(const string &x, int len) {
    int l = (int) x.length();
    if (len <= l) return x.substr(0, len);
    string ans(len, '0');
    for (int i = 0; i < len; i++) {
        ans[i] = x[i % l];
    }
    return ans;
}

vector<vector<int> > CRmath::chooseElementsFromVec(const vector<int> &a, int m) {
    assert(a.size() >= m);
    vector<vector<int> > ans;
    if (m == 0) return ans;
    if (m == 1) {
        for (auto x: a) {
            vector<int> tmp(1, x);
            ans.push_back(tmp);
        }
        return ans;
    }
    if (m == a.size()) {
        ans.push_back(a);
        return ans;
    }
    int n = (int) a.size();
    vector<vector<int> > tmp;
    vector<int> b;
    for (int i = 0; i < n - 1; i++) {
        b.push_back(a[i]);
    }
    tmp = chooseElementsFromVec(b, m - 1);
    for (int i = 0; i < tmp.size(); i++) {
        tmp[i].push_back(a[n - 1]);
        ans.push_back(tmp[i]);
    }
    tmp = chooseElementsFromVec(b, m);
    for (auto x: tmp) {
        ans.push_back(x);
    }
    return ans;
}

vector<vector<int> > CRmath::chooseMnumbersFromN(int n, int m) {
    assert(n >= m);
    vector<int> a;
    for (int i = 1; i <= n; i++) a.push_back(i);
    return chooseElementsFromVec(a, m);
}

vector<string> CRmath::allBinaryStrWithOnes(int len, int n) {
    assert(len >= n);
    vector<string> ans;
    vector<vector<int> > a = chooseMnumbersFromN(len, n);
    for (auto x: a) {
        string s(len, '0');
        for (auto y: x) {
            s[y - 1] = '1';
        }
        ans.push_back(s);
    }
    return ans;
}

string CRmath::randBinaryStrWithOnes(int len, int n) {
    assert(len > 0);
    string ans(len, '0');
    vI tmp = generateDiffRandIntDiffSeed(n, 0, len - 1);
    for (auto x: tmp) {
        ans[x] = '1';
    }
    return ans;
}

int CRmath::get1or0BasedOnPro(double _probability) {
    assert(_probability >= global::EPS && _probability <= 1 + global::EPS);
    int r = 1000000;
    int s = (int) (r * _probability);
    int t = randIntDiff(1, r);
    if (t < s) return 1;
    else return 0;
}
