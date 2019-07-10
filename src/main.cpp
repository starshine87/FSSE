#include <fstream>
#include <string>
#include <map>
#include <set>

#include "util.h"
#include "server.h"
#include "client.h"

using namespace std;

void hashSpeedTest()
{
    char input[] = "this is a test";
    unsigned char ans[65];

    struct timespec tpstart;
    struct timespec tpend;
    long timedif;
    clock_gettime(CLOCK_MONOTONIC, &tpstart);
    for (int i = 0; i < 10000000; ++i)
    {
        SHA256((unsigned char *)input, strlen(input), ans);
        unsigned char sha_out[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, input, strlen(input));
        SHA256_Final(sha_out, &sha256);
    }
    clock_gettime(CLOCK_MONOTONIC, &tpend);
    timedif = 1000000 * (tpend.tv_sec - tpstart.tv_sec) + (tpend.tv_nsec - tpstart.tv_nsec) / 1000;
    cout << "sha time:\t" << (double)timedif/10000000 << "us" << endl;

    clock_gettime(CLOCK_MONOTONIC, &tpstart);
    for (int i=0; i<10000000; ++i) {
        Util::f2_sha(input, i);
    }
    clock_gettime(CLOCK_MONOTONIC, &tpend);
    timedif = 1000000 * (tpend.tv_sec - tpstart.tv_sec) + (tpend.tv_nsec - tpstart.tv_nsec) / 1000;
    cout << "f2 time:\t" << (double)timedif/10000000 << "us" << endl;
    return;
}

void prf_test()
{
    struct timespec tpstart;
    struct timespec tpend;
    long timedif;
    clock_gettime(CLOCK_MONOTONIC, &tpstart);
    for (int i=0; i<10000000; ++i) {
        Util::prf_ran();
    }
    clock_gettime(CLOCK_MONOTONIC, &tpend);
    timedif = 1000000 * (tpend.tv_sec - tpstart.tv_sec) + (tpend.tv_nsec - tpstart.tv_nsec) / 1000;
    cout << "random time: \t" << (double)timedif/10000000 << "us" << endl;

    clock_gettime(CLOCK_MONOTONIC, &tpstart);
    for (int i=0; i<10000000; ++i) {
        Util::prf_sha();
    }
    clock_gettime(CLOCK_MONOTONIC, &tpend);
    timedif = 1000000 * (tpend.tv_sec - tpstart.tv_sec) + (tpend.tv_nsec - tpstart.tv_nsec) / 1000;
    cout << "hash time: \t" << (double)timedif/10000000 << "us" << endl;
    return;
}

void enron_test(int n)
{
    struct timespec tpstart;
    struct timespec tpend;
    long timedif = 0;
    Server s;
    //Client c(Util::f1_sha(Util::prf_ran(), Util::prf_ran()));
    Client c("74c3ada59cb43d55");
    int pairs = 0;
    string folder = "../data/enron-extract/";
    for (int i=1; i<=n; ++i) {
        ifstream fin(folder + to_string(i) + ".txt");
        set<string> keywords;
        while (!fin.eof()) {
            ++pairs;
            string w;
            getline(fin, w);
            keywords.insert(w);
        }
        clock_gettime(CLOCK_MONOTONIC, &tpstart);
        c.add(i, keywords, &s);
        clock_gettime(CLOCK_MONOTONIC, &tpend);
        timedif += 1000000 * (tpend.tv_sec - tpstart.tv_sec) + (tpend.tv_nsec - tpstart.tv_nsec) / 1000;
        keywords.clear();
        fin.close();
    }
    ofstream fout("result_"+to_string(n)+".txt");
    fout << "# of files: \t" << n << endl;
    fout << "# of pairs: \t" << pairs << endl;
    fout << "init time: \t" << (double)timedif/1000 << "ms" << endl;
    timedif = 0;
    pairs = 0;
    for (int i=0; i<100; ++i) {
        clock_gettime(CLOCK_MONOTONIC, &tpstart);
        vector<string> result = c.search("Path\r", &s);
        clock_gettime(CLOCK_MONOTONIC, &tpend);
        timedif += 1000000 * (tpend.tv_sec - tpstart.tv_sec) + (tpend.tv_nsec - tpstart.tv_nsec) / 1000;
        pairs += result.size();
    }
    fout << "# of search pairs: \t" << pairs << endl;
    fout << "search time: \t" << (double)timedif/1000/100 << "ms" << endl;
//    for (int i=0; i<result.size(); ++i) {
//        cout << result[i] << endl;
//    }
    fout.close();
    return;
}

void map_test()
{
    map<string, string> test;
    test["Notification\r"] = "1345tqsrgewrbasd";
    cout << test["Notification\r"] << endl;
}

int main()
{
    //hashSpeedTest();
    //Server s;

    //s.add(vector<AddToken>());
    //enron_test(10000);
    enron_test(100000);
    //enron_test(255636);
    //map_test();
    return 0;
}

//export LIBRARY_PATH=/usr/local/Cellar/openssl/1.0.2s/lib/