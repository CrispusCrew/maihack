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

/*struct Triangle {
    std::vector <std::pair <ld, ld>> points;// [3];
};*/

class Triangle {
public:
    std::vector <std::pair <ld, ld>> points;// [3];
    Triangle(ld f1, ld f2, ld f3, ld f4, ld f5, ld f6) {
        points.push_back(std::make_pair(f1, f2));
        points.push_back(std::make_pair(f3, f4));
        points.push_back(std::make_pair(f5, f6));
        points.push_back(std::make_pair(f1, f2));
    }
};

bool pointInsideTriangle(std::pair <ld, ld> point, Triangle triangle) {

    bool answ = false;
    for(int i = 1; i < 4; i++) { // 4 дублирует 1
        if (
            (((triangle.points[i].second <= point.second) && (point.second < triangle.points[i - 1].second)) 
            || ((triangle.points[i - 1].second <= point.second) && (point.second < triangle.points[i].second))) &&
            
            (point.first > ( triangle.points[i].first + (triangle.points[i - 1].first - triangle.points[i].first) * (point.second - triangle.points[i].second) 
            * 1.0 / (triangle.points[i - 1].second - triangle.points[i].second) ) ) 
            ) answ = !answ;
    }
    return answ;
}

bool triangleInsideTriangle(Triangle triangle, Triangle triangle2) {

    for(int i = 0; i < 3; i++) 
        if(pointInsideTriangle(triangle.points[i], triangle2))
            return true;
    for(int i = 0; i < 3; i++) 
        if(pointInsideTriangle(triangle2.points[i], triangle))
            return true;

    return false;
}

bool vectorsIntercept(std::pair <ld, ld> P1, std::pair <ld, ld> P2, // P1P2 и P3P4
                      std::pair <ld, ld> P3, std::pair <ld, ld> P4) {

    ld uB, uA = (P4.second -P3.second) * (P2.first - P1.first) - (P4.first - P3.first) * (P2.second - P1.second);
    if(uA == 0) return false; // паралелльны

    uB = (P2.first - P1.first) * (P1.second - P3.second) - (P2.second - P1.second) * (P1.first - P3.first); uB /= uA;

    uA = ((P4.first - P3.first) * (P1.second - P3.second) - (P4.second - P3.second) * (P1.first - P3.first)) / uA;

    if ( ((uA >= 0) && (uA <= 1)) && ((uB >= 0) && (uB <= 1)))
        return true;
    return false;
}

void demTriangle(Triangle triangle) {
    std::cout <<
    triangle.points[0].first << " " << triangle.points[0].second << std::endl <<
    triangle.points[0].first << " " << triangle.points[0].second << std::endl << 
    triangle.points[0].first << " " << triangle.points[0].second << std::endl << std::endl;
}

bool triangleIntercept(Triangle triangle, Triangle triangle2)  {

    std::cout << "triangle one is" << std::endl;
    demTriangle(triangle);

    std::cout << "triangle two is" << std::endl;
    demTriangle(triangle2);

    if(triangleInsideTriangle(triangle, triangle2)) return true;

    for(int i = 0; i < 3; i++) 
        for (int j = 0; j < 3; j++) 
            if(vectorsIntercept(triangle.points[i], triangle.points[i + 1], 
                             triangle2.points[j], triangle2.points[j + 1])) return true;

    return false;
}

bool collisionTest(std::vector <Triangle> first, std::vector <Triangle> second) {
    
    for(int i = 0; i < first.size(); i++)
        for(int j = 0; j < second.size(); j++)
            if(triangleIntercept(first[i], second[j])) return true;

return false;
}

void demSolve() {
    std::ifstream fin ("input2.txt");

    std::vector <Triangle> plane;
    std::vector <Triangle> port;
    ld buf, buf2; 
    ld f1, f2, f3, f4, f5, f6;

    const int PlaneParts = 4; // сколько треугольников на описание самолета
    const int PortParts = 3;

    for(int i = 0; i < PlaneParts; i++) {
        fin >> f1 >> f2 >> f3 >> f4 >> f5 >> f6;
        plane.push_back(Triangle(f1,f2,f3,f4,f5,f6));
    }

    for(int i = 0; i < PortParts; i++) {
        fin >> f1 >> f2 >> f3 >> f4 >> f5 >> f6;
        port.push_back(Triangle(f1,f2,f3,f4,f5,f6));
    }   

    for(int i = 0; i < PlaneParts; i++) {
        for (int j = 0; j < PortParts; j++) {
            if (triangleIntercept(plane[i], port[j])) {
                std::cout << "INTERCEPT DANGER" << std::endl;
                std::cout << "Plane part #" << i + 1 << std::endl;
                std::cout << "Port part #" << j + 1 << std::endl;
                fin.close(); return;
            }
        }
    }
    fin.close();
}

int main() {
    demSolve();
    //std::vector <Triangle> test;

    //collisionTest(test);


}

    /*
    
    Triangle tst, tst2;
    tst.points.push_back(std::make_pair(1,1));
    tst.points.push_back(std::make_pair(5,2));
    tst.points.push_back(std::make_pair(3,4)); 
    tst.points.push_back(std::make_pair(1,1));

    tst2.points.push_back(std::make_pair(5,5));
    tst2.points.push_back(std::make_pair(7,3));
    tst2.points.push_back(std::make_pair(2,2)); 
    tst2.points.push_back(std::make_pair(5,5));

    if(triangleIntercept(tst, tst2)) std::cout << "YEEES";
    else std::cout << "NOOOO";



    if (vectorsIntercept(std::make_pair(1,1), std::make_pair(5,2),
    std::make_pair(1,4), std::make_pair(3,4))) std::cout << "YEEES";
    else std::cout << "NOOOO";

    
    
    Triangle tst;
    tst.points.push_back(std::make_pair(1,1));
    tst.points.push_back(std::make_pair(5,2));
    tst.points.push_back(std::make_pair(3,4)); 
    tst.points.push_back(std::make_pair(1,1));
    if (pointInsideTriangle(std::make_pair(1,7), tst)) std::cout << "YEEES";
    else std::cout << "NOOOO";*/