#pragma once

#include "util.hpp"
using namespace std;

struct AddToken
{
    string loc, data, pos, data2;
    AddToken();
    AddToken(string _loc, string _data, string _pos, string _data2) {
        loc = _loc;
        data = _data;
        pos = _pos;
        data2 = _data2;
    }
    ~AddToken();
};