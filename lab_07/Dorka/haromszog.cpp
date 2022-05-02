/**
 *  \file haromszog.cpp
 *  Haromszog osztály tagfüggvényeinek megvalósítása
 */
#include "haromszog.h"

void Haromszog::rajzol() const {
    std::cout << "Rajzol: " << *this << std::endl;
}
std::ostream& operator<<(std::ostream& os, const Haromszog& sz) {
    return os << "Haromszog"<<  (Alakzat&) sz << "p1=" << sz.getp1() << "p2=" << sz.getp2();
}