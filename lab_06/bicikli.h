#ifndef BICIKLI_H
#define BICIKLI_H

#include <iostream>

using namespace std; // kenyelem + atlathatosag

class Jarmu
{
private:
    double vMax;
public:
    Jarmu(double v) : vMax(v) { cout << "\tJarmu ctor vMax=" << vMax << endl; }
    Jarmu(const Jarmu& masik) { vMax = masik.vMax; cout << "\tJarmu copy vMax=" << vMax << endl; }
    virtual ~Jarmu() { cout << "\tJarmu dtor vMax=" << vMax << endl; }
};

class Szan : public Jarmu
{
private:
    int kutyakSzama;
public:
    Szan(double v = 0, int n = 0) : Jarmu(v), kutyakSzama(n) { cout << "\tSzan ctor kutyakSzama=" << kutyakSzama << endl; }
    Szan(const Szan& masik) : Jarmu(masik) { kutyakSzama = masik.kutyakSzama; cout << "\tSzan copy kutyakSzama=" << kutyakSzama << endl; }
    ~Szan() { cout << "\tSzan dtor kutyakSzama=" << kutyakSzama << endl; }
};

class Kerek
{
private:
    int atmero;
public:
    Kerek(int d = 16) : atmero(d) { cout << "\tKerek ctor" << endl; }
    Kerek(const Kerek& masik) : atmero(masik.atmero) { cout << "\tKerek copy" << endl; }
    virtual ~Kerek() { cout << "\tKerek dtor" << endl; }
    void kiir() { cout << "atmero=" << atmero << endl; }
};

class Bicikli : public Jarmu
{
private:
    Kerek elso;
    Kerek hatso;
public:
    Bicikli(double v, int d) : Jarmu(v), elso(d), hatso(d) { cout << "\tBicikli ctor "; elso.kiir(); }
    Bicikli(const Bicikli& masik) : Jarmu(masik), elso(masik.elso), hatso(masik.hatso)
    { cout << "\tBicikli copy "; elso.kiir(); }
    ~Bicikli() { cout << "\tBicikli dtor "; elso.kiir(); }
};

#endif // BICIKLI_H