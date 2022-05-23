#ifndef COMMON_H
#define COMMON_H

void
swap(int * a, int * b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

#endif // COMMON_H