#include "src/util.hpp"
#include "config.h"

using namespace std;

void hashSpeedTest() {
    char input[] = "this is a test";
    unsigned char ans[65];

    struct timespec tpstart;
    struct timespec tpend;
    long timedif;

    clock_gettime(CLOCK_MONOTONIC, &tpstart);
    SHA256((unsigned char*)input, strlen(input), ans);
    // unsigned char sha_out[SHA256_DIGEST_LENGTH];
    // SHA256_CTX sha256;
    // SHA256_Init(&sha256);
    // SHA256_Update(&sha256, input, strlen(input));
    // SHA256_Final(sha_out, &sha256);
    clock_gettime(CLOCK_MONOTONIC, &tpend);
    timedif = 1000000 * (tpend.tv_sec-tpstart.tv_sec)+(tpend.tv_nsec-tpstart.tv_nsec)/1000;
    cout << "sha time:\t" << timedif << "ms" << endl;
}

int main()
{
    hashSpeedTest();
    return 0;
}

//export LIBRARY_PATH=/usr/local/Cellar/openssl/1.0.2s/lib/