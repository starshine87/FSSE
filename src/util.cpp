#include "util.h"

using namespace std;

string Util::prf_ran()
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    srand(t.tv_nsec);
    string ret = "";

    for (int i = 0; i < lambda / 16; ++i)
    {
        char c[5];
        int tmp = rand() % 65536;
        sprintf(c, "%04x", tmp);
        ret += c;
    }

    return ret;
}

string Util::prf_sha()
{
    return Util::f1_sha(to_string(0), "");
}

// ONLY SUPPORT -1~
string Util::set(int n)
{
    if (n >= 0)
    {
        string ret = "";
        char c[9];
        for (int i = 0; i < lambda / 32 - 1; ++i)
        {
            sprintf(c, "%08x", 0);
            ret += c;
        }
        sprintf(c, "%08x", n);
        return ret + c;
    }
    else {
        string ret = "";
        for (int i=0; i<lambda/4; ++i) {
            ret += "f";
        }
        return ret;
    }
}

/** 
 *  hash1, hash3, f1
 */
string Util::f1_sha(string k_w, string w)
{
    k_w += w;
    const char *input = k_w.c_str();
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(hash, &sha256);
    char output[lambda / 4 + 1];
    for (int i = 0; i < lambda / 8; ++i)
    {
        sprintf(output + 2 * i, "%02x", hash[i]);
    }
    output[lambda / 4] = 0;
    return output;
}

// f2
string Util::f2_sha(string k_s, int id)
{
    k_s += to_string(id);
    const char *input = k_s.c_str();
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(hash, &sha256);
    char output[lambda / 4 + 1];
    for (int i = 0; i < lambda / 8; ++i)
    {
        sprintf(output + 2 * i, "%02x", hash[i]);
    }
    output[lambda / 4] = 0;
    return output;
}

// h2
string Util::h2_sha(string k_w, string tau)
{
    k_w += tau;
    const char *input = k_w.c_str();
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(hash, &sha256);
    char output[lambda / 2 + 1];
    for (int i = 0; i < lambda / 4; ++i)
    {
        sprintf(output + 2 * i, "%02x", hash[i]);
    }
    output[lambda / 2] = 0;
    return output;
}

string Util::xor_string(string a, string b)
{
    for (int i = 0; i < a.length(); ++i)
    {
        a[i] = a[i] ^ b[i];
    }
    return a;
}