/**
 * \file: hetero_store.hpp
 *
 */

#ifndef HETEROSTORE_HPP
#define HETEROSTORE_HPP

#include <iostream>
#include <stdexcept>

template<class T, size_t meret = 100, class except = std::out_of_range>
class HeteroStore
{
private:
    size_t db;
    T* arr[meret];
public:
    HeteroStore() : db(0) {}
    ~HeteroStore() { clear(); }
    size_t size(void) const { return db; }
    size_t capacity(void) const { return meret; }
    void add(T* p)
    {
        if (db == meret)
        {
            delete p;
            throw except("Nincs hely");
        }
        arr[db++] = p;
    }
    template<typename F>
    void traverse(F func) { for (size_t i = 0; i < db; i++) func(arr[i]); }
    void clear(void) { for (size_t i = 0; i < db; i ++) delete arr[i]; db = 0; }
}; // class HeteroStore

#endif // HETEROSTORE_HPP
