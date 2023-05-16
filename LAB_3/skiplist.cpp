#include <bits/stdc++.h>
using namespace std;
#define loop(o, n) for (int i = o; i < n; i++)

int t;
class node
{
public:
    int data;
    node *next;
    node *down;
    node *top;
    node(int dat)
    {
        data = dat;
        next = nullptr;
        down = nullptr;
        top = nullptr;
    }
};

vector<node *> head{};
vector<node *> tail{};
int level(int l)
{
    int n = 1;
    l = l - 1;
    int k = pow(2, n);
    while (l / k != 0)
    {
        n++;
        k = pow(2, n);
    }
    return n;
}

void push(int val, int l)
{
    if (head.size() == l)
    {
        node *newnode = new node(val);
        head.push_back(newnode);
        if (l > 0)
        {
            head[l]->down = head[l - 1];
            head[l - 1]->top = head[l];
        }
    }
    else if (tail.size() == l)
    {
        node *newnode = new node(val);
        tail.push_back(newnode);
        head[l]->next = tail[l];
        if (l < head.size() - 1)
            tail[l]->top = head[l + 1];
        if (l > 0)
        {
            tail[l]->down = tail[l - 1];
            tail[l - 1]->top = tail[l];
        }
    }
    else
    {
        node *newnode;
        newnode = tail[l];
        tail[l] = new node(val);
        newnode->next = tail[l];
        if (l < head.size() - 1)
            tail[l]->top = newnode->top;
        if (l > 0)
            tail[l]->down = tail[l - 1];
    }
}

void skiplinkedlist(int a[], int n)
{
    loop(0, n)
    {
        int k = 2 * i;
        int l = 0;
        while (k % 2 == 0 && l < level(n))
        {
            push(a[i], l);
            l++;
            k = k / 2;
        }
    }
}
node *insertafter;
void skiplist(int x)
{
    int l = head.size() - 1;
    node *soln = head[l];
    node *next = soln->next;
    // cout<<next->data;
    int k = soln->data;
    while (k != x)
    {
        if (l == 0 && next == nullptr)
            break;
        if (l == 0 && next->data > x)
            break;
        if (next == nullptr)
        {
            soln = soln->down;
            l--;
            next = soln->next;
        }
        else if (next->data > x)
        {
            soln = soln->down;
            l--;
            next = soln->next;
        }
        else
        {
            soln = soln->next;
            next = next->next;
        }
        k = soln->data;
    }
    while (l != 0)
    {
        soln = soln->down;
        l--;
    }
    insertafter = soln;
}
void insert(int x)
{
    int l = head.size();
    int r = 1;
    if (x < head[0]->data)
    {
        while (l > 0)
        {
            node *newnode;
            newnode = head[l - 1];
            head[l - 1] = new node(x);
            head[l - 1]->next = newnode;
            if (l < head.size())
            {
                head[l]->down = head[l - 1];
                head[l - 1]->top = head[l];
            }
            l--;
        }
    }
    else
    {
        skiplist(x);
        node *newnode = new node(x);
        newnode->next = insertafter->next;
        newnode->top = insertafter->top;
        insertafter->next = newnode;
        int n = (rand() % 2);
        insertafter = insertafter->top;
        node *link = newnode;
        while (n != 0 && r < l)
        {
            cout << n;
            node *newnode = new node(x);
            newnode->next = insertafter->next;
            newnode->top = insertafter->top;
            insertafter->next = newnode;
            newnode->down = link;
            link->top = newnode;
            link = newnode;
            insertafter = insertafter->top;
            n = (rand() % 2);
        }
    }
}
int main()
{
    int arr[] = {1, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    skiplinkedlist(arr, n);
    insert(2);
    cout << head[1]->next->top->data;

    // cout<<level(n);
    /* skiplinkedlist(arr,n);
   skiplist(2);
   cout<<insertafter->top->top->data;
    node* soln=tail[2];
    soln=soln->down;
    soln=soln->next;
     soln=soln->down;
    soln=soln->next;
  cout<<head[2]->next->down->next->down->data;  */
}
