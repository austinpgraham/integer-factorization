#include <iostream>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

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

void printFactorization(ZZ number) {
    PrimeSeq ps;
    ZZ next_prime;
    while(number != 1) {
        int count = 0;
        next_prime = ps.next();
        while(number % next_prime == 0) {
            number /= next_prime;
            count ++;
        }
        if(count > 0) {
            cout<<next_prime<<" "<<count<<" times"<<endl;
        }
    }
}

int main() {
    ZZ p = conv<ZZ>("179769313486231590770839156793787453197860296048756011706444423684197180216158519368947833795864925541502180565485980503646440548199239100050792877003355816639229553136239076508735759914822574862575007425302077447712589550957937778424442426617334727629299387668709205606050270810842907692932019128194467627007");
    ZZ R = PowerMod(ZZ{2}, conv<ZZ>("112887841112934944112883788113053525"), p);
    return 0;
}