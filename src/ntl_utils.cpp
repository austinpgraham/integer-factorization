#include <NTL/ZZ.h>
#include <map>
#include <iterator>
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
    }
    return NULL;
}