//
//  my_fun.h
//  CRsim
//
//  Created by Ji on 14-10-3.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#ifndef __CRsim__my_fun__
#define __CRsim__my_fun__

#include "../global/include.h"
#include "math.h"

template<class T>
void vecFromArrayIndex0(vector<T> &a, T b[], const int &n)
{
    a.resize(n+2);
    for(int i = 0; i < n; i++) a[i] = b[i];
}

template<class T>
void vecFromArrayIndex1(vector<T> &a, T b[], const int &n)
{
    a.resize(n+2);
    for(int i = 1; i <= n; i++) a[i] = b[i];
}

template<class T>
void vecFromArrayRange(vector<T> &a, T b[], const int &st, const int &n)
{
    a.resize(n+2);
    for(int i = st; i <= st+n-1; i++) a[i] = b[i];
}

template<class T>
T vecRandChoice(const vector<T> &a)
{
    return a[CRmath::randInt(0, a.size()-1)];
}

template<class T>
vector<T> getComFromTwoVector(const vector<T> &x, const vector<T> &y)
{
    vector<T> ans;
    for(int i = 0; i < x.size(); i++){
        for(int j = 0; j < y.size(); j++){
            if(x[i] == y[j]){
                ans.push_back(x[i]);
                break;
            }
        }
    }
    return ans;
}

template<class T>
double averValOfVector(const vector<T> &x)
{
    double ans = 0;
    for(int i = 0; i < x.size(); i++) ans += x[i];
    return ans/x.size();
}

template<class T>
int vectorFind(const vector<T> &a, const T &x)
{
    for(int i = 0; i < a.size(); i++){
        if(a[i] == x) return i;
    }
    return -1;
}

template<class T>
int vectorFind(const vector<T> &a, const T &x, const int &st, const int &ed)
{
    assert(st<=ed);
    assert(ed < a.size());
    for(int i = st; i <= ed; i++){
        if(a[i] == x) return i;
    }
    return -1;
}

template<class T>
int vectorSortedFind(const vector<T> &a, const T &x)
{
    if(a.size() == 0) return -1;
    int r = (int)a.size(), l = 0;
    int ans = -1;
    while(l <= r){
        int mid = (l+r)>>1;
        if(a[mid] == x){
            ans = mid;
            break;
        }
        else if(a[mid] > x){
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    return ans;
}

template<class T>
int vectorSortedFind(const vector<T> &a, const T &x, const int &st, const int &ed)
{
    if(a.size() == 0) return -1;
    assert(st<=ed);
    assert(ed < a.size());
    int r = ed, l = st;
    int ans = -1;
    while(l <= r){
        int mid = (l+r)>>1;
        if(a[mid] == x){
            ans = mid;
            break;
        }
        else if(a[mid] > x){
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    return ans;
}

template<class T>
int vectorReverseSortedFind(const vector<T> &a, const T &x)
{
    if(a.size() == 0) return -1;
    int r = (int)a.size(), l = 0;
    int ans = -1;
    while(l <= r){
        int mid = (l+r)>>1;
        if(a[mid] == x){
            ans = mid;
            break;
        }
        else if(a[mid] > x){
            l = mid + 1;
        }
        else{
            r = mid - 1;
        }
    }
    return ans;
}

template<class T>
int vectorReverseSortedFind(const vector<T> &a, const T &x, const int &st, const int &ed)
{
    if(a.size() == 0) return -1;
    assert(st<=ed);
    assert(ed < a.size());
    int r = ed, l = st;
    int ans = -1;
    while(l <= r){
        int mid = (l+r)>>1;
        if(a[mid] == x){
            ans = mid;
            break;
        }
        else if(a[mid] > x){
            l = mid + 1;
        }
        else{
            r = mid - 1;
        }
    }
    return ans;
}

template<class T>
int arraySortedFind( T a[], const T &x, const int &st, const int &ed)
{
    int r = ed, l = st;
    int ans = -1;
    while(l <= r){
        int mid = (l+r)>>1;
        if(a[mid] == x){
            ans = mid;
            break;
        }
        else if(a[mid] > x){
            r = mid - 1;
        }
        else{
            l = mid +1;
        }
    }
    return ans;
}

template<class T>
int arrayReverseSortedFind( T a[], const T &x, const int &st, const int &ed)
{
    int r = ed, l = st;
    int ans = -1;
    while(l <= r){
        int mid = (l+r)>>1;
        if(a[mid] == x){
            ans = mid;
            break;
        }
        else if(a[mid] > x){
            l = mid + 1;
        }
        else{
            r = mid - 1;
        }
    }
    return ans;
}


#endif /* defined(__CRsim__my_fun__) */
