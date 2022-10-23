#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <ostream>
#include <fstream>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <bitset>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <array>
#include <algorithm>
#include <functional>
#include <cmath>
#include <time.h>
#include <random>
#include <chrono>
#include <cassert>
#include <cstring>
#include <climits>
#include <stdexcept>

const int t32 = INT_MAX-1;
const long long t64= LLONG_MAX-1;

using ll = long long;   
using ull = unsigned long long;
using ld = long double;

long double sqr(long double x) {return x * x;}

struct MathVec {
    std::pair <ld,ld> start;
    std::pair <ld,ld> finish;
    std::pair <ld,ld> coord;
};

bool collision(std::vector <MathVec> &first, std::vector <MathVec> &second) {

    MathVec A; int k = 1, i; ld L, s;
    ld minA, maxA;

imSoSorry:

    A.coord.first = first[k].start.second - first[k].finish.second;
    A.coord.second = first[k].finish.first - first[k].start.first;

    L = sqrtl(sqr(A.coord.first) + sqr(A.coord.second));
    A.coord.first /= L;
    A.coord.second /= L;

    s = first[k].start.first * A.coord.first + first[k].start.second * A.coord.second; 
    minA = s, maxA = s;

    for(i = 1; i < first.size(); i++) {
        s = first[i].start.first * A.coord.first + first[i].start.second * A.coord.second;
        if (s < minA) minA = s;
        if (s > maxA) maxA = s;
    }

    s = second[k].start.first * A.coord.first + second[k].start.second * A.coord.second; 
    ld minB = s, maxB = s;

    for(i = 1; i < second.size(); i++) {
        s = second[i].start.first * A.coord.first + second[i].start.second * A.coord.second;
        if (s < minB) minB = s;
        if (s > maxB) maxB = s;
    }

    ld I;
    if (minA < minB) I = minB - maxA;
    else I = minA - maxB;

    if(I <= 0) return true;
    
    ++k;
    if( k < first.size() ) goto imSoSorry;

    return false;
} 

void collisionTest () {
    int sizeF, sizeS, i; ld x,y;
    std::vector <MathVec> first, second, final;
    std::ifstream fin ("inputN.txt");
    std::ofstream fout ("output.txt");

    fin >> sizeF;
    first.resize(sizeF);
    for(i = 0; i < (sizeF - 1); i++) {
        fin >> x >> y;

        first[i].finish.first = x;
        first[i].finish.second = y;

        first[i + 1].start.first = x;
        first[i + 1].start.second = y;
    }

    fin >> x >> y; i++;
    first[i].finish.first = x;
    first[i].finish.second = y;
    first[0].start.first = x;
    first[0].start.second = y;

    for(i = 0; i < sizeF; i++) {
        fout << "i = " << i << std::endl;
        fout << "start\t" << first[i].start.first << " " << first[i].start.second << std::endl;
        fout << "finish\t" << first[i].finish.first << " " << first[i].finish.second << std::endl << std::endl;
    }

    fin >> sizeS;
    second.resize(sizeS);
    for(i = 0; i < (sizeS - 1); i++) {
        fin >> x >> y;

        second[i].finish.first = x;
        second[i].finish.second = y;

        second[i + 1].start.first = x;
        second[i + 1].start.second = y;
    }

    fin >> x >> y; i++;
    second[i].finish.first = x;
    second[i].finish.second = y;
    second[0].start.first = x;
    second[0].start.second = y;

    if(collision(first, second)) fout << "Collision detected" << std::endl;
    else fout << "Collision not detected" << std::endl;
}

int main() {
    collisionTest();
}