#pragma once

#include "libH.h"

// алгоритм Евклида поиска наибольшего общего делителя

int NOD(int a, int b)
{
    while (a != 0 and b != 0)
    {
        if (a > b)
        {
            a = a % b;
        }
        else
        {
            b = b % a;
        }

    }
    return (a + b);
}

void ex_nod(void)
{
    cout << NOD(30, 18) << endl;
    cout << NOD(NOD(30, 18),40) << endl;
    cout << NOD(NOD(NOD(30, 18), 40),50) << endl;
    return;
}
