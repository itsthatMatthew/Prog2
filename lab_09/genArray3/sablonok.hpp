#pragma once
#ifndef _SABLONOK_HPP_
#define _SABLONOK_HPP_

#include <iostream>
//#include "fancy_iterators.hpp"

#define ELKESZULT 17

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

/// Függvénysablon, ami kiírja egy generikus tömb adatait
/// Feltételezzük, hogy a generikus tömbnek van: 
///   - ForwardIteratora, size(), valamint capacity() tagfüggvénye
/// @param T   - sablon paraméter: iterátoros tömb típus
/// @param txt - kiírandó szöveg
/// @param arr - konkrét tömb
/// @param os  - output steram 
template <class T>
void PrintArray(const char *txt, const T& arr, std::ostream& os = std::cout) {
    os << txt << " size=" << arr.size()
         << " capacity=" << arr.capacity() << std::endl;
    os << "\t data=";
    // kiírjuk az adatokat
    
    printEach(arr.begin(), arr.end(), os, ",");
}

template <typename InputIterator, class Func>
Func forEach(InputIterator first, InputIterator last, Func func)
{
    while(first != last)
        func(*first++);
    return func;
}

template<typename T>
class ostreamFunctor
{
private:
    std::ostream& m_ostr;
    const char* m_hatar;
public:
    ostreamFunctor(std::ostream& ostr, const char* hatar) : m_ostr(ostr), m_hatar(hatar) {}
    void operator() (T var) { m_ostr << var << m_hatar; }
}; // ostreamFunctor

#endif // _SABLONOK_HPP_