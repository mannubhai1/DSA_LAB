#ifndef MYRBTREE_H
#define MYRBTREE_H

#include "points.h"

class Node
{
public:
    Point p;
    Node *left;
    Node *right;
    Node *parent;
    bool isRed;
    Node(Point p)
    {
        this->p = p;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        isRed = true;
    }
    Node *uncle();
    Node *sibling();
    bool hasRedChild();
    bool isOnLeft();
};

// This is a red-black tree that stores Point objects.
// The tree is ordered by the x-coordinate of the Point, and if two
// points have the same x-coordinate, then the y-coordinate is used.
class myRBTree
{
public:
    Node *root;
    int numNodes;
    double sumX;
    double sumY;

    myRBTree();
    void insert(Point p);
    void remove(Point p);
    void clearTree();
    Node *find(Point p);
    void print();

private:
    void insert(Node *n);
    void remove(Node *n);
    Node *find(Node *n, Point p);
    void print(Node *n);
    void rotateLeft(Node *n);
    void rotateRight(Node *n);
    void swapColors(Node *n1, Node *n2);
    void swapValues(Node *n1, Node *n2);
    void fixInsert(Node *n);
    // void fixRemove(Node *n);
    void fixRedRed(Node *n);
    void fixDoubleBlack(Node *n);
    void transplant(Node *u, Node *v);
    Node *minimum(Node *n);
    Node *maximum(Node *n);
    Node *successor(Node *n);
    Node *predecessor(Node *n);
    Node *getReplacement(Node *n);
};

#endif