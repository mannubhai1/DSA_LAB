#include "myRBTree.h"
#include <iostream>
#include <vector>

using namespace std;

Node *Node::uncle()
{
    if (parent == nullptr || parent->parent == nullptr)
        return nullptr;
    if (parent == parent->parent->left)
        return parent->parent->right;
    else
        return parent->parent->left;
}

Node *Node::sibling()
{
    if (parent == nullptr)
        return nullptr;
    if (this == parent->left)
        return parent->right;
    else
        return parent->left;
}

bool Node::hasRedChild()
{
    if (left != nullptr && left->isRed)
        return true;
    if (right != nullptr && right->isRed)
        return true;
    return false;
}

bool Node::isOnLeft()
{
    return this == parent->left;
}

myRBTree::myRBTree()
{
    root = nullptr;
    numNodes = 0;
    sumX = 0;
    sumY = 0;
}

void myRBTree::insert(Point p)
{
    Node *n = new Node(p);
    insert(n);
}

void myRBTree::insert(Node *n)
{
    Node *y = nullptr;
    Node *x = root;
    while (x != nullptr)
    {
        y = x;
        if (n->p.x < x->p.x || (n->p.x == x->p.x && n->p.y < x->p.y))
            x = x->left;
        else
            x = x->right;
    }
    n->parent = y;
    if (y == nullptr)
        root = n;
    else if (n->p.x < y->p.x || (n->p.x == y->p.x && n->p.y < y->p.y))
        y->left = n;
    else
        y->right = n;
    numNodes++;
    sumX += n->p.x;
    sumY += n->p.y;
    fixInsert(n);
}

void myRBTree::remove(Point p)
{
    Node *n = find(p);
    if (n != nullptr)
    {
        remove(n);
    }
}

// void myRBTree::remove(Node *n)
// {
//     Node *y = n;
//     Node *x;
//     bool yOriginalColor = y->isRed;
//     if (n->left == nullptr)
//     {
//         x = n->right;
//         transplant(n, n->right);
//     }
//     else if (n->right == nullptr)
//     {
//         x = n->left;
//         transplant(n, n->left);
//     }
//     else
//     {
//         y = minimum(n->right);
//         yOriginalColor = y->isRed;
//         x = y->right;
//         if (y->parent == n)
//             x->parent = y;
//         else
//         {
//             transplant(y, y->right);
//             y->right = n->right;
//             y->right->parent = y;
//         }
//         transplant(n, y);
//         y->left = n->left;
//         y->left->parent = y;
//         y->isRed = n->isRed;
//     }
//     if (!yOriginalColor)
//         fixRemove(x);
// numNodes--;
// sumX -= n->p.x;
// sumY -= n->p.y;
//     delete n;
// }

void myRBTree::remove(Node *n)
{
    Node *m = getReplacement(n);
    bool nmBlack = ((m == nullptr || m->isRed == false) && (n->isRed == false));
    Node *parent = n->parent;

    if (m == nullptr)
    {
        if (n == root)
        {
            root = nullptr;
        }
        else
        {
            if (nmBlack)
            {
                fixDoubleBlack(n);
            }
            else
            {
                if (n->sibling() != nullptr)
                    n->sibling()->isRed = true;
            }

            if (n->isOnLeft())
            {
                parent->left = nullptr;
            }
            else
            {
                parent->right = nullptr;
            }
        }
        numNodes--;
        sumX -= n->p.x;
        sumY -= n->p.y;
        delete n;
        return;
    }
    if (n->left == nullptr || n->right == nullptr)
    {
        if (n == root)
        {
            n->p = m->p;
            n->left = n->right = nullptr;
            numNodes--;
            sumX -= m->p.x;
            sumY -= m->p.y;
            delete m;
        }
        else
        {
            if (n->isOnLeft())
            {
                parent->left = m;
            }
            else
            {
                parent->right = m;
            }
            numNodes--;
            sumX -= n->p.x;
            sumY -= n->p.y;
            delete n;
            m->parent = parent;
            if (nmBlack)
            {
                fixDoubleBlack(m);
            }
            else
            {
                m->isRed = false;
            }
        }
        return;
    }

    swapValues(n, m);
    remove(m);
}

void myRBTree::clearTree()
{
    vector<Node *> nodes;
    nodes.push_back(root);
    while (!nodes.empty())
    {
        Node *n = nodes.back();
        nodes.pop_back();
        if (n != nullptr)
        {
            nodes.push_back(n->left);
            nodes.push_back(n->right);
            delete n;
        }
    }
    root = nullptr;
    numNodes = 0;
    sumX = 0;
    sumY = 0;
}

Node *myRBTree::find(Point p)
{
    return find(root, p);
}

Node *myRBTree::find(Node *n, Point p)
{
    if (n == nullptr || (n->p.x == p.x && n->p.y == p.y))
        return n;
    if (p.x < n->p.x || (p.x == n->p.x && p.y < n->p.y))
        return find(n->left, p);
    else
        return find(n->right, p);
}

void myRBTree::print()
{
    print(root);
}

void myRBTree::print(Node *n)
{
    if (n == nullptr)
        return;
    print(n->left);
    cout << "(" << n->p.x << ", " << n->p.y << ") ";
    print(n->right);
}

void myRBTree::rotateLeft(Node *n)
{
    Node *y = n->right;
    n->right = y->left;
    if (y->left != nullptr)
        y->left->parent = n;
    y->parent = n->parent;
    if (n->parent == nullptr)
        root = y;
    else if (n == n->parent->left)
        n->parent->left = y;
    else
        n->parent->right = y;
    y->left = n;
    n->parent = y;
}

void myRBTree::rotateRight(Node *n)
{
    Node *y = n->left;
    n->left = y->right;
    if (y->right != nullptr)
        y->right->parent = n;
    y->parent = n->parent;
    if (n->parent == nullptr)
        root = y;
    else if (n == n->parent->right)
        n->parent->right = y;
    else
        n->parent->left = y;
    y->right = n;
    n->parent = y;
}

void myRBTree::swapColors(Node *n1, Node *n2)
{
    bool temp = n1->isRed;
    n1->isRed = n2->isRed;
    n2->isRed = temp;
}

void myRBTree::swapValues(Node *n1, Node *n2)
{
    Point temp = n1->p;
    n1->p = n2->p;
    n2->p = temp;
}

void myRBTree::fixInsert(Node *n)
{
    while (n != root && n->parent->isRed)
    {
        if (n->parent == n->parent->parent->left)
        {
            Node *y = n->parent->parent->right;
            if (y != nullptr && y->isRed)
            {
                n->parent->isRed = false;
                y->isRed = false;
                n->parent->parent->isRed = true;
                n = n->parent->parent;
            }
            else
            {
                if (n == n->parent->right)
                {
                    n = n->parent;
                    rotateLeft(n);
                }
                n->parent->isRed = false;
                n->parent->parent->isRed = true;
                rotateRight(n->parent->parent);
            }
        }
        else
        {
            Node *y = n->parent->parent->left;
            if (y != nullptr && y->isRed)
            {
                n->parent->isRed = false;
                y->isRed = false;
                n->parent->parent->isRed = true;
                n = n->parent->parent;
            }
            else
            {
                if (n == n->parent->left)
                {
                    n = n->parent;
                    rotateRight(n);
                }
                n->parent->isRed = false;
                n->parent->parent->isRed = true;
                rotateLeft(n->parent->parent);
            }
        }
    }
    root->isRed = false;
}

void myRBTree::fixRedRed(Node *n)
{
    if (n == root)
    {
        n->isRed = false;
        return;
    }
    Node *parent = n->parent, *grandparent = parent->parent, *uncle = n->uncle();
    if (parent->isRed)
    {
        if (uncle != nullptr && uncle->isRed)
        {
            grandparent->isRed = true;
            parent->isRed = false;
            uncle->isRed = false;
            fixRedRed(grandparent);
        }
        else
        {
            if (parent->isOnLeft())
            {
                if (n->isOnLeft())
                {
                    swapColors(parent, grandparent);
                }
                else
                {
                    rotateLeft(parent);
                    swapColors(n, grandparent);
                }
                rotateRight(grandparent);
            }
            else
            {
                if (n->isOnLeft())
                {
                    rotateRight(parent);
                    swapColors(n, grandparent);
                }
                else
                {
                    swapColors(parent, grandparent);
                }
                rotateLeft(grandparent);
            }
        }
    }
}

void myRBTree::fixDoubleBlack(Node *n)
{
    if (n == root)
    {
        return;
    }
    Node *sibling = n->sibling(), *parent = n->parent;
    if (sibling == nullptr)
    {
        fixDoubleBlack(parent);
    }
    else
    {
        if (sibling->isRed)
        {
            parent->isRed = true;
            sibling->isRed = false;
            if (sibling->isOnLeft())
            {
                rotateRight(parent);
            }
            else
            {
                rotateLeft(parent);
            }
            fixDoubleBlack(n);
        }
        else
        {
            if (sibling->hasRedChild())
            {
                if (sibling->left != nullptr && sibling->left->isRed)
                {
                    if (sibling->isOnLeft())
                    {
                        sibling->left->isRed = sibling->isRed;
                        sibling->isRed = parent->isRed;
                        rotateRight(parent);
                    }
                    else
                    {
                        sibling->left->isRed = parent->isRed;
                        rotateRight(sibling);
                        rotateLeft(parent);
                    }
                }
                else
                {
                    if (sibling->isOnLeft())
                    {
                        sibling->right->isRed = parent->isRed;
                        rotateLeft(sibling);
                        rotateRight(parent);
                    }
                    else
                    {
                        sibling->right->isRed = sibling->isRed;
                        sibling->isRed = parent->isRed;
                        rotateLeft(parent);
                    }
                }
                parent->isRed = false;
            }
            else
            {
                sibling->isRed = true;
                if (parent->isRed)
                {
                    parent->isRed = false;
                }
                else
                {
                    fixDoubleBlack(parent);
                }
            }
        }
    }
}

void myRBTree::transplant(Node *u, Node *v)
{
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != nullptr)
        v->parent = u->parent;
}

Node *myRBTree::minimum(Node *n)
{
    while (n->left != nullptr)
        n = n->left;
    return n;
}

Node *myRBTree::maximum(Node *n)
{
    while (n->right != nullptr)
        n = n->right;
    return n;
}

Node *myRBTree::successor(Node *n)
{
    if (n->right != nullptr)
        return minimum(n->right);
    Node *y = n->parent;
    while (y != nullptr && n == y->right)
    {
        n = y;
        y = y->parent;
    }
    return y;
}

Node *myRBTree::predecessor(Node *n)
{
    if (n->left != nullptr)
        return maximum(n->left);
    Node *y = n->parent;
    while (y != nullptr && n == y->left)
    {
        n = y;
        y = y->parent;
    }
    return y;
}

Node *myRBTree::getReplacement(Node *n)
{
    if (n->left != nullptr && n->right != nullptr)
        return successor(n);
    if (n->left == nullptr && n->right == nullptr)
        return nullptr;
    if (n->left != nullptr)
        return n->left;
    else
        return n->right;
}