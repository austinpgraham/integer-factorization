#ifndef UTILS_H
#define UTILS_H
#include <NTL/ZZ.h>
#include <map>
#include <iostream>

class FactorizationResult
{
private:
    std::map<NTL::ZZ, int> results;
    NTL::ZZ value;
public:
    FactorizationResult(NTL::ZZ);
    ~FactorizationResult();
    void increment_count(NTL::ZZ);
    void set_remaining(NTL::ZZ);
    bool validate();
    friend std::ostream& operator<< (std::ostream& os, const FactorizationResult&);
    NTL::ZZ remaining;
};

FactorizationResult* compute_factorization(NTL::ZZ& number);
long PrimeTest(const NTL::ZZ&, long);
#endif