// Generikus matrixok hasznalatat lehetove tevo fejlecfajl.
// Matrix tipusa es hibaosztalya sablonparameterkent valaszthato.

/* Tervre adott visszajelzesekrol visszajelzesekre adott visszajelzesrol visszajelzesek Gabornak:
 * - valtottam 2D-s tomb tarolasra, igy az iterator a kisse korulmenyes maradt
 * - a konstruktor makro valoban nem a "legszebb" megoldas, de mukodik es kenyelmes
 * - a statikus alapertekeket vegul elhagytam, tobb okbol is:
 *      + valoban korulmenyesek voltak, csak amennyire a labor feladatokat vettem alapul a hazihoz,
 *      egyfajta "must have" dolognak tunt
 *      + nem primitiv tipusokra, ahol a 0 mint ertek ertelmes, csak problemat okozott
 *      (pl.: egy koordinataparnal 0-val letrehozni nem igazan mukodokepes), igy maradt az,
 *      hogy megadott ertek hijan uresen inicializalja a mezoket, es nem probal azzal okoskodni,
 *      hogy pl.: vegig 0 ertekuk legyen
 *      + lehet, hogy az adattal feltoltes csak feleslegesen lassitja a konstruktort,
 *      mert nem is szeretnenk
*/

#pragma once
#ifndef _GENERIKUS_MATRIX_HPP_
#define _GENERIKUS_MATRIX_HPP_

#include <iostream> // A matrixok kiiratasahoz es beolvasasahoz szukseges
#include <stdexcept> // A kivetelek dobasahoz es kezelesehez szukseges

// Matrixok konstruktor definiciojat egyszerusito makro
/* WARNING(mate): programozoi kenyelmebol (sajatombol) a parameterek nevet nem atveszi, hanem mivel ismert, egybol hasznalja. Ez nem kifejezetten biztonsagos, de megvaltozasuk nem valoszinu (+egyeb valve source code leak jellegu kommentek) */
#define GM_KONSTR(...) { \
    if (m_Sor == 0 || m_Oszlop == 0) throw EXCEPT("Matrix(): 0 dim"); \
    m_mezoPtr = new TYPE*[m_Sor]; \
    for (size_t i = 0; i < m_Sor; i++) \
        m_mezoPtr[i] = new TYPE[m_Oszlop]; \
    for (size_t i = 1; i <= m_Sor; i++) { \
    for (size_t j = 1; j <= m_Oszlop; j++) { \
        __VA_ARGS__; } } \
}

template<class TYPE = double, class EXCEPT = std::out_of_range> class Matrix {
private: // Belso adattagok

    // Matrix sorszama
    size_t m_Sor;
    // Matrix oszlopszama
    size_t m_Oszlop;
    // Ketdimenzios tombkent foglalt memoria, ahol a mezoket tarolja
    TYPE** m_mezoPtr;

public: // Az osztaly fuggvenyei
    /* Cseles konstruktor felepites.
     * Mivel az embernek tobb parameterlista is intuitiv (lehet), ezeket kulon kezelunk:
     *
     * Matrix m0;          <~ ures matrixot vafutk
     * Matrix m1(1);       <~ "1" ertek beallitasat varjuk egy 1x1-es matrixba
     * Matrix m2(2, 3);    <~ az alapertek (tipus def. konstruktora) beallitasat varjuk a megadott meretekkel
     * Matrix m3(4, 5, 6); <~ specifikacio szerint az elso ket ertek a meretet, a harmadik az erteket adja
     *
     * Tovabba specialis konstruktorok:
     *
     * Matrix mfv(7, 8, &foo);       <~ "foo" fvpointerevel inicializalja
     * Matrix mft(9, 10, funk);      <~ "funk" funktorral inicializalja
     * Matrix mil({{1, 2}, {3, 4}}); <~ stl inicializalo listaval inicializalja
     * ^~ Ez utobbi kenyelmes es igazan intuitiv inicializaciot enged meg, a matrixokat lenyegeben
     * "lerajzolhatjuk" a programkodban, es abbol jonnek letre:
     * Matrix<int> matrix = { {1, 2, 3},
     *                        {4, 5, 6} }; <~ Egy 2x3-as int matrixot ad
     *
     * Matrix<int> egysegmatrix = { {1, 0, 0},
     *                              {0, 1, 0},
     *                              {0, 0, 1} }; <~ 3x3-as egysegmatrixot hoz letre
    */

    /// Konstruktor
    /// parameter nelkuli, ures, inicializalatlan matrixot hoz letre
    Matrix() : m_Sor(0), m_Oszlop(0), m_mezoPtr(nullptr) {}

    /// Konstruktor
    /// @param ertek a mezo beallitando erteket adja meg
    explicit Matrix(TYPE ertek)
    : m_Sor(1), m_Oszlop(1) {
        m_mezoPtr = new TYPE*[1];
        *m_mezoPtr = new TYPE[1];
        **m_mezoPtr = ertek;
    }

    /// Konstruktor
    /// @param sorszam a matrix sorainak szamat adja meg
    /// @param oszlopszam a matrix oszlopainak szamat adja meg
    Matrix(size_t sorszam, size_t oszlopszam)
    : m_Sor(sorszam), m_Oszlop(oszlopszam) {
        GM_KONSTR( mezo(i, j) = TYPE() );
    }

    /// Konstruktor
    /// @param sorszam a matrix sorainak szamat adja meg
    /// @param oszlopszam a matrix oszlopainak szamat adja meg
    /// @param ertek a mezonkent beallitando erteket adja meg
    Matrix(size_t sorszam, size_t oszlopszam, TYPE ertek)
    : m_Sor(sorszam), m_Oszlop(oszlopszam) {
        GM_KONSTR( mezo(i, j) = ertek );
    }

    /// Konstruktor
    /// @param sorszam a matrix sorainak szamat adja meg
    /// @param oszlopszam a matrix oszlopainak szamat adja meg
    /// @param fv ketparameteres fuggvenypointer, mely alapjan beallitja a mezoket
    Matrix(size_t sorszam, size_t oszlopszam, TYPE (*fv)(size_t, size_t))
    : m_Sor(sorszam), m_Oszlop(oszlopszam) {
        GM_KONSTR( mezo(i, j) = fv(i, j) );
    }

    /// Konstruktor
    /// @param sorszam a matrix sorainak szamat adja meg
    /// @param oszlopszam a matrix oszlopainak szamat adja meg
    /// @param funk ketparameteres funktor, mely alapjan beallitja a mezoket
    template<class FUNK>
    Matrix(size_t sorszam, size_t oszlopszam, FUNK funk)
    : m_Sor(sorszam), m_Oszlop(oszlopszam) {
        GM_KONSTR( mezo(i, j) = funk(i, j) );
    }

    /// Konstruktor
    /// @param list agyazott inicializalo lista, melybol a Matrixot kepzi (kulso a sorokat, belso az oszloponkenti mezoket adja meg)
    Matrix(const std::initializer_list<const std::initializer_list<TYPE>>& list)
    : m_Sor(list.size()), m_Oszlop(list.begin()->size()) {
        GM_KONSTR( mezo(i, j) = list.begin()[i - 1].begin()[j - 1] );
    }

    // Masolo konstruktor
    Matrix(const Matrix& masik)
    : m_Sor(masik.m_Sor), m_Oszlop(masik.m_Oszlop) {
        GM_KONSTR( mezo(i, j) = masik.mezo(i, j) );
    }

    // Destruktor
    ~Matrix() {
        for (size_t i = 0; i < m_Sor; i++)
            delete[] m_mezoPtr[i];
        delete[] m_mezoPtr;
    }

    // Ertekado operator
    Matrix& operator=(const Matrix& masik) {
        if (this != &masik)
        {
            for (size_t i = 0; i < m_Sor; i++)
                delete[] m_mezoPtr[i];
            delete[] m_mezoPtr;
            m_Sor = masik.m_Sor;
            m_Oszlop = masik.m_Oszlop;
            m_mezoPtr = new TYPE*[m_Sor];
            for (size_t i = 0; i < m_Sor; i++)
                m_mezoPtr[i] = new TYPE[m_Oszlop];
            for (size_t i = 1; i <= m_Sor; i++)
            for (size_t j = 1; j <= m_Oszlop; j++)
                mezo(i, j) = masik(i, j);
        }
        return *this;
    }

public: // Iteratorok

    class sor_iterator {
    private:
        const Matrix* matrix; // kis csel az agyazott iterator szamara az oszlopszam eleresere
        TYPE** sor;
    public:
        sor_iterator(const Matrix* mtrx, TYPE** alap = 0) : matrix(mtrx), sor(alap) {}
        sor_iterator& operator++() { sor++; return *this; }
        sor_iterator operator++(int) { sor_iterator temp = *this; ++(*this); return temp; }
        TYPE* operator*() { return *sor; }
        bool operator==(sor_iterator jobb_i) { return sor == jobb_i.sor; }
        bool operator!=(sor_iterator jobb_i) { return sor != jobb_i.sor; }

        class mezo_iterator {
        private:
            TYPE* mezo;
        public:
            mezo_iterator(TYPE* alap = 0) : mezo(alap) {}
            mezo_iterator& operator++() { mezo++; return *this; }
            mezo_iterator operator++(int) { mezo_iterator temp = *this; ++(*this); return temp; }
            TYPE& operator*() { return *mezo; }
            bool operator==(mezo_iterator jobb_i) { return mezo == jobb_i.mezo; }
            bool operator!=(mezo_iterator jobb_i) { return mezo != jobb_i.mezo; }
        }; // class mezo_iterator
        mezo_iterator begin(void) const { return mezo_iterator(*sor); }
        mezo_iterator end(void) const   { return mezo_iterator(*sor + matrix->oszlopszam()); }
    }; // class sor_iterator
    sor_iterator begin(void) const { return sor_iterator(this, m_mezoPtr); }
    sor_iterator end(void) const   { return sor_iterator(this, m_mezoPtr + m_Sor); }

public: // Haszonfuggvenyek

    TYPE& mezo(size_t sor, size_t oszlop) {
        if (sor - 1 >= m_Sor || oszlop - 1 >= m_Oszlop) throw EXCEPT("mezo(): index hiba");
        //     ^~ Kihasznaljuk, hogy unsigned formaban vannak tarolva
        return m_mezoPtr[sor - 1][oszlop - 1];
    }
    const TYPE mezo(size_t sor, size_t oszlop) const {
        if (sor - 1 >= m_Sor || oszlop - 1 >= m_Oszlop) throw EXCEPT("mezo() const: index hiba");
        return m_mezoPtr[sor - 1][oszlop - 1];
    }

    /// Visszaadja a matrix sorainak szamat
    size_t sorszam(void) const { return m_Sor; }
    /// Visszaadja a matrix oszlopainak szamat
    size_t oszlopszam(void) const { return m_Oszlop; }

    /// Matrix kiiro fuggvenye
    std::ostream& Print(const char* = NULL, std::ostream& = std::cout) const;

    static Matrix GaussEliminacio(const Matrix&, size_t = 0);   // NOTE(mate): kesz
    Matrix GaussEliminalt(size_t szelte = 0) const { return GaussEliminacio(*this, szelte); }
    static Matrix EgysegMatrix(size_t);                         // NOTE(mate): kesz
    Matrix EgysegMatrix(void) const { return EgysegMatrix(m_Oszlop); }
    Matrix Transzponalt(void) const;                            // NOTE(mate): kesz
    Matrix Inverz(void) const;                                  // NOTE(mate): kesz
    TYPE Determinans(void) const;                               // NOTE(mate): kesz
    size_t Rang(void) const;                                    // NOTE(mate): kesz

public: // Matrixmuveletek (tulterhelt operatorokkal elerhetoek)

    Matrix Osszead(const Matrix&) const;                        // NOTE(mate): kesz
    Matrix Kivon(const Matrix&) const;                          // NOTE(mate): kesz
    Matrix Szoroz(TYPE) const;                                  // NOTE(mate): kesz
    Matrix Szoroz(const Matrix&) const;                         // NOTE(mate): kesz

public: // Sor- es oszlopmuveletek

    Matrix& Mellefuz(const Matrix&);                            // NOTE(mate): kesz
    Matrix& Alafuz(const Matrix&);                              // NOTE(mate): kesz
    Matrix& SorSzoroz(size_t, TYPE);                            // NOTE(mate): kesz
    Matrix& SorTorol(size_t);                                   // NOTE(mate): kesz
    Matrix& SorCserel(size_t, size_t);                          // NOTE(mate): kesz
    Matrix& OszlopSzoroz(size_t, TYPE);                         // NOTE(mate): kesz
    Matrix& OszlopTorol(size_t);                                // NOTE(mate): kesz
    Matrix& OszlopCserel(size_t, size_t);                       // NOTE(mate): kesz
    Matrix ReszMatrix(size_t, size_t, size_t, size_t) const;    // NOTE(mate): kesz

public: // Tulterhelt operatorok (inline hivas)

    TYPE& operator()(size_t sor, size_t oszlop) { return this->mezo(sor, oszlop); }
    const TYPE operator()(size_t sor, size_t oszlop) const { return this->mezo(sor, oszlop); }

    Matrix operator+(const Matrix& jobb_M) const { return this->Osszead(jobb_M); }
    Matrix operator-(const Matrix& jobb_M) const { return this->Kivon(jobb_M); }
    Matrix operator*(TYPE jobb_S) const { return this->Szoroz(jobb_S); }
    Matrix operator*(const Matrix& jobb_M) const { return this->Szoroz(jobb_M); }

    Matrix operator+=(const Matrix& jobb_M) { return *this = *this + jobb_M; }
    Matrix operator-=(const Matrix& jobb_M) { return *this = *this - jobb_M; }
    Matrix operator*=(TYPE jobb_S) { return *this = *this * jobb_S; }
    Matrix operator*=(const Matrix& jobb_M) { return *this = *this * jobb_M; }

    bool operator==(const Matrix& jobb_M) const;
    bool operator!=(const Matrix& jobb_M) const { return !(*this==jobb_M); }

    // Matrixok kozti tipuskonverzio (mezonkent)
    template<typename KONV> operator Matrix<KONV>() const;

    Matrix operator!() const { return this->Transzponalt(); }
    Matrix operator~() const { return this->Inverz(); }
}; // class Matrix

// NOTE(mate): Matrix osztalynak itt vege, ez utan belso/kulso fuggvenydefiniciok kovetkeznek

/// Matrix Gauss-eliminaltjat adja meg
/// @param matrix az adott matrixon, amin elvegzendo az algoritmus
/// @param szelte az algoritmus "jobb-szele", ameddig a lepeseket elvegzi (lin. egy. rendsz. megoldasara + inverz)
template<class TYPE, class EXCEPT> Matrix<TYPE, EXCEPT> Matrix<TYPE, EXCEPT>::GaussEliminacio(const Matrix& matrix, size_t szelte) {
    Matrix<TYPE, EXCEPT> visszatero = matrix;
    if (szelte == 0) szelte = visszatero.m_Oszlop;
    size_t i = 1, j = 1;
    bool fut = true;
    while (fut) {
        if (visszatero(i, j) != TYPE(0)) {
            visszatero.SorSzoroz(i, TYPE(1) / visszatero(i, j));
            if (i < visszatero.m_Sor) {
                for (size_t t = i + 1; t <= visszatero.m_Sor; t++) {
                    TYPE sorelso = visszatero(t, j);
                    for (size_t oszlop = 1; oszlop <= visszatero.m_Oszlop; oszlop++)
                        visszatero(t, oszlop) = visszatero(t, oszlop) - sorelso * visszatero(i, oszlop) / visszatero(i, j);
                }
            }
            if (i < visszatero.m_Sor && j < szelte) {
                i++;
                j++;
            }
            else fut = false;
        }
        else {
            bool talalt = false;
            for (size_t t = i + 1; t <= visszatero.m_Sor; t++) {
                if (visszatero(t, j) != TYPE(0)) {
                    visszatero.SorCserel(i, t);
                    talalt = true;
                }
                if (talalt) break;
                else j++;
            }
            if (j < szelte) j++;
            else fut = false;
        }
    }
    // na most visszafele is
    //j--;
    fut = true;
    while (fut) {
        if (visszatero(i, j) != TYPE(0)) {
            if (j > 1) {
                for (size_t sor = i - 1; sor > 0; sor--) {
                    TYPE sorelso = visszatero(sor, j);
                    for (size_t oszlop = j; oszlop <= visszatero.m_Oszlop; oszlop++)
                        visszatero(sor, oszlop) = visszatero(sor, oszlop) - visszatero(i, oszlop) * sorelso / visszatero(i, j);
                }
            }
            if (i > 1 && j > 1)
                j--;
            else fut = false;
        }
        else {
            bool talalt = false;
            for (size_t t = j - 1; t > 1; t--) {
                if (visszatero(i, t) != 0) {
                    talalt = true;
                }
                if (talalt) break;
                else j--;
            }
            if (i > 1 && j > 1) i--;
            else fut = false;
        }
    }
    return visszatero;
}

/// Matrix transzponaltjat adja meg
template<class TYPE, class EXCEPT> Matrix<TYPE, EXCEPT> Matrix<TYPE, EXCEPT>::Transzponalt(void) const {
    Matrix visszatero(m_Oszlop, m_Sor);
    for (size_t i = 1; i <= m_Sor; i++)
    for (size_t j = 1; j <= m_Oszlop; j++)
        visszatero(j, i) = mezo(i, j);
    return visszatero;
}

/// Matrix inverzet adja meg
/// (egysegmatrixszal kibovitett matrix Gauss-eliminaciojaval)
template<class TYPE, class EXCEPT> Matrix<TYPE, EXCEPT> Matrix<TYPE, EXCEPT>::Inverz(void) const {
    if (m_Oszlop != m_Sor) throw EXCEPT("Inverz(): nem egyezo dim");
    if (Determinans() == TYPE(0)) throw EXCEPT("Inverz(): 0 det, nincs inverz");
    Matrix matrix = *this;
    matrix.Mellefuz(matrix.EgysegMatrix());
    matrix = GaussEliminacio(matrix, m_Oszlop);
    return matrix.ReszMatrix(1, m_Oszlop + 1, m_Sor, 2 * m_Oszlop);
}

/// Matrix determinansat adja meg
/// (roviditett Gauss-eliminacioval, ahol a foatloba kepez vezereket, determinanst pedig szorzatosszeggel adja)
template<class TYPE, class EXCEPT> TYPE Matrix<TYPE, EXCEPT>::Determinans(void) const {
    if (m_Oszlop != m_Sor) throw EXCEPT("Determinans(): nem egyezo dim");
    // Gauss-eliminacio lepesei, de csak felso-haromszog matrixig
    Matrix<TYPE, EXCEPT> matrix = *this;
    size_t i = 1, j = 1;
    bool fut = true;
    while (fut) {
        if (i == matrix.m_Sor || j == matrix.m_Oszlop) break;
        if (matrix(i, j) != TYPE(0)) {
            if (i < matrix.m_Sor) {
                for (size_t t = i + 1; t <= matrix.m_Sor; t++) {
                    TYPE sorelso = matrix(t, j);
                    for (size_t oszlop = 1; oszlop <= matrix.m_Oszlop; oszlop++)
                        matrix(t, oszlop) = matrix(t, oszlop) - matrix(i, oszlop) * sorelso / matrix(i, j);
                }
            }
            if (i < matrix.m_Sor && j < matrix.m_Oszlop) {
                i++;
                j++;
            }
            else fut = false;
        }
        else {
            bool talalt = false;
            for (size_t t = i + 1; t <= matrix.m_Sor; t++) {
                if (matrix(t, j) != TYPE(0)) {
                    matrix.SorCserel(i, t);
                    talalt = true;
                    break;
                }
                j++;
            }
            if (talalt) {
                if (j < matrix.m_Oszlop) j++;
                else fut = false; //  Ha csupa 0, a det is biztosan 0, kilep
            }
        }
    }
    TYPE det = matrix(1, 1);
    for (size_t i = 2; i <= m_Sor; i++)
        det = det * matrix(i, i);
    return det;
}

/// Matrix rangjat adja meg
/// (fuggetlen sorok kihasznalasaval)
template<class TYPE, class EXCEPT> size_t Matrix<TYPE, EXCEPT>::Rang(void) const {
    size_t rang = m_Sor;
    Matrix<TYPE, EXCEPT> gauss = GaussEliminalt();
    for (size_t sor = 1; sor <= m_Sor; sor++)
    {
        bool nullsor = true;
        for (size_t oszlop = 1; oszlop <= m_Oszlop; oszlop++)
        {
            if (gauss(sor, oszlop) != TYPE(0))
            {
                nullsor = false;
            }
        }
        if (nullsor) rang--;
    }
    return rang;
}

/// Egy adott meretu egysegmatrixszal ter vissza
/// @param o az oldalmeret
template<class TYPE, class EXCEPT> Matrix<TYPE, EXCEPT> Matrix<TYPE, EXCEPT>::EgysegMatrix(size_t o) {
    Matrix visszatero(o, o, TYPE(0));
    for (size_t i = 1; i <= o; i++)
        visszatero(i, i) = TYPE(1);
    return visszatero;
}

/// A matrix melle fuzi a parametrkent kapottat (megeggyezo sorszam szukseges)
/// @param masik a mellefuzendo matrix
template<class TYPE, class EXCEPT> Matrix<TYPE, EXCEPT>& Matrix<TYPE, EXCEPT>::Mellefuz(const Matrix& masik) {
    Matrix temp(m_Sor, m_Oszlop + masik.m_Oszlop);
    for (size_t sor = 1; sor <= m_Sor; sor++)
    {
        for (size_t oszlop = 1; oszlop <= m_Oszlop; oszlop++)
            temp(sor, oszlop) = mezo(sor, oszlop);
        for (size_t oszlop = 1; oszlop <= masik.m_Oszlop; oszlop++)
            temp(sor, oszlop + m_Oszlop) = masik(sor, oszlop);
    }
    *this = temp;
    return *this;
}

/// A matrix ala fuzi a parametrkent kapottat (megeggyezo oszlopszam szukseges)
/// @param masik az alafuzendo matrix
template<class TYPE, class EXCEPT> Matrix<TYPE, EXCEPT>& Matrix<TYPE, EXCEPT>::Alafuz(const Matrix& masik) {
    Matrix temp(m_Sor + masik.m_Sor, m_Oszlop);
    for (size_t oszlop = 1; oszlop <= m_Oszlop; oszlop++)
    {
        for (size_t sor = 1; sor <= m_Sor; sor++)
            temp(sor, oszlop) = mezo(sor, oszlop);
        for (size_t sor = 1; sor <= masik.m_Sor; sor++)
            temp(sor + m_Sor, oszlop) = masik(sor, oszlop);
    }
    *this = temp;
    return *this;
}

/// Megszoroz egy adott sort egy skalarral
/// @param sor a megszorzando sor szama
/// @param skalar a szorzo skalar
template<class TYPE, class EXCEPT> Matrix<TYPE, EXCEPT>& Matrix<TYPE, EXCEPT>::SorSzoroz(size_t sor, TYPE skalar) {
    for (size_t oszlop = 1; oszlop <= m_Oszlop; oszlop++)
        mezo(sor, oszlop) = mezo(sor, oszlop) * skalar;
    return *this;
}

/// Torol egy adott sort a matrixbol
/// @param sort a torlendo sor
template<class TYPE, class EXCEPT> Matrix<TYPE, EXCEPT>& Matrix<TYPE, EXCEPT>::SorTorol(size_t sort) {
    Matrix temp(m_Sor - 1, m_Oszlop);
    for (size_t oszlop = 1; oszlop <= m_Oszlop; oszlop++)
    {
        for (size_t sor = 1; sor < sort; sor++)
            temp(sor, oszlop) = mezo(sor, oszlop);
        for (size_t sor = sort; sor < m_Sor; sor++)
            temp(sor, oszlop) = mezo(sor + 1, oszlop );
    }
    *this = temp;
    return *this;
}

/// Kicserel ket sort a matrixban
/// @param sort az egyik cserelendo sor
/// @param sorral a masik cserelendo sor
template<class TYPE, class EXCEPT> Matrix<TYPE, EXCEPT>& Matrix<TYPE, EXCEPT>::SorCserel(size_t sort, size_t sorral) {
    Matrix temp = *this;
    for (size_t oszlop = 1; oszlop <= m_Oszlop; oszlop++) {
        mezo(sort, oszlop) = temp(sorral, oszlop);
        mezo(sorral, oszlop) = temp(sort, oszlop);
    }
    return *this;
}

/// Megszoroz egy adott oszlopot egy skalarral
/// @param oszlop a megszorzando oszlop szama
/// @param skalar a szorzo skalar
template<class TYPE, class EXCEPT> Matrix<TYPE, EXCEPT>& Matrix<TYPE, EXCEPT>::OszlopSzoroz(size_t oszlop, TYPE skalar) {
    for (size_t sor = 1; sor <= m_Sor; sor++)
        mezo(sor, oszlop) = mezo(sor, oszlop) * skalar;
    return *this;
}

/// Torol egy adott oszlopot a matrixbol
/// @param oszlopot a torlendo oszlop
template<class TYPE, class EXCEPT> Matrix<TYPE, EXCEPT>& Matrix<TYPE, EXCEPT>::OszlopTorol(size_t oszlopot) {
    Matrix temp(m_Sor, m_Oszlop - 1);
    for (size_t sor = 1; sor <= m_Sor; sor++)
    {
        for (size_t oszlop = 1; oszlop < oszlopot; oszlop++)
            temp(sor, oszlop) = mezo(sor, oszlop);
        for (size_t oszlop = oszlopot; oszlop < m_Oszlop; oszlop++)
            temp(sor, oszlop) = mezo(sor, oszlop + 1);
    }
    *this = temp;
    return *this;
}

/// Kicserel ket oszlopot a matrixban
/// @param oszlopot az egyik cserelendo oszlop
/// @param oszloppal a masik cserelendo oszlop
template<class TYPE, class EXCEPT> Matrix<TYPE, EXCEPT>& Matrix<TYPE, EXCEPT>::OszlopCserel(size_t oszlopot, size_t oszloppal) {
    Matrix temp = *this;
    for (size_t sor = 1; sor <= m_Sor; sor++) {
        mezo(sor, oszlopot) = temp(sor, oszloppal);
        mezo(sor, oszloppal) = temp(sor, oszlopot);
    }
    return *this;
}

/// Visszaad egy reszmatrixot a meghatarozott marapeterek koze beszoritva
/// @param f_sor a legfelso sorszam
/// @param b_oszlop a legszelso baloldali oszlopszam
/// @param a_sor a legalso sorszam
/// @param j_oszlop a legszelso jobboldali oszlopszam
template<class TYPE, class EXCEPT> Matrix<TYPE, EXCEPT> Matrix<TYPE, EXCEPT>::ReszMatrix(size_t f_sor, size_t b_oszlop, size_t a_sor, size_t j_oszlop) const {
    Matrix visszatero(a_sor - f_sor + 1, j_oszlop - b_oszlop + 1);
    for (size_t i = f_sor; i <= a_sor; i++)
    for (size_t j = b_oszlop; j <= j_oszlop; j++)
        visszatero(i - f_sor + 1, j - b_oszlop + 1) = mezo(i, j);
    return visszatero;
}

// Matrixmuveletek

template<class TYPE, class EXCEPT> Matrix<TYPE, EXCEPT> Matrix<TYPE, EXCEPT>::Osszead(const Matrix& jobb_M) const {
    if (m_Sor != jobb_M.m_Sor || m_Oszlop != jobb_M.m_Oszlop) throw EXCEPT("Osszead(): nem azonos dim");
    Matrix visszatero(m_Sor, m_Oszlop);
    for (size_t i = 1; i <= m_Sor; i++)
    for (size_t j = 1; j <= m_Oszlop; j++)
        visszatero(i, j) = mezo(i, j) + jobb_M(i, j);
    return visszatero;
}

template<class TYPE, class EXCEPT> Matrix<TYPE, EXCEPT> Matrix<TYPE, EXCEPT>::Kivon(const Matrix& jobb_M) const {
    if (m_Sor != jobb_M.m_Sor || m_Oszlop != jobb_M.m_Oszlop) throw EXCEPT("Kivon(): nem azonos dim");
    Matrix visszatero(m_Sor, m_Oszlop);
    for (size_t i = 1; i <= m_Sor; i++)
    for (size_t j = 1; j <= m_Oszlop; j++)
        visszatero(i, j) = mezo(i, j) - jobb_M(i, j);
    return visszatero;
}

template<class TYPE, class EXCEPT> Matrix<TYPE, EXCEPT> Matrix<TYPE, EXCEPT>::Szoroz(TYPE jobb_S) const {
    Matrix visszatero(m_Sor, m_Oszlop);
    for (size_t i = 1; i <= m_Sor; i++)
    for (size_t j = 1; j <= m_Oszlop; j++)
        visszatero(i, j) = jobb_S * mezo(i, j);
    return visszatero;
}

template<class TYPE, class EXCEPT> Matrix<TYPE, EXCEPT> Matrix<TYPE, EXCEPT>::Szoroz(const Matrix& jobb_M) const {
    if (m_Oszlop != jobb_M.m_Sor) throw EXCEPT("Szoroz(): nem megfelelo dim");
    Matrix visszatero(m_Sor, jobb_M.m_Oszlop, TYPE(0)); // NOTE(mate): 0 init nem feltetlen letezo, def konstr?
    for (size_t i = 1; i <= m_Sor; i++)
    for (size_t j = 1; j <= jobb_M.m_Oszlop; j++)
    for (size_t k = 1; k <= m_Oszlop; k++)
        visszatero(i, j) = visszatero(i, j) + mezo(i, k) * jobb_M(k ,j);
    return visszatero;                   // ^~ += kivaltasara a visszatero mezot igy adjuk hozza
}

// Tulterhelt operatorok (baloldali skalar)
template<class TYPE, class EXCEPT> Matrix<TYPE, EXCEPT> operator*(TYPE bal_S, const Matrix<TYPE, EXCEPT>& jobb_M) { return jobb_M * bal_S; }
template<class TYPE, class EXCEPT> Matrix<TYPE, EXCEPT> operator*=(TYPE bal_S, const Matrix<TYPE, EXCEPT>& jobb_M) { return jobb_M *= bal_S; }

// Hasonlitas
template<class TYPE, class EXCEPT> bool Matrix<TYPE, EXCEPT>::operator==(const Matrix& jobb_M) const {
    if (m_Sor != jobb_M.m_Sor || m_Oszlop != jobb_M.m_Oszlop) throw EXCEPT("==/!=: Nem azonos dim");
    for (size_t i = 1; i <= m_Sor; i++)
    for (size_t j = 1; j <= m_Oszlop; j++)
        if (mezo(i, j) != jobb_M.mezo(i ,j)) return false;
    return true;
}

// Matrixok kozti tipuskonverzio (mezonkent)
template<class TYPE, class EXCEPT> template<typename KONV> Matrix<TYPE, EXCEPT>::operator Matrix<KONV>() const {
    Matrix<KONV, EXCEPT> visszatero(m_Sor, m_Oszlop);
    for (size_t i = 1; i <= m_Sor; i++)
    for (size_t j = 1; j <= m_Oszlop; j++)
        visszatero(i, j) = (KONV) mezo(i, j);
    return visszatero;
}

/** >m.Print("Matrix");
 * Matrix   R3x2
 *  _           _
 * |    11  12   |
 * |    21  22   |
 * |_   31  32  _|
 */

/// Matrix kiiro fuggvenye
/// @param megj tetszoleges megjegyzes a kiiratas elejen, ha nincs, NULL (alapertek)
/// @param ostr az ostream amire a kiiratas tortenik, alaperteke std::cout
template<class TYPE, class EXCEPT> std::ostream& Matrix<TYPE, EXCEPT>::Print(const char* megj, std::ostream& ostr) const {
    if (megj != NULL) ostr << megj << std::endl; // ha nem NULL a megjegyzes, irja ki
    return ostr << *this << std::endl;
}

// Kiiratas/beolvasas tulterhelt operatorokkal
template<class TYPE, class EXCEPT> std::ostream& operator<<(std::ostream& ostr, const Matrix<TYPE, EXCEPT>& jobb_M) {
    ostr << 'R' << jobb_M.sorszam() << 'x' << jobb_M.oszlopszam() << '\n'; // elso sor a dimenzioknak
    for (size_t i = 0; i <= jobb_M.sorszam(); i++) {
        for (size_t j = 0; j <= jobb_M.oszlopszam() + 1; j++) {
            if (j == 0) {
                if (i == 0) ostr << " _";           // Bal felso sarok
                else if (i == jobb_M.sorszam()) ostr << "|_";  // Bal also sarok
                else ostr << "| ";                  // Bal oldal
            }
            else if ( j == jobb_M.oszlopszam() + 1) {
                if (i == 0) ostr << "_ ";           // Jobb felso sarok
                else if (i == jobb_M.sorszam()) ostr << "_|";  // Jobb also sarok
                else ostr << " |";                  // Jobb oldal
            }
            else if (i != 0) ostr << jobb_M.mezo(i, j);    // Ha nem a legfelso sorban tart, mezo erteke
            if (j != jobb_M.oszlopszam() + 1) ostr << '\t';    // Ha nem az utolso oszlop, tabulator
        } // j
        if (i != jobb_M.sorszam()) ostr << '\n';    // Sorok vegeztevel uj sor
    } // i
    return ostr;
}
template<class TYPE, class EXCEPT> std::istream& operator>>(std::istream& istr, Matrix<TYPE, EXCEPT>& jobb_M) {
    size_t sor;
    size_t oszlop;
    char puffer;
    istr >> puffer >> sor >> puffer >> oszlop;
    //      ^~ 'R'           ^~ 'x'
    Matrix<TYPE, EXCEPT> uj_M(sor, oszlop);
    for (size_t i = 1; i <= sor; i++)
    for (size_t j = 1; j <= oszlop; j++)
        istr >> uj_M(i, j);
    jobb_M = uj_M;
    return istr;
}

#undef GM_KONSTR // Headeren kivuli hasznalatot nem engedjuk

#endif // _GENERIKUS_MATRIX_HPP_