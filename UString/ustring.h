#ifndef USTRING_H // Hedaer guard
#define USTRING_H

#include "string5.h" // Szülő osztály deklarációja

class UString : public String
{
public:
    /// Statikus adattag nagybetűség tárolására
    static bool isUCase;

    /// Ustring konstruktora
    UString(const String& str= "") : String(str) {}

    /// Nagybetűség beállítása
    static void UCase(bool);

    /// Nagybetűség lekérdezése
    bool UCase() const;
}; // class UString

/// Kiiratás túlterhelése
std::ostream& operator<<(std::ostream&, const UString&);

#endif // USTRING_H
