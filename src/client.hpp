#pragma once

#include "util.hpp"
#include "server.hpp"
using namespace std;

class Client
{
    uint64_t k_s;
    map<string, uint64_t> A;

public:
    Client();
    Client(uint64_t _k_s) {
        k_s = _k_s;
    }
    bool add(const int id, const vector<string> db, Server server);
    vector<uint64_t> search(const string keyword, Server server);
    bool del(const int id, Server server);
    uint64_t getKey() {
        return k_s;
    }
    ~Client();
};