#include <iostream>
#include <NTL/ZZ.h>

using namespace std;

int main()
{
    NTL::ZZ my_num;
    GenPrime(my_num, 850, 80);
    cout<<my_num<<endl;
    cout<<NumBits(my_num)<<endl;
    return 0;
}