#include "util.hpp"

using namespace std;

// uint64_t Util::f2_sha(uint64_t k_s, int id)
// {
//     char s1[21], s2[21];
//     sprintf(s1, "%", PRIu64, id);
//     sprintf(s2, "%", PRIu64, k_s);
//     char* input = strcat(s1, s2);
//     unsigned char hash[SHA256_DIGEST_LENGTH];
//     SHA256_CTX sha256;
//     SHA256_Init(&sha256);
//     SHA256_Update(&sha256, input, strlen(input));
//     SHA256_Final(hash, &sha256);
//     char output[21];
//     for (int i=0; i<SHA256_DIGEST_LENGTH; ++i) {
//         sprintf(output)
//     }
// }