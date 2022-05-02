/**
 * A vektor.h fejlécfájlban megadott osztály kidolgozása
 * Azon metódusokat tartalmazza, melyek a fejlécfájlban csak definiálva lettek.
 * (Bővebben kommentelt, tisztább olvashatóság érdekében.)
 */

#include "vektor.h"

size_t Vektor::defSize = 7;     // Alapértelmezett vektorméret
double Vektor::defValue = 27;   // Alapértelmezett kezdőérték

/// Vektor osztály másoló konstruktora. Dinamikusan foglal memóriát.
Vektor::Vektor(const Vektor& other)
: nElements(other.nElements)                // Elemszámot átveszi,
{
    this->pVec = new double[nElements];     // majd elegendő memóriát foglal,
    for (size_t i = 0; i < nElements; i++)  // ezt pedig feltölti
        this->pVec[i] = other.pVec[i];      // a "másik" értékeivel.
}

/// Vektor osztály destruktora. Felszabadítja a pVec mögött foglalt memóriát.
Vektor::~Vektor()
{
    delete[] this->pVec;    // Felszabadítja a mutató mögötti memóriaterületet.
}      // ^~ delete[] operátor, mert a foglalásnál tömbnek tettük meg.

/// Értékadó operátor (nem inicializálásnál történő értékadáshoz).
Vektor& Vektor::operator=(const Vektor& rhs_V)
{
    if (this != &rhs_V)                     // Ha önmagát kapja, vissza is tér.
    {                                           // Ha nem:
    delete[] this->pVec;                    // Az eddigi memóriát felszabadítja,
    this->nElements = rhs_V.nElements;      // elemszámot átveszi,
    this->pVec = new double[nElements];     // az újnak elegendő memóriát foglal,
    for (size_t i = 0; i < nElements; i++)  // ezt pedig feltölti
        this->pVec[i] = rhs_V.pVec[i];      // a jobb oldali Vektor értékeivel.
    }
    return *this;                           // Végül visszatér a referenciával.
}

/// Index operátor (mivel pVec privát, de az adatokat el szeretnénk érni).
double& Vektor::operator[](size_t idx)
{        // ,~ kihasználjuk, hogy unsigned.
    if (idx >= this->nElements) // Ha túlcímzés történik,
        throw "KILZ7Q";             // kivételt dob.
    return this->pVec[idx];     // Visszatér a megfelelő elem referenciájával.
}

/// Index operátor konstans értékekre túlterhelt változata.
const double& Vektor::operator[](size_t idx) const
{        // ,~ kihasználjuk, hogy unsigned.
    if (idx >= this->nElements) // Ha túlcímzés történik,
        throw "KILZ7Q";             // kivételt dob.
    return this->pVec[idx];     // Visszatér a megfelelő elem konstans referenciájával.
}

/// Szrozás operátor valós * Vektor értékekre.
Vektor operator*(double val, const Vektor& vec)
{
    Vektor ret_V(vec.size());   // "Visszatérő" vektor a paraméter méretével inicializálva.

    for (size_t i = 0; i < vec.size(); i++) // Minden egyes elemre
        ret_V[i] = vec[i] * val;            // végezze el a szorzást,
    return ret_V;                           // majd térjen vissza az így kapott vektorral.
}