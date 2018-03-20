#include <iostream>
#include <NTL/ZZ.h>
#include <math.h>

using namespace std;
using namespace NTL;

const long PI = 3;

ZZ powerOfTwo(ZZ power) {
    ZZ acc = ZZ{2};
    for(int i = 0; i < power; i++) {
        acc *= 2;
    }
    return acc;
}

ZZ getBigAssPrimeNumber() {
    ZZ term = powerOfTwo(ZZ{1024}) - powerOfTwo(ZZ{960}) + powerOfTwo(ZZ{64});
    term *= (powerOfTwo(ZZ{894})*PI + 129093);
    return term;
}

int main() {
    ZZ p = getBigAssPrimeNumber();
    cout<<p<<endl;
    return 0;
}