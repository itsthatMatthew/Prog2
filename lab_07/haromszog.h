/**
 *  \file haromszog.h
 *  Haromszog osztály deklarációja
 */
#ifndef HAROMSZOG_H
#define HAROMSZOG_H

#include "alakzat.h"

/// Ügyeljen arra, hogy a csúcspontokat az alaposztály orgiójához relatívan tárolja!
class Haromszog : public Alakzat
{
private:
    Pont m_A, m_B, m_C; // offset
public:
    Haromszog(const Pont& a, const Pont& b, const Pont& c, const Szin& sz)
    : Alakzat(Pont((a.x+b.x+c.x)/3,(a.y+b.y+c.y)/3), sz), m_A(a-getp0()), m_B(b-getp0()), m_C(c-getp0()) {}

    Pont getA() const { return m_A+getp0(); }
    Pont getB() const { return m_B+getp0(); }
    Pont getC() const { return m_C+getp0(); }

    void rajzol() const;
};

std::ostream& operator<<(std::ostream&, const Haromszog&);

#endif // KOR_H

