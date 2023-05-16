#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>

using namespace std;

class Node
{
    int value;
    Node *ltree;
    Node *rtree;
    int lcount = 0;
    int rcount = 0;

public:
    Node();

    Node(int);

    int getValue(Node *root);

    Node *builder(int in[], int post[], int start, int end, int *postIndex);

    Node *generateTree(int inorder[], int postorder[], int n);

    Node *Find(int x, Node *root);

    Node *InsertinTree(int x, Node *root);

    Node *DeleteNode(int x, Node *root);

    void InorderTraverse(Node *root);

    void PreorderTraverse(Node *root);

    void PostorderTraverse(Node *root);

    void LevelorderTraverse(Node *root);

    bool checkBST(Node *root, Node **prev);

    bool isBST(Node *root);

    Node *FindPrevious(Node **head, int x, Node *prev);

    Node *Predecessor(int x, Node *root);

    Node *FindNext(Node **head, int x, Node *next);

    Node *Successor(int x, Node *root);

    Node *Select(int k, Node *root);

    int Diameter(Node *root);

    int Height(Node *root);

    int LowestCommonAncestor(Node *root, int x, int y);

    int MaxFind(Node *root, int &res);

    int MaxPathSum(Node *root);
};

#endif // end DSALAB07BST_H