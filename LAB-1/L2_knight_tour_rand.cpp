#include <bits/stdc++.h>

using namespace std;

static int x[8] = {2, 2, -2, -2, -1, -1, 1, 1};
static int y[8] = {-1, 1, -1, 1, 2, -2, 2, -2};

bool check(int a, int b, int m[])
{
    int last = 8 * b + a;
    return ((b < 8 && b >= 0) && (a < 8 && a >= 0) && (m[last] < 0));
}

int degree(int m[], int a, int b)
{
    int c = 0;
    for (int i = 0; i < 8; i++)
        if (check((x[i] + i), (y[i] + b), m))
            c++;
    return c;
}

bool next_m(int m[], int *a, int *b)
{
    int min_dx = -1, c, min_d = 9, na, nb;
    int start = rand() % 8;
    for (int j = 0; j < 8; j++)
    {
        int i = (start + j) % 8;
        na = *a + x[i];
        nb = *b + y[i];
        c = degree(m, na, nb);
        if (check(na, nb, m) && c < min_d)
        {
            min_dx = i;
            min_d = c;
        }
    }

    if (min_dx == -1)
        return false;

    na = *a + x[min_dx];
    nb = *b + y[min_dx];

    m[nb * 8 + na] = m[(*b) * 8 + (*a)] + 1;
    *a = na;
    *b = nb;

    return true;
}

bool find_t()
{
    int m[64];
    int ran_x = rand() % 8, ran_y = rand() % 8;

    for (int i = 0; i < 63; i++)
        m[i] = -1;

    int a = ran_x, b = ran_y;
    m[b * 8 + a] = 1;

    for (int i = 0; i < 63; ++i)
        if (next_m(m, &a, &b) == 0)
            return false;

    for (int i = 0; i < 8; i++)
    {
        if (((a + x[i]) == ran_x) && ((b + y[i]) == ran_y))
            return false;
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            cout << m[j * 8 + i] << " ";
        cout << '\n';
    }
    return true;
}

int main()
{
    srand(time(NULL));
    while (!find_t())
        ;
    return 0;
}
