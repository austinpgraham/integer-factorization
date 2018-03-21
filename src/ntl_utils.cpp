#include <NTL/ZZ.h>
#include <map>
#include "ntl_utils.h"

using namespace NTL;
using namespace std;

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

FactorizationResult* compute_factorization(ZZ& number) 
{
    PrimeSeq ps;
    FactorizationResult* fs = new FactorizationResult(number);
    ZZ next_prime;
    while(number != 1) {
        int count = 0;
        next_prime = ps.next();
        if(next_prime == 0)
        {
            fs->set_remaining(number);
            return fs;
        }
        while(number % next_prime == 0) {
            number /= next_prime;
            count ++;
        }
        if(count > 0) {
            fs->increment_count(next_prime);
        }
    }
    return NULL;
}