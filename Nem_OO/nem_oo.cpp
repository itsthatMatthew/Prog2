#include <cstring>
#include <cctype>
#include "nem_oo.h"

/**
 * \file nem_oo_teszt.cpp
 * (UTF-8 kodolasu fajl. Allitsa at a kodolast,
 *  ha a tovabbi kommentek nem olvashatok helyesen!)
 *
 * FELADATOK:
 *  1. Ebben a fájlban valósítsa meg a nem_oo.h állományban deklarált függvényeket!
 *
 * Ügyeljen a helyes névtér használatra!
 *   Tipp: Használja a scope operátort, vagy nyisson névteret!
 */

/**
 * Saját atoi.
 * Számjegyeket tartalmazó karaktersorozat átalakítása int-re.
 * Helyes számjegysorozat végét white space, vagy sztring vége ('\0') jelzi.
 *   Ha a számjegysorozatban olyan számjegy, vagy betű fordul elő,
 *   ami nem érvényes az adott számrendszerben, az hiba.
 *   Pl. hármas számrendszerben nem fordulhat elő a 3-as számjegy, de az A betű sem.
 * Hiba esetén egy const char* típusú kivételt kell dobni, melynek értéke
 * az Ön neptun azonosítója!
 * @param p    - pointer a sztringre
 * @param base - számrendszer alapja (0-10)
 * @return     - base számrendszerben értelmezett szám
 */
int sajat::atoi(const char *p, int base)
{
    int eredmeny = 0;
    char szam;

    // Az ASCII tábla összes létező tulajdonáságt kihasználjuk
    while((szam = *p) > ' ')
    {
        szam -= '0';

        if (szam > 9 ) // ezzel tudna 10 feletti alapokat kezelni
            szam -= ('A' - '0');

        if (szam >= base)
            throw "KILZ7Q";

        eredmeny = eredmeny * base + szam;
        p++;
    }

    return eredmeny;
}

/**
 * Sajat strcat.
 * Két C stílusú sztring (nullával lezárt karaktersorozat) összefűzése
 * A függvény dinamikusan foglal helyet az eredménynek.
 * @param p1   - pointer az első sztringre
 * @param p2   - pointer az másik sztringre
 * @return     - dinamikusan foglalt terület címe, ahova az eredmény kerül (hívónak kell felszabadítania)
 */
char *sajat::strcat(const char *p1, const char *p2)
{
    size_t p1hossz = strlen(p1);
    size_t p2hossz = strlen(p2);
    size_t ujhossz = p1hossz + p2hossz;
    char *r = new char[ujhossz + 1];

    for (size_t i = 0; i < p1hossz; i++)
    {
        r[i] = p1[i];
    }

    for (size_t i = 0; i < p2hossz; i++)
    {
        r[ujhossz - p2hossz + i] = p2[i];

    }
    
    r[ujhossz] = 0;

    return r;
}

/**
 * unique
 * A paraméterként kapott két pointer közötti karaktersorozatból kihagyja az egymás után ismétlődő
 * karaktereket (char). A sorozatot az eredeti helyén hagyja!
 * @param first - pointer az adatok kezdetére
 * @param last  - pointer, ami az utolsó adat után mutat
 * @return      - pointer, ami az új sorozat utolsó adata után mutat (a kihagyással rövidült a sorozat)
 */
char *sajat::unique(char *first, char *last)
{
    char *fol = first;

    for (char *mov = first; mov < last; mov++)
    {
        if (*fol != *mov)
        {
            fol++;
            *fol = *mov;
        }
    }
    fol++;

    return fol;
}

/**
 * Az alább megvalósított adatstruktúra és a hozzá tartózó függvények
 * A max sablonnal kapcsolatos feladat megvalósításához kellenek.
 *
 * Értse meg a működésüket!
 * A feladat részletes leírását a max.hpp fájlban találja.
 * A kapcsolódó feladatot a max.hhp-ben oldja meg, azaz
 * abban valósítsa meg a várt sablont és annak specializációját!
 */

/**
 * Adatstruktúra komplex szám tárolásához
 */
struct Komplex {
    double re;  // valós rész
    double im;  // képzetes rész
};

/**
 * Komplex szám abszolút értéke
 * @param k - komplex szám
 * @return valós - a komplex szám abszolút értéke
 */
inline double absKomplex(const Komplex& k) {
    return sqrt(k.re*k.re + k.im*k.im);
}

/**
 * Komplex szám kiírása egy ostream típusú adatfolyamra
 * @param os - ostream típusú objektum
 * @param k - komplex szám
 * @return os
 */
inline std::ostream& operator<<(std::ostream& os, const Komplex& k) {
    os << "(" << k.re << "," << k.im << "j)";
    return os;
}