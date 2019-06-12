#pragma once

#include "util.hpp"
#include "add_token.hpp"
#include "search_token.hpp"
using namespace std;

class Server
{
    map<uint64_t, uint64_t> PL;
public:
    Server();
    bool add(vector<AddToken> addTokens);
    vector<uint64_t> search(SearchToken searchToken);
    bool del(); // TODO
    ~Server();
};