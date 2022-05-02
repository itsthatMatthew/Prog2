/*
 * \file alaptipus.hpp
 */

#pragma once
#ifndef ALAPTIPUS_H
#define ALAPTIPUS_H

template<typename  T>
class Alaptipus
{
private:
    T adat;
public:
    Alaptipus(T valt = 0) : adat(valt) {} // constr + conv
    operator T&() { return adat; } // cast
    operator T() const { return adat; } // const cast
    T* operator&() {   return &adat; }
    const T* operator&() const {   return &adat; }
    virtual ~Alaptipus() {} // destr
}; // class Alaptipus

#endif // ALAPTIPUS_H