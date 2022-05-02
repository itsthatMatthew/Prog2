/**
 * \file swap.cpp
 */
#include "swap.h"

void swap(bool& a, bool& b) {
    bool temp = a;
    a = b;
    b = temp;

    return;
}

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;

    return;
}

void swap(char& a, char& b) {
    char temp = a;
    a = b;
    b = temp;

    return;
}

void swap(double& a, double& b) {
    double temp = a;
    a = b;
    b = temp;

    return;
}

void swap(const char*& a, const char*& b) {
    const char* temp = a;
    a = b;
    b = temp;

    return;
}