#include <bits/stdc++.h>
using namespace std;

int safe(int x, int y, int A[][100], int n)
{
    return (x >= 0 && x < n && y >= 0 && y < n && A[x][y] == -1);
}

void printSolution(int A[][100], int n)
{
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < n; y++)
            cout << " " << setw(2) << A[x][y] << " ";
        cout << endl;
    }
}

int SOLN(int x, int y, int count, int A[][100], int B[8], int C[8], int n)
{
    int next_x, next_y;
    if (count == n * n)
        return 1;

    for (int i = 0; i < 8; i++)
    {
        next_x = x + B[i];
        next_y = y + C[i];
        if (safe(next_x, next_y, A, n))
        {
            A[next_x][next_y] = count;
            if (SOLN(next_x, next_y, count + 1, A, B, C, n) == 1)
                return 1;
            else
                A[next_x][next_y] = -1;
        }
    }
    return 0;
}

int solve(int n)
{
    int A[n][100];

    for (int x = 0; x < n; x++)
        for (int y = 0; y < n; y++)
            A[x][y] = -1;
    int B[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int C[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    A[0][0] = 0;

    if (SOLN(0, 0, 1, A, B, C, n) == 0)
    {
        cout << "Solution does not exist";
        return 0;
    }
    else
        printSolution(A, n);

    return 1;
}

int main()
{
    int n;
    cin >> n;
    solve(n);
    return 0;
}