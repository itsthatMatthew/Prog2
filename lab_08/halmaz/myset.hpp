/**
 * @file myset.hpp
 */
#pragma once
#ifndef MYSET_HPP
#define MYSET_HPP

#include "point.h"

#define ELKESZULT 4

inline bool operator == (const Point& bal_P, const Point& jobb_P)
{ return bal_P.getX() == jobb_P.getX() && bal_P.getY() == jobb_P.getY(); }

template<typename T>
inline bool equal(const T& bal, const T& jobb) { return bal == jobb; }

template<>
inline bool equal<Point>(const Point& bal_P, const Point& jobb_P)
{ return bal_P.getX() == jobb_P.getX(); }

template<typename T, size_t maxMeret = 10>
class Set
{
private:
    size_t db;
    T arr[maxMeret];
public:
    Set() : db(0) {}
    virtual ~Set() {}

    size_t size(void) const { return db; }
    bool isElement(T elem)
    {
        for (size_t i = 0; i < db; i++)
            if (equal(arr[i], elem)) return true;
        return false;
    }
    void insert(T elem)
    {
        if (db == maxMeret) throw "Nincs hely!";
        if (!isElement(elem))
        {
            arr[db++] = elem;
        }
    }
}; // class Set

#endif // MYSET_HPP