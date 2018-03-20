#include <iostream>
#include <NTL/ZZ.h>
#include <sstream>

using namespace std;
using namespace NTL;

char ids[6][4][9] = {{"112887841", "112934944", "112883788", "113053525"},
                      {"112887841", "112934944", "113053525", "112883788"},
                      {"112887841", "113053525", "112883788", "112934944"},
                      {"112887841", "113053525", "112934944", "112883788"},
                      {"112887841", "112883788", "112934944", "113053525"},
                      {"112887841", "112883788", "113053525", "112934944"}};



ZZ printFactorization(ZZ number) {
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
            cout<<next_prime<<" "<<count<<" times"<<endl;
        }
    }
    return number;
}

int main() {
    ZZ p = conv<ZZ>("179769313486231590770839156793787453197860296048756011706444423684197180216158519368947833795864925541502180565485980503646440548199239100050792877003355816639229553136239076508735759914822574862575007425302077447712589550957937778424442426617334727629299387668709205606050270810842907692932019128194467627007");
    for(int i = 0; i < 6; i++) {
        ostringstream ss;
        for(int j = 0; j < 4; j++) {
            ss << ids[i][j];
        }
        cout<<"Now working with "<<ss.str()<<endl;
        ZZ R = PowerMod(ZZ{2}, conv<ZZ>(ss.str().c_str()), p);
        ZZ remaining = printFactorization(R);
        cout<<NumBits(remaining)<<endl;
    }
    return 0;
}