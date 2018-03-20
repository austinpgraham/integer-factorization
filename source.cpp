#include <iostream>
#include <NTL/ZZ.h>
#include <math.h>

using namespace std;
using namespace NTL;

const long PI = 3;

ZZ powerOfTwo(ZZ power) {
    ZZ acc = ZZ{2};
    for(int i = 0; i < power - 1; i++) {
        acc *= 2;
    }
    return acc;
}

long witness(const ZZ& n, const ZZ& x)
{
   ZZ m, y, z;
   long j, k;
   if (x == 0) return 0;
   k = 1;
   m = n/2;
   while (m % 2 == 0) {
      k++;
      m /= 2;
   }
   z = PowerMod(x, m, n);
   if (z == 1) return 0;
   j = 0;
   do {
      y = z;
      z = (y*y) % n; 
      j++;
   } while (j < k && z != 1);
   return z != 1 || y != n-1;
}

long PrimeTest(const ZZ& n, long t)
{
   if (n <= 1) return 0;
   PrimeSeq s;
   long p;
   p = s.next();
   while (p && p < 2000) {
      if ((n % p) == 0) return (n == p);
      p = s.next();  
   }
   ZZ x;
   long i;
   for (i = 0; i < t; i++) {
      x = RandomBnd(n);
      if (witness(n, x)) 
         return 0;
   }
   return 1;
}

ZZ getBigAssPrimeNumber() {
    ZZ term = powerOfTwo(ZZ{1024}) - powerOfTwo(ZZ{960}) - powerOfTwo(ZZ{64})*(powerOfTwo(ZZ{894})*PI + 129093);
    while(!PrimeTest(term, 10)) {
        term ++;
    }
    return term;
}

int main() {
    ZZ p = getBigAssPrimeNumber();
    cout<<NumBits(p)<<endl;
    return 0;
}