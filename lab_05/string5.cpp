/**
 *
 * \file string5.cpp
 *
 * Itt kell megvalósítania a hiányzó tagfüggvényeket.
 * Segítségül megadtuk a C++ nem OO eszközeinek felhasználásával készített String-kezelő
 * függvényke neveit.
 *
 * Ha valamit INLINE-ként valósít meg, akkor annak a string5.h-ba kell kerülnie,
 * akár kívül akár osztályon belül definiálja. (Az inline függvényeknek minden
 * fordítási egységben elérhetőknek kell lenniük)
 * *
 * A teszteléskor ne felejtse el beállítani a string5.h állományban az ELKESZULT makrót.
 *
 */

#ifdef _MSC_VER
// MSC ne adjon figyelmeztető üzenetet a C sztringkezelő függvényeire
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>             // Kiíratáshoz
#include <cstring>              // Sztringműveletekhez

#include "memtrace.h"           // a standard headerek után kell lennie
#include "string5.h"


/// Konstruktorok: egy char karakterből (createString)
///                egy nullával lezárt char sorozatból (createString)

/// Char paraméteres konstruktor
String::String(char ch)
{
  len = 1;
  pData = new char[2];
  pData[0] = ch;
  pData[1] = 0;
}

/// C string paraméteres konstruktor
String::String(const char* str)
{
  len = strlen(str);
  pData = new char[len+1];
  strcpy(pData, str);
}

/// Másoló konstruktor: String-ből készít (createString)
String::String(const String& string)
{
  len = string.len;
  pData = new char[len+1];
  strcpy(pData, string.pData);
}

/// Destruktor (disposeString)

/// operator=
String& String::operator=(const String& string)
{
  if (this != &string)
  {
  delete[] pData;
  len = string.len;
  pData = new char[len+1];
  strcpy(pData, string.pData);
  }
  return *this;
}

/// [] operátorok: egy megadott indexű elem REFERENCIÁJÁVAL térnek vissza (charAtString)
/// indexhiba esetén const char * kivételt dob!
char& String::operator[](size_t idx)
{
  if (idx >= len) throw "String index hiba";
  return pData[idx];
}
/*const char& String::operator[](size_t idx) const {
  return this->operator[](idx);
}*/


/// + operátorok:
///                 String-hez jobbról karaktert ad (addString)
String String::operator+(char ch) const
{
  String retStr;
  retStr.len = this->len+1;
  retStr.pData = new char[retStr.len+1];
  strcpy(retStr.pData, pData);
  retStr.pData[retStr.len-1] = ch;
  retStr.pData[retStr.len] = 0;

  return retStr;
}

///                 String-hez String-et ad (addString)
String String::operator+(const String& string) const
{
  String retStr;
  retStr.len = this->len + string.len;
  retStr.pData = new char[retStr.len+1];
  strcpy(retStr.pData, this->pData);
  strcat(retStr.pData, string.pData);

  return retStr;
}

String operator+(char ch, const String& string)
{
  String retStr(ch);
  retStr = retStr + string;
  return retStr;
}

/// << operator, ami kiír az ostream-re
std::ostream& operator<<(std::ostream& ostr, const String& string)
{
  ostr << string.c_str();
  return ostr;
}

std::istream& operator>>(std::istream& istr, String& string)
{
  char temp;
  string = "";
  std::ios_base::fmtflags flags = istr.flags();
  istr >> std::skipws;
  while (istr >> temp)
  {
    istr >> std::noskipws;
    if (temp == ' ') {
      istr.putback(temp);
      break;
    } else
      string = string + temp;
  }
  istr.setf(flags);
  return istr;
}


/// >> operátor, ami beolvas az istream-ről egy szót
