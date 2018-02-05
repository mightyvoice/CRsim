//
// Created by Ji Li on 2017/9/9.
//

#ifndef CRSIM_VEC2_H
#define CRSIM_VEC2_H

#include "../global/include.h"

template<class T>
class CRvec {
private:
    /* the length of the vector */
    double getLength() {
        double ans = 0;
        ans += vec.first * vec.first + vec.second * vec.second;
        return sqrt(ans);
    };

public:
    typedef T value_type;
    pair<value_type, value_type> vec;
    double length;

    CRvec(const value_type &x, const value_type &y) {
        vec.first = x;
        vec.second = y;
        length = getLength();
    };

    CRvec(const pair<value_type, value_type> &x) {
        vec.first = x.first;
        vec.second = x.second;
        length = getLength();
    };

    CRvec(const pair<value_type, value_type> &x, const pair<value_type, value_type> &y) {
        vec.first = y.first - x.first;
        vec.second = y.second - x.second;
        length = getLength();
    };

    /* dot product of two vectors */
    value_type operator*(const CRvec<T> &y) {
        return vec.first * y.vec.first + vec.second * y.vec.second;
    };

    /* add two vectors */
    CRvec<T> operator+(const CRvec<T> &y) {
        CRvec<T> ans(vec.first + y.first, vec.second + y.second);
        return ans;
    };

    /* minus two vectors */
    CRvec<T> operator-(const CRvec<T> &y) {
        CRvec<T> ans(vec.first - y.first, vec.second - y.second);
        return ans;
    };

    /* cross product of two vectors */
    value_type operator%(const CRvec<T> &y) {
        return vec.first * y.vec.second - y.vec.first * vec.second;
    };

    /* dot product of two vectors */
    static value_type vecDotMul(const CRvec<T> &x, const CRvec<T> &y) {
        return x * y;
    };

    /* cross product of two vectors */
    static value_type vecCroMul(const CRvec<T> &x, const CRvec<T> &y) {
        return x % y;
    };

    /* add two vectors */
    static CRvec<T> vecAdd(const CRvec<T> &x, const CRvec<T> &y) {
        return x + y;
    };

    /* minus two vectors */
    static CRvec<T> vecMinus(const CRvec<T> &x, const CRvec<T> &y) {
        return x - y;
    };

    /* angles between two vectors */
    static double vecAngle(const CRvec<T> &x, const CRvec<T> &y) {
        assert(x.length > global::EPS && y.length > global::EPS);
        return acos((x * y) * 1.0 / (x.length * y.length));
    }

    static bool vecRightTurn(const CRvec<T> &x, const CRvec<T> &y) {
        return (x % y) < 0;
    };

    static bool vecLeftTurn(const CRvec<T> &x, const CRvec<T> &y) {
        return (x % y) > 0;
    };

    static bool vecSame(const CRvec<T> &x, const CRvec<T> &y) {
        return (x % y) <= global::EPS;
    };
};

#endif //CRSIM_VEC2_H
