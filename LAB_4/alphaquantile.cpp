#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct node
{
    int val;
    double wt;
};

int partition(struct node arr[], int left, int right)
{
    int x = arr[right].val;
    int i = left;
    for (int j = left; j <= right - 1; j++)
    {
        if (arr[j].val <= x)
        {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[right]);
    return i;
}

int quickSelect(struct node arr[], double k, int low, int high) 
{
    int p = arr[high].val;
    int index = partition(arr, low, high);
    double s = 0;
    for (int i = 0; i < index; i++)
    {
        s = s + arr[i].wt;
    }
    if (s <= k)
    {
        int min = index + 1;
        for (int i = index + 1; i <= high; i++)
        {
            if (arr[i].val < arr[min].val)
            {
                min = i;
            }
        }
        if (s + arr[index].wt > k)
        {
            int max = 0;
            for (int i = 0; i < index; i++)
            {
                if (arr[i].val > max)
                {
                    max = arr[i].val;
                }
            }
            return max;
        }

        else if (s + arr[index].wt + arr[min].wt > k)
        {
            return arr[index].val;
        }
        else
        {
            return quickSelect(arr, k, 0, index + 1);
        }
    }

    return quickSelect(arr, k, 0, index - 1);
}

int main()
{

    // cout<<"Enter n: ";
    int n;
    cin >> n;
    struct node arr[n];
    // cout<<"Enter Elements and their weights: "<<endl;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i].val >> arr[i].wt;
    }
    // cout<<"Enter k: ";
    double k;

    k = 0.9;
    cout << quickSelect(arr, k, 0, n - 1);
}