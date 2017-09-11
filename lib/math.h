//
// Created by Ji Li on 2017/9/9.
//

#ifndef CRSIM_MATH_H
#define CRSIM_MATH_H

#include "../global/include.h"
#include "vec2.h"

class CRmath {
private:
    static unsigned int randomSeed;
    static unsigned int randomSeedDiff;

    static double nChooseMnum[105][105];

public:
    /* a random integer */
    static int CRrand();

    /* a random integer, different seed each time */
    static int CRrandDiff();

    /* a random integer  from [_start, _end] */
    static int randInt(int _start, int _end);

    /* a random integer  from [_start, _end]  use different seed each time */
    static int randIntDiff(int _start, int _end);

    /* generate n different random integer from the range [st, ed] */
    static vI generateDiffRandInt(int n, int st, int ed);

    static vI generateDiffRandIntDiffSeed(int n, int st, int ed);

    /* a random number  based on the uniform distribution
        in the range [_start, _end] */
    static double randUniform(double _start, double _end);

    /* a random number  based on the exponential distribution */
    static double randExponential(double _lambda);

    /* a random number  based on the exponential distribution, different seed each time */
    static double randExponentialDiff(double _lambda);

    static int get1or0BasedOnPro(double _probability);

    /* the number of C(n, m) */
    static double nChooseM(int n, int m);

    /* choose m numbers from a vector<int> */
    static vector<vector<int>> chooseElementsFromVec(const vector<int> &a, int m);

    /* choose m numbers from [1, n] */
    static vector<vector<int> > chooseMnumbersFromN(int n, int m);

    /* binary string to a integer */
    static int binaryStringToInt(string x);

    /* transfer a integer to its binary presentation */
    static string intToBinaryString(int x);

    /* transfer a integer to its binary presentation with length n */
    static string intToBinaryString(int x, int len);

    /* right shift a binary string, higher bits fill with 0 */
    static string rightShift(const string &x, int n);

    /* circularly right shift x with shift length n */
    static string circularRightShift(const string &x, int n);

    /* circularly left shift x with shift length n */
    static string circularLeftShift(const string &x, int n);

    /* repeat a string n times */
    static string repeatString(const string &x, int n);

    /* repeat a string until a length len */
    static string repeatStringToLength(const string &x, int len);

    /* all binary strings each one has len length and n 1s */
    static vector<string> allBinaryStrWithOnes(int len, int n);

    /* get a random binary string with length: len and n ones in it */
    static string randBinaryStrWithOnes(int len, int n);

    /* suqared distance between point x and point y */

    template<class T>
    static T twoPointsDistanceSquare(T x1, T y1, T x2, T y2) {
        return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    }

    template<class T>
    static T twoPointsDistanceSquare(const pair<T, T> &x, const pair<T, T> &y) {
        return (x.first - y.first) * (x.first - y.first) + (x.second - y.second) * (x.second - y.second);
    }

    /* distance between point x and point y */
    template<class T>
    static T twoPointsDistance(const pair<T, T> &x, const pair<T, T> &y) {
        return sqrt((x.first - y.first) * (x.first - y.first) + (x.second - y.second) * (x.second - y.second));
    }

    /* If point z is inside the angle formed by line ax and line ay */
    template<class T>
    static bool pointAboveLine(const pair<T, T> &x, const pair<T, T> &y, const pair<T, T> &z) {
        CRvec<T> a(x, y);
        CRvec<T> b(x, z);
        return a % b > global::EPS;
    };

    /* If point z is above the line connected by point x and y */
    template<class T>
    static bool pointInsideAngle(const pair<T, T> a, const pair<T, T> &x, const pair<T, T> &y, const pair<T, T> &z) {
        return pointAboveLine(a, x, z) && pointAboveLine(a, z, y);
    };

};

#endif //CRSIM_MATH_H
