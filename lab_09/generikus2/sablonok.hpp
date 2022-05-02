#pragma once
#ifndef _SABLONOK_HPP_
#define _SABLONOK_HPP_

#include <iostream>
#include "fancy_iterators.hpp"

#define ELKESZULT 7

template<typename ITER>
void printEach(ITER begin, ITER end, std::ostream& ostr = std::cout, const char* sep = ", ")
{
    for (ITER iter = begin; iter != end; ++iter)
    {
        if (iter != begin) ostr << sep;
        ostr << *iter;
    }
    ostr << std::endl;
}

template<typename ITER>
int szamol_ha_negativ(ITER begin, ITER end)
{
    int ret_sum = 0;
    while(begin != end)
    {
        if (*begin++ < 0) ret_sum++;
    }
    return ret_sum;
}

template<typename T>
class nagyobb_mint
{
private:
    T adat;
public:
    nagyobb_mint(T bemenet) : adat(bemenet) {}
    bool operator()(T var) { return adat < var; }
}; // nagyobb_mint

template<typename ITER, typename PRED>
int szamol_ha(ITER begin, ITER end, PRED pred)
{
    int ret_sum = 0;
    while (begin != end)
    {
        if (pred(*begin++)) ret_sum++;
    }
    return ret_sum;
}

#endif // _SABLONOK_HPP_