/**
 *  \file haromszog.cpp
 *  Haromszog osztály tagfüggvényeinek megvalósítása
 */
#include "haromszog.h"

void Haromszog::rajzol() const
{
    std::cout << "Rajzol: " << *this << std::endl;
}

std::ostream& operator<<(std::ostream& ostr, const Haromszog& h) {
    return ostr << "Haromszog " << (Alakzat&) h << ",A=" << h.getA() << ",B=" << h.getB() << ",C=" << h.getC();
}