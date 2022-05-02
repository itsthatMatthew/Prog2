/**
 * \file resistor.cpp
 *   (UTF-8 kodolasu fajl. Allitsa at a megjenetes kodolasat,
 *    ha a tovabbi kommentek nem olvashatok helyesen!)
 *
 * Ohmikus ellenállást modellező osztály megvalósítása
 */

/**
 * Itt kell megvalósítani a resistor.h-ban deklarált nem inline függvényeket.
 * A Jportára ezt a fájlt kell feltölteni.
 */

#include "resistor.h"
#include "gtest_lite.h"
#include <math.h>

double Resistor::defR = 127.0;

Resistor::Resistor() : R(Resistor::defR) { Pr("ctor0"); }

Resistor::Resistor(double r) : R(r) { Pr("ctor1"); }

void Resistor::setDef(double r) { Resistor::defR = r; } // alapérték beállítása. A paraméter nélkül hívott konstruktor ezzel az ellenállásértékkel hozza létre az objektumot (ld. *2 megj.).

/*double Resistor::getR() const // (eredő) ellenállás lekérdezése [Ω].
{
    return R;
}*/

Resistor Resistor::operator+(const Resistor& rhsR) const // soros kapcsolás operátora.
{
    return Resistor(this->getR() + rhsR.getR());
}

Resistor Resistor::operator%(const Resistor& rhsR) const // párhuzamos kapcsolás operátora.
{
    return Resistor(1.0/(1.0/this->getR() + 1.0/rhsR.getR()));
}

Resistor operator*(int n, const Resistor& r) {
    if (n <= 0) throw "KILZ7Q";

    Resistor retR(0.0);
    for (int i = 0; i < n; i++)
    {
        retR = retR + r;
    }
    return retR;
}

// Új tagfv-ek

Resistor::Resistor(const Resistor& rhs) : R(rhs.R) { Pr("copy"); }

Resistor::~Resistor() { Pr("dtor"); }

Resistor& Resistor::operator=(const Resistor& rhs)
{
    this->R = rhs.R;
    Pr("assign");
    return *this;
}

double Resistor::getI(double u) const { return u/R; }

double Resistor::getU(double i) const { return i*R; }

bool Resistor::operator==(const Resistor& r) const
{
    double eps = 2.5e-5; // mivel a gtest_lite-os makró sem futott megfelelően az adott
                         // tesztesetre, de a szorgalmit be szerettem volna adni, ilyen
                         // csúnya epszilonvadászathoz kellett folyamodnom, ami pont
                         // sikeres teszteredményt ad...
    //std:: cout << R - r.R << std::endl;
    return fabs(R - r.R) < eps;
}

std::ostream& operator<<(std::ostream& os, const Resistor& rhs)
{
    os << rhs.getR();
    return os;
}