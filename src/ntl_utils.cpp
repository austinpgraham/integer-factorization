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

FactorizationResult::FactorizationResult(ZZ value)
{
    this->value = value;
}

void FactorizationResult::increment_count(ZZ key)
{
    this->results[key]++;
}

void FactorizationResult::set_remaining(ZZ remaining)
{
    this->remaining = remaining;
}

bool FactorizationResult::validate(ZZ& p)
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
    return ZZ{mult_value*this->remaining} % p == this->value;
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
    bool usePrimeSeq = true;
    long count = 0;
    while(number != 1)
    {
        if(usePrimeSeq)
        {
            next_prime = ps.next();
            if(next_prime == 0)
            {
                usePrimeSeq = false;
                count = NumBits(number);
                continue;
            }
            while(number % next_prime == 0) {
                number /= next_prime;
                // fs->increment_count(next_prime);
            }
            max_prime = next_prime;
        }
        else
        {
            // if(count == 100000)
            // {
            //     cout<<"Hit 100000"<<endl;
            //     cout<<NumBits(max_prime)<<endl;
            //     break;
            // }
            // NextPrime(max_prime, max_prime + 1);
            // while(number % max_prime == 0) {
            //     number /= max_prime;
            //     // fs->increment_count(max_prime);
            // }
            // count++;
            for(int i = 0; i < 200; i++)
            {
                long bitcount = 0;
                while(bitcount == 0)
                {
                    bitcount = RandomBnd(count);
                }
                ZZ big_prime;
                GenPrime(big_prime, bitcount);
                cout<<big_prime<<endl;
                for(int j = 0; j < 1000; j++)
                {
                    while(number % big_prime == 0) {
                        number /= big_prime;
                        cout<<big_prime<<endl;
                        count = NumBits(number);
                    } 
                    NextPrime(big_prime, big_prime + 1);  
                    if(big_prime >= number)
                    {
                        break;
                    }
                }
                cout<<i+1<<"  "<<count<<endl;
            }
            // ZZ big_prime;
            // GenPrime(big_prime, count);
            // while(number % big_prime == 0) {
            //     number /= big_prime;
            // }
            // count--;
            // if(count <= 31)
            // {
            //     break;
            // }

        }
    }
    fs->set_remaining(number);
    return fs;
}
