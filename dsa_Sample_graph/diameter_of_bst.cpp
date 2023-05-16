#include <bits/stdc++.h>

using namespace std;

struct node
{
    int data;
    node* right;
    node* left;

    node(int data)
    {
        this->data = data;
        this->right = NULL;
        this->left = NULL;
    }
    
};


int height(node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    
   int l =  height(root->left);
    int r = height(root->right);
    return max (r,l)+1;

}

void diameter (node *root, int &d)
{
    if (root == NULL)
    {
        return;
    }
    int h = 0;
    int l = 0;
    int r = 0;
     l =height(root->left);
    r =height(root->right);
    d = max(d, l+r+1);
    diameter(root->left, d);
    diameter(root->right, d);
}

int main()
{
  

    // int data;
    // cin >> data;
     node *root = new node(10);
    root->left = new node(20);
    root->right = new node(30);
    root->left->left= new node (40);
     root->left->right=  new node(60); 
    
    
    
    int d = 0;
    diameter(root, d);
    cout << d << endl;
    return 0;
}
