#pragma once

#include "util.hpp"
using namespace std;

struct AddToken
{
    uint64_t loc, data, pos, data2;
    AddToken();
    AddToken(uint64_t _loc, uint64_t _data, uint64_t _pos, uint64_t _data2) {
        loc = _loc;
        data = _data;
        pos = _pos;
        data2 = _data2;
    }
    ~AddToken();
};