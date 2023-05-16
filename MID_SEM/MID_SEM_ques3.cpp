#include <bits/stdc++.h>
using namespace std;

void insert_element(vector<int> &A, int x, int k)
{
    A.push_back(x);
    int child_i = A.size() - 1;       // last element
    int parent_i = (child_i - 1) / k; // if all the k elements are not filled, then parent index will be the root index,,
                                      // else it will divide by k , to get the parent index
    while (parent_i >= 0 && A[child_i] > A[parent_i])
    {
        swap(A[child_i], A[parent_i]);
        child_i = parent_i; // updates child and parent indicess
        parent_i = (child_i - 1) / k;
    }
}

void Remove_top_element(vector<int> &A, int k) // removes the top element then again do the operations
{
    A[0] = A[A.size() - 1]; // largest element will come in the first pos
    A.pop_back();           // which is swapped by the last number , and popped out
                            // we need not store max element as we will print it before removing it
    int parent_i = 0;

    while (true)
    {
        int l = parent_i; // l will store the index of the maximum element
        int i = k * parent_i + 1;
        while (i <= k * (parent_i + 1) && i < A.size()) // checks first layer of child and then compare the max value index with
        {                                               // parent index , if the index is not same , we swap and check the next layer
            if (A[l] < A[i])
            {
                l = i;
            }
            i++;
        }
        if (l == parent_i)
        {
            break;
        }
        else
        {
            swap(A[parent_i], A[l]);
            parent_i = l;
        }
    }
}

int Extract_Max(vector<int> &A)
{
    return A[0];
}

int main()
{
    vector<int> A;
    int k;
    cin >> k;
    insert_element(A, 66, k);
    insert_element(A, 15, k);
    insert_element(A, 10, k);
    insert_element(A, 9, k);
    insert_element(A, 1, k);
    insert_element(A, 34, k);
    insert_element(A, 88, k);
    // insert_element(A, 4, k);
    // insert_element(A, 5, k);
    // insert_element(A, 2, k);
    // insert_element(A, 1, k);

    cout << Extract_Max(A) << endl;

    Remove_top_element(A, k);

    return 0;
}