#include <NTL/ZZ.h>
#include "ntl_utils.h"

using namespace NTL;

ZZ compute_factorization(ZZ& number) 
{
    PrimeSeq ps;
    ZZ next_prime;
    while(number != 1) {
        int count = 0;
        next_prime = ps.next();
        if(next_prime == 0)
        {
            return number;
        }
        while(number % next_prime == 0) {
            number /= next_prime;
            count ++;
        }
        if(count > 0) {
            // add here
        }
    }
    return number;
}