#include <bits/stdc++.h>
using namespace std;
#define fr(o, n)                \
    for (int i = o; i < n; i++) \
        ;

int quicksort(int a[], int p, int l, int h)
{

    if (l == h)
        return l;
    if (p == l)
    {
        while (a[h] > a[p])
        {
            h--;
        }
        if (p == h)
            return p;
        else
        {
            swap(a[p], a[h]);
            return quicksort(a, h, p, h);
        }
    }
    else
    {
        while (a[l] < a[p])
        {
            l++;
        }
        if (p == l)
            return p;
        else
        {
            swap(a[p], a[l]);
            return quicksort(a, l, l, p);
        }
    }
}

void quick(int a[], int l, int h)
{
    if (h <= l)
        return;
    int c = quicksort(a, l, l, h);
    int d = quicksort(a, h, l, h);
    if (d < c)
    {
        quick(a, l, d - 1);
        quick(a, d + 1, c - 1);
        quick(a, c + 1, h);
    }
    else
    {
        quick(a, l, c - 1);
        quick(a, c + 1, d - 1);
        quick(a, d + 1, h);
    }
}

int main()
{
    int a[8] = {4, 10, 6, 9, 3, 2, 7, 8};
    quick(a, 0, 7);
    for (int i = 0; i < 8; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}