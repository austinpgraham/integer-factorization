#include <iostream>
#include <NTL/ZZ.h>
#include <sstream>
#include <fstream>
#include <chrono>
#include "ntl_utils.h"

using namespace std;
using namespace NTL;

char ids[24][4][10] = {
    {"112887841", "113053525", "112883788", "112934944"},
    {"112887841", "113053525", "112934944", "112883788"},
    {"112887841", "112883788", "113053525", "112934944"},
    {"112887841", "112883788", "112934944", "113053525"},
    {"112887841", "112934944", "113053525", "112883788"},
    {"112887841", "112934944", "112883788", "113053525"},
    {"113053525", "112887841", "112883788", "112934944"},
    {"113053525", "112887841", "112934944", "112883788"},
    {"113053525", "112883788", "112887841", "112934944"},
    {"113053525", "112883788", "112934944", "112887841"},
    {"113053525", "112934944", "112887841", "112883788"},
    {"113053525", "112934944", "112883788", "112887841"},
    {"112883788", "112887841", "113053525", "112934944"},
    {"112883788", "112887841", "112934944", "113053525"},
    {"112883788", "113053525", "112887841", "112934944"},
    {"112883788", "113053525", "112934944", "112887841"},
    {"112883788", "112934944", "112887841", "113053525"},
    {"112883788", "112934944", "113053525", "112887841"},
    {"112934944", "112887841", "113053525", "112883788"},
    {"112934944", "112887841", "112883788", "113053525"},
    {"112934944", "113053525", "112887841", "112883788"},
    {"112934944", "113053525", "112883788", "112887841"},
    {"112934944", "112883788", "112887841", "113053525"},
    {"112934944", "112883788", "113053525", "112887841"}
};


void write_output_to_file(const char* filename, ostringstream* out_stream)
{
    ofstream out_file(filename, ofstream::app);
    out_file << (*out_stream).str();
    out_file.close();
}

int main(int argc, char** argv) {
    if (argc < 2)
    {
        cout<<"Must supply output file name."<<endl;
        return -1;
    }
    char* filename = argv[1];
    ZZ p = conv<ZZ>("179769313486231590770839156793787453197860296048756011706444423684197180216158519368947833795864925541502180565485980503646440548199239100050792877003355816639229553136239076508735759914822574862575007425302077447712589550957937778424442426617334727629299387668709205606050270810842907692932019128194467627007");
    auto start = chrono::system_clock::now();
    for(int i = 0; i < 24; i++) {
        ostringstream ss;
        for(int j = 0; j < 4; j++) {
            ss << ids[i][j];
        }
        ZZ R = PowerMod(ZZ{2}, conv<ZZ>(ss.str().c_str()), p);
        ss << endl;
        FactorizationResult* result = compute_factorization(R);
        ss<<*result<<endl;
        cout<<*result<<endl;
        delete result;
        write_output_to_file(filename, &ss);
    }
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    cout<<"Total elapsed time: "<<elapsed_time.count()<<" (s)"<<endl;
    ostringstream ss;
    ss<<"Total elapsed time: "<<elapsed_time.count()<<" (s)"<<endl;
    write_output_to_file(filename, &ss);
    return 0;
}