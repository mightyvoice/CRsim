//
// Created by Ji Li on 2017/9/9.
//

#ifndef CRSIM_INCLUDE_H
#define CRSIM_INCLUDE_H

#include <vector>
#include <utility>
#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <stack>
#include <queue>
#include <string>
#include <cstring>
#include <cmath>
#include <random>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <list>
#include <bitset>
#include <stdio.h>

#include "global.h"
#include "configure.h"

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> vI;
typedef vector<double> vD;
typedef vector<string> vS;
typedef vector<pair<int, int> > vP;
typedef pair<int, int> pI;
typedef map<int, int> mI;
typedef map<string, int> mSI;
typedef set<int> sI;
typedef set<pI> spI;
typedef priority_queue<int> qmax;
typedef priority_queue<int, vector<int>, greater<int> >qmin;
typedef map<int, int>::iterator mI_it;
typedef set<int>::iterator sI_it;

const double PI = acos(-1.0);
const int ioo = (~0)-(1<<31);
const LL loo = (~(LL)0)-((LL)1<<63);//

#endif //CRSIM_INCLUDE_H
