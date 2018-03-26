#include <NTL/ZZ.h>
#include <map>
#include <iostream>
#include <iterator>
#include "ntl_utils.h"

using namespace NTL;
using namespace std;

long witness(const ZZ& n, const ZZ& x)
{
   ZZ m, y, z;
   long j, k;

   if (x == 0) return 0;

   // compute m, k such that n-1 = 2^k * m, m odd:

   k = 1;
   m = n/2;
   while (m % 2 == 0) {
      k++;
      m /= 2;
   }

   z = PowerMod(x, m, n); // z = x^m % n
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

   // first, perform trial division by primes up to 2000

   PrimeSeq s;  // a class for quickly generating primes in sequence
   long p;

   p = s.next();  // first prime is always 2
   while (p && p < 2000) {
      if ((n % p) == 0) return (n == p);
      p = s.next();  
   }

   // second, perform t Miller-Rabin tests

   ZZ x;
   long i;

   for (i = 0; i < t; i++) {
      x = RandomBnd(n); // random number between 0 and n-1

      if (witness(n, x)) 
         return 0;
   }

   return 1;
}

FactorizationResult::FactorizationResult(ZZ value)
{
    this->value = value;
}

FactorizationResult::~FactorizationResult()
{
    
}

void FactorizationResult::increment_count(ZZ key)
{
    this->results[key]++;
}

void FactorizationResult::set_remaining(ZZ remaining)
{
    this->remaining = remaining;
}

bool FactorizationResult::validate()
{
    map<ZZ, int>::iterator it;
    ZZ mult_value = ZZ{1};
    for(it = this->results.begin(); it != this->results.end(); it++)
    {
        for(int i = 0; i < it->second; i++)
        {
            mult_value *= ZZ{it->first};
        }
    }
    return (mult_value*this->remaining) == this->value;
}

ostream& operator<<(ostream& os, const FactorizationResult& fr)
{
    os<<"Working with: "<<fr.value<<endl;
    for(auto const& it: fr.results)
    {
        os<<it.first<<"^"<<it.second<<endl;
    }
    os<<"Bits of remaining: "<<NumBits(fr.remaining)<<endl;
    return os;
}

FactorizationResult* compute_factorization(ZZ& number) 
{
    PrimeSeq ps;
    FactorizationResult* fs = new FactorizationResult(number);
    ZZ max_prime;
    ZZ next_prime;
    while(number != 1) {
        next_prime = ps.next();
        if(next_prime == 0)
        {
            fs->set_remaining(number);
            return fs;
        }
        while(number % next_prime == 0) {
            number /= next_prime;
            fs->increment_count(next_prime);
        }
        max_prime = next_prime;
    }
    fs->set_remaining(number);
    return fs;
}
