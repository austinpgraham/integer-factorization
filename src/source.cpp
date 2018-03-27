#include <iostream>
#include <NTL/ZZ.h>
#include <sstream>
#include <fstream>
#include <chrono>
#include <pthread.h>
#include "ntl_utils.h"

using namespace std;
using namespace NTL;

typedef struct thread_args
{
    char group[11][4][10];
    const char *filename;
    ZZ &p;
} FactorThreadArgs;

void write_output_to_file(const char *filename, ostringstream *out_stream)
{
    ofstream out_file(filename, ofstream::app);
    out_file << (*out_stream).str();
    out_file.close();
}

void *do_factorization(void *voidArgs)
{
    FactorThreadArgs *args = (FactorThreadArgs *)voidArgs;
    const char *filename = args->filename;
    ZZ &p = args->p;
    auto start = chrono::system_clock::now();

    for (int i = 0; i < 12; i++)
    {
        ostringstream ss;

        for (int j = 0; j < 4; j++)
        {
            ss << (args->group)[i][j];
        }

        ZZ R = PowerMod(ZZ{2}, conv<ZZ>(ss.str().c_str()), p);
        ss << endl;
        FactorizationResult *result = compute_factorization(R);
        ss << *result << endl;
        ss << "Is valid: " << (result->validate(p) ? "True" : "False") << endl;
        delete result;

        write_output_to_file(filename, &ss);
    }

    auto end = chrono::system_clock::now();

    ostringstream ss;
    chrono::duration<double> elapsed_time = end - start;

    ss << elapsed_time.count() << endl;
    write_output_to_file(filename, &ss);

    return NULL;
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        cout << "Must supply output file name." << endl;
        return -1;
    }

    char *filename = argv[1];
    char *filename2 = argv[2];

    pthread_t first_search;
    pthread_t second_search;

    auto start = chrono::system_clock::now();
    cout << "Converting P value..." << endl;

    ZZ p = conv<ZZ>("179769313486231590770839156793787453197860296048756011706444423684197180216158519368947833795864925541502180565485980503646440548199239100050792877003355816639229553136239076508735759914822574862575007425302077447712589550957937778424442426617334727629299387668709205606050270810842907692932019128194467627007");
    cout<<"Starting thread 1..."<<endl;
    FactorThreadArgs first = {{{"112883788", "112887841", "112934944", "113053525"},
                               {"112883788", "113053525", "112887841", "112934944"},
                               {"112883788", "113053525", "112934944", "112887841"},
                               {"112883788", "112934944", "112887841", "113053525"},
                               {"112883788", "112934944", "113053525", "112887841"},
                               {"112934944", "112887841", "113053525", "112883788"},
                               {"112934944", "112887841", "112883788", "113053525"},
                               {"112934944", "113053525", "112887841", "112883788"},
                               {"112934944", "113053525", "112883788", "112887841"},
                               {"112934944", "112883788", "112887841", "113053525"},
                               {"112934944", "112883788", "113053525", "112887841"}}, filename, p};
    int err = pthread_create(&first_search, NULL, do_factorization, &first);
    if(err)
    {
        cout<<"First thread could not be created"<<endl;
        return -1;
    }
    cout<<"Starting thread 2..."<<endl;
    FactorThreadArgs second = {{{"112887841", "113053525", "112883788", "112934944"},
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
                                {"113053525", "112934944", "112883788", "112887841"}}, filename2, p};
    err = pthread_create(&second_search, NULL, do_factorization, &second);
    if(err)
    {
        cout<<"Second thread could not be created"<<endl;
        return -1;
    }
    cout<<"Both search threads started. Check files "<<filename<<" and "<<filename2<<" for updates."<<endl;
    pthread_join(first_search, NULL);
    pthread_join(second_search, NULL);
    do_factorization(&first);
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_time = end - start;

    cout << "Done." << endl;
    cout << "Total time: " << elapsed_time.count() << " (s)" << endl;

    return 0;
}