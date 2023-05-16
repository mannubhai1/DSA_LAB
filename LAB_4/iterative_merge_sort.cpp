#include <bits/stdc++.h>
using namespace std;

void merge(int A[], int low, int mid, int high)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = A[low + i];
    for (int j = 0; j < n2; j++)
        R[j] = A[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = low;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            A[k] = L[i];
            i++;
        }
        else
        {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        A[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        A[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int A[], int low, int high)
{
    int n = 6;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            int mid = j + i - 1;
            int high = min(j + 2 * i - 1, n - 1);
            merge(A, j, mid, high);
        }
    }
}

int main()
{
    int A[] = {12, 11, 13, 5, 6, 7};
    int len = sizeof(A) / sizeof(A[0]);

    mergeSort(A, 0, len - 1);

    for (auto &e : A)
        cout << e << " ";
    return 0;
}