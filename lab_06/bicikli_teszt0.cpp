/**
 *  6. labor �nellen�rz� feladat teszt
 *
 *  A jporta nem pontosan ezt a tesztet futtatja, de az elv�rt kimenete azonos.
 *  Ha �rdeklik a r�szletek, n�zze meg a Jporta-n a teszt forr�s�t.
 *
 */



#include "memtrace.h"
#include "bicikli.h"

struct MyKerek : Kerek {
    MyKerek() : Kerek(-1) {
        std::cout << "\tMyKerek ctor ";
        kiir();
    }
    ~MyKerek() {
        std::cout << "\tMyKerek dtor ";
        kiir();
    }
};


int main() {
    Szan sz1(1.1, 7);
    Szan sz2 = sz1;
    Bicikli b1(10, 16);
    Bicikli b2 = b1;
    Kerek *k = new MyKerek;
    delete k;
    Jarmu *j = new Bicikli(0,0);
    delete j;
}