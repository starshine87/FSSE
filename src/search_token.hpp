#pragma once

#include "util.hpp"
using namespace std;

struct SearchToken
{
    uint64_t k_w, tau;
    SearchToken();
    SearchToken(uint64_t _k_w, uint64_t _tau) {
        k_w = _k_w;
        tau = _tau;
    }
    ~SearchToken();
};