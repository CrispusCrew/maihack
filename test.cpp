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
#include <charconv>

const int t32 = INT_MAX-1;
const long long t64= LLONG_MAX-1;

using ll = long long;   
using ull = unsigned long long;
using ld = long double;

long double sqr(long double x) {return x * x;}

template <typename type> type tsqr(type x) {return x * x;}

template <typename T> std::ostream& operator<<(std::ostream &out, const std::vector<T> &v) {for (auto &it : v) {out << it << " ";}return out;}

using namespace std;

int main() {
    std::ifstream fin ("input copy.txt");
    std::ofstream fout ("output.txt");

    std::string str;
    fin >> str; std::cout << str;
    fin >> str; std::cout << str;
    fin >> str; std::cout << str;
    fin >> str; std::cout << str;
}