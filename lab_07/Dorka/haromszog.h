/**
 *  \file haromszog.h
 *  Haromszog osztály deklarációja
 */
#ifndef HAROMSZOG_H
#define HAROMSZOG_H

 #include "alakzat.h"
 #include <iostream>
/// Ügyeljen arra, hogy a csúcspontokat az alaposztály orgiójához relatívan tárolja!
class Haromszog :public Alakzat{
    Pont p1;
    Pont p2; 
public:
    Haromszog(const Pont& P0, const Pont& P1, const Pont& P2, const Szin& Sz): Alakzat(P0, Sz), p1(P1), p2(P2){}
    void rajzol() const; 
    
    Pont getp1() const{
        return p1;
    }
    Pont getp2() const{
        return p2;
    }
};
std::ostream& operator<<(std::ostream& os,Haromszog& sz);

#endif // KOR_H

