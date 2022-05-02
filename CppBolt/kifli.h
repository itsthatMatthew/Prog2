#ifndef KIFLI_H
#define KIFLI_H

#include "aru.h"

class Kifli : public Aru
{
private:
    String spec;
public:
    Kifli (double ar, const char* spec = "") : Aru("Kifli", "db", ar), spec(spec) {}
    std::ostream& print(std::ostream& os) const
    {
        return os << megnevezes << " "
                  << spec << "; "
                  << ar << "Ft/" << egyseg;
    }
};

#endif // KIFLI_H