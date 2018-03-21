#ifndef UTILS_H
#define UTILS_H
#include <NTL/ZZ.h>
#include <map>

class FactorizationResult
{
private:
    std::map<NTL::ZZ, int> results;
    NTL::ZZ value;
    NTL::ZZ remaining;
public:
    FactorizationResult(NTL::ZZ);
    ~FactorizationResult();
    void increment_count(NTL::ZZ);
    void set_remaining(NTL::ZZ);
};

FactorizationResult* compute_factorization(NTL::ZZ& number);
#endif