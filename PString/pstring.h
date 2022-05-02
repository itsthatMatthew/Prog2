#pragma once
#ifndef _P_STRING_
#define _P_STRING_

#include <iostream>
#include "string5.h"
#include "serializable.h"

class PString : public String, public Serializable
{
public:
    // ctr / cctr / dtr
    PString();
    PString(const String& str);
    ~PString();
    // write/read    
    void write(std::ostream& ostr) const;
    void read(std::istream& istr);
}; // class PString

#endif // _P_STRING_