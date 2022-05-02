#include <iostream>

// 1. 
long  glob = 0;
float fglob;

// 2. 
long& fr()
{
    return glob;
}

// 3. 
/*int& fifi()
{
    int a;
    return a;
}*/

// 4. 
/*int *fp()
{
    int a;
    return &a;
}*/

// 5. 
long& fr(long& a, char c)
{
    return a;
}

// 6. 
/*long& fr(long x)
{
    return x;
}*/


// 7. 
/*float& fr(long x)
{
    return fglob;
}*/

// 8. 
float szg(int a = 1, float x = 0)
{
    return a * x;
}


// 9. 
int main()
{
    fr()++;
    fr() = 54;
    fr() = fr() + 4;
    std::cout << glob;
    return 0;
}
