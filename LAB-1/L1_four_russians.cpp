// #include <bits/stdc++.h>
// using namespace std; // t= 2^b  m=n/b

// const unsigned int n = 13;

// int binaryToDecimal(unsigned long long s)
// {
//     int num = s;
//     int dec_value = 0;

//     // Initializing base value to 1, i.e 2^0
//     int base = 1;

//     int temp = num;
//     while (temp)
//     {
//         int last_digit = temp % 10;
//         temp = temp / 10;

//         dec_value += last_digit * base;

//         base = base * 2;
//     }

//     return dec_value;
// }

// int LSB(unsigned int x)
// {
//     int i = 0;
//     for (i; x & (1 << i) == 0; i++)
//         return i;
// }

// void soln(int b, int B[n][n], bool T[][1000][n], int m)
// {
//     int cnt = 0;
//     int ans[n];
//     int soln[n] = {0};
//     int C[n][n] = {0};
//     while (cnt < n)
//     {
//         for (int tn = 0; tn < m; tn++)
//         {
//             for (int i = 0; i < n - b; i += b)
//             {
//                 int num = 0;
//                 for (int j = i; j < b + i; j++)
//                 {
//                     num = num * 10 + B[cnt][j];
//                 }

//                 int dec = binaryToDecimal(num);

//                 for (int k = 0; k < n; k++)
//                 {
//                     ans[k] = T[tn][dec][k];
//                 }
//                 // ans+= T[cnt][dec];
//             }

//             for (int i = 0; i < n; i++)
//                 soln[i] = soln[i] | ans[i];
//         }
//         for (int j = 0; j < n; j++)
//         {
//             C[j][cnt] = soln[j];
//         }
//         cnt++;
//     }
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < n; j++)
//         {
//             cout << C[i][j] << " ";
//         }
//         cout << endl;
//     }
//     return;
// }

// void formTable(int b, int A[n][n], int B[n][n])
// {
//     int m = n / b;
//     int q = 0;
//     int t = (int)pow(2, b);
//     bool T[m][1000][n] = {0};
//     for (int index = 0; index < m; index++)
//     {
//         for (int j = 0; j < t; j++)
//         {
//             q = LSB(j);
//             int jp = j ^ ~(1 << q);
//             for (int k = 0; k < 32; k++)
//             {
//                 T[index][j][k] = T[index][jp][k] | A[index][q + index];
//             }
//         }
//     }
//     soln(b, B, T, m);
//     return;
// }

// int main()
// {
//     // unsigned int n;
//     // cin>>n;
//     int A[n][n], B[n][n];
//     unsigned int b = ceil(log2(n));
//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < n; j++)
//             cin >> A[i][j];
//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < n; j++)
//             cin >> B[i][j];
//     formTable(b, A, B);
//     return 0;
// }
#include <bits/stdc++.h>
using namespace std;

vector<vector<vector<bool>>> t; // table
int n, b, k;                    // total size, sub part size, no. of sub parts

int lsb(int num)
{
    int c = 0;
    int p = num & 1;
    while ((p == 0) && c < 32)
    {
        num = num >> 1;
        p = num & 1;
        c++;
    }

    if (c == 32)
        return 0;
    return c;
}

int b_d(vector<vector<int>> &cc, int b, int start, int n)
{
    int sz = cc.size();
    int s = 0;
    for (int i = start + b - 1; i >= start; i--)
    {
        if (i < sz)
            s = s * 2 + cc[i][n];

        else
            s = s * 2 + 0;
    }
    return s;
}

void table(int n, int b, int k, vector<vector<int>> &a, vector<vector<vector<bool>>> &t)
{
    int r = int(pow(2, b)); // 2 pow b
    t.resize(k, vector<vector<bool>>(r, vector<bool>(n)));

    for (int j = 0; j < k; j++)
    {
        for (int i = 0; i < n; i++)
            t[j][0][i] = 0;

        for (int l = 1; l < r; l++)
        {
            int q = lsb(l);
            int l1 = l & (~(1 << q));

            for (int i = 0; i < n; i++)
            {
                t[j][l][i] = t[j][l1][i] | a[i][(q + j * b)];
            }
        }
    }
}

void print_v(vector<vector<int>> &cc)
{
    for (vector<int> i : cc)
    {
        for (int j : i)
        {
            cout << j << " ";
        }

        cout << endl;
    }
}

int main()
{
    cin >> n;
    vector<vector<int>> cx(n, vector<int>(n));
    vector<vector<int>> cy(n, vector<int>(n));
    vector<vector<int>> cc(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> cx[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cin >> cy[i][j];
    }

    int b = int(ceil(log2(n)));
    k = int(ceil(n / float(b))); // number of subgroups
    // length of subgroup

    table(n, b, k, cx, t);  // table formin
    int r = int(pow(2, b)); // rows

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            int d = b_d(cy, b, j * b, i);
            for (int h = 0; h < n; h++)
            {
                cc[h][i] |= t[j][d][h];
                // cout <<cc[h][i];
            }
        }
    }

    print_v(cc);
}
