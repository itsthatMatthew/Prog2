/**
 * @file ember.h
 * 
 * Ember osztály deklarációja.
 * Nevet, születési évet tárol.
 * A nevet dinamikusan, \0-lal lezárt karaktersorozatként tárolja.
 * 
 */

#pragma once    // C++ stílusú header guard

class Ember
{
protected:  // Szrámaztatott osztályok számára elérhető, de külsőleg nem
    char* nev;
    int szulEv;
public:
    /// Ez az alapértelmezett konstruktor is
    /// @param n  - név (alapértelmezése a saját Neptun kódja)
    /// @param ev - születési év (alapértelmezésben a saját születései éve)
    Ember(const char* n = "KILZ7Q", int ev = 2002); // Alapértelmezett paraméterekkel

    /// Másoló konstruktor
    Ember(const Ember& e);

    /// Destruktor
    virtual ~Ember();

    /// Értékadó operátor
    Ember& operator=(const Ember& e);

    /// Név lekérdezése
    const char* getNev() const;

    /// Adott évben betöltött kor lekérdezése
    /// @param  ev - adott év, amelyikben a betöltött életkort vizsgáljuk
    /// Nem vizsgálja, hogy megszületett-e
    virtual int getKor(int ev) const;

    /// Foglalkozás lekérdezése
    virtual const char* foglalkozas() const;
};