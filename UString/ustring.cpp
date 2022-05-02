#include "ustring.h"

/// Statikus adattag nagybetűség tárolására
bool UString::isUCase = false;  // Alapértelmezett állapota hamis

/// Nagybetűség beállítása
void UString::UCase(bool set)
{
    UString::isUCase = set;
}

/// Nagybetűség lekérdezése
bool UString::UCase() const
{
    return UString::isUCase;
}

/// Kiiratás túlterhelése
std::ostream& operator<<(std::ostream& outs, const UString& string)
{
    // Ha nagybetűs kiiratás...
    if (string.UCase() == true)
    {
        // minden betűre külön...
        for (size_t i = 0; i < string.size(); i++)
        {
            // ha kisbetűs,
            if (string[i] >= 'a' && string[i] <= 'z')
                // legyen nagybetűs, majd írja ki;
                outs << (char) (string[i] + ('A'-'a'));
            // ha nem (nagybetű, szám, írásjel stb.),
            else
                // simán írja ki.
                outs << string[i];
        }
        
    }
    // Ha nem nagybetűs kiiratás...
    else
    {
        // csak simán írja ki az egészet alapértelmezettként.
        outs << string.c_str();
    }

    return outs;
}
