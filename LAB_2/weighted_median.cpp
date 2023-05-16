#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define MAX_ELEMENTS 100

struct node
{
    int value;
    int wt;
};

int parent(int a)
{
    return (a / 2);
}

int left(int a)
{
    return (2 * a);
}

int right(int a)
{
    return (2 * a + 1);
}

void swap(int a, int b, struct node Arr[])
{
    struct node temp;
    temp.value = Arr[a - 1].value;
    temp.wt = Arr[a - 1].wt;

    Arr[a - 1].value = Arr[b - 1].value;
    Arr[a - 1].wt = Arr[b - 1].wt;

    Arr[b - 1].value = temp.value;
    Arr[b - 1].wt = temp.wt;
}

int maxIndex(int a, int b, int c, struct node Arr[])
{
    if (Arr[a - 1].value >= Arr[b - 1].value && Arr[a - 1].value >= Arr[c - 1].value)
        return a;
    else if (Arr[b - 1].value >= Arr[a - 1].value && Arr[b - 1].value >= Arr[c - 1].value)
        return b;
    return c;
}

int maxIndex2(int a, int b, struct node Arr[])
{
    if (Arr[a - 1].value >= Arr[b - 1].value)
        return a;
    return b;
}

int minIndex(int a, int b, int c, struct node Arr[])
{
    if (Arr[a - 1].value <= Arr[b - 1].value && Arr[a - 1].value <= Arr[c - 1].value)
        return a;
    else if (Arr[b - 1].value <= Arr[a - 1].value && Arr[b - 1].value <= Arr[c - 1].value)
        return b;
    return c;
}

int minIndex2(int a, int b, struct node Arr[])
{
    if (Arr[a - 1].value <= Arr[b - 1].value)
        return a;
    return b;
}

void max_heapify_upwards(int a, struct node Arr[])
{
    int n = a;
    if (a == 1)
    {
        return;
    }
    int m = maxIndex2(a, parent(a), Arr);

    if (a == m)
    {
        swap(a, parent(a), Arr);
        max_heapify_upwards(m, Arr);
    }
}

void min_heapify_upwards(int a, struct node Arr[])
{
    int n = a;
    if (a == 1)
    {
        return;
    }
    int m = minIndex2(a, parent(a), Arr);

    if (a == m)
    {
        swap(a, parent(a), Arr);
        min_heapify_upwards(m, Arr);
    }
}

void max_heapify_downwards(int a, struct node Arr[], int n)
{
    if (a > n / 2)
    {
        return;
    }
    int m = maxIndex(a, left(a), right(a), Arr);

    if (a != m)
    {
        swap(a, m, Arr);
        max_heapify_downwards(m, Arr, n);
    }
}

void min_heapify_downwards(int a, struct node Arr[], int n)
{
    if (a > n / 2)
    {
        return;
    }
    int m = minIndex(a, left(a), right(a), Arr);

    if (a != m)
    {
        swap(a, m, Arr);
        min_heapify_downwards(m, Arr, n);
    }
}

void deleteRootfromMaxHeap(struct node Arr[], int c1)
{
    struct node c;
    c.value = Arr[0].value;
    c.wt = Arr[0].wt;

    Arr[0].value = Arr[c1 - 1].value;
    Arr[0].wt = Arr[c1 - 1].wt;
    c1--;
    if (Arr[0].value < Arr[left(1) - 1].value || Arr[0].value < Arr[right(1) - 1].value)
    {
        max_heapify_downwards(1, Arr, c1);
    }
}

void deleteRootfromMinHeap(struct node Arr[], int c2)
{
    struct node c;
    c.value = Arr[0].value;
    c.wt = Arr[0].wt;

    Arr[0].value = Arr[c2 - 1].value;
    Arr[0].wt = Arr[c2 - 1].wt;
    c2--;
    if (Arr[0].value > Arr[left(1) - 1].value || Arr[0].value > Arr[right(1) - 1].value)
    {
        min_heapify_downwards(1, Arr, c2);
    }
}

int main()
{
    struct node H1[100];
    struct node H2[100];

    for (int i = 0; i < 100; i++)
    {
        H1[i].value = 0;
        H1[i].wt = 0;
        H2[i].value = 0;
        H2[i].wt = 0;
    }

    unsigned int s1 = 0; // sum of weights in H1
    unsigned int s2 = 0; // sum of weights in H2

    unsigned int c1 = 0; // elements in H1
    unsigned int c2 = 0; // elements in H2

    int k = 1;
    int a, w, sum;
    // int ele[5] = {2, 3, 5, 4, 1};
    // int wts[5] = {2, 1, 4, 1, 2};
    int ele[5] = {10, 1, 3, 9, 4};
    int wts[5] = {4, 1, 2, 3, 10};      
    while (k <= 5)
    {
        a = ele[k - 1];
        w = wts[k - 1];
        if (a == EOF || w == EOF)
        {
            break;
        }

        if (a >= H1[0].value)
        {
            s2 = s2 + w;
            H2[(++c2) - 1].value = a;
            H2[c2 - 1].wt = w;
            min_heapify_upwards(c2, H2);
            sum = s1 + s2;
            while ((float)s1 / sum < 0.5)
            {
                if ((float)(s1 + H2[0].wt) / sum <= 0.5)
                {
                    s1 = s1 + H2[0].wt;
                    s2 = s2 - H2[0].wt;
                    H1[(++c1) - 1].value = H2[0].value;
                    H1[c1 - 1].wt = H2[0].wt;
                    max_heapify_upwards(c1, H1);
                    deleteRootfromMinHeap(H2, c2);
                    c2--;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            s1 = s1 + w;
            H1[(++c1) - 1].value = a;
            H1[c1 - 1].wt = w;
            max_heapify_upwards(c1, H1);
            sum = s1 + s2;
            while ((float)s1 / sum > 0.5)
            {
                s1 = s1 - H1[0].wt;
                s2 = s2 - H1[0].wt;
                H2[(++c2) - 1].value = H1[0].value;
                H2[c2 - 1].wt = H1[0].wt;
                deleteRootfromMaxHeap(H1, c1);
                c1--;
            }
        }
        k++;
    }
    cout << "The weighted median is: " << H1[0].value;
    return 0;
}