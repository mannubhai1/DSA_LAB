#include "binary_tree.h"
#include <cstdio>
#include <climits>
#include <queue>

/*Constructor*/

Node ::Node() : value(0), ltree(NULL), rtree(NULL), lcount(0), rcount(0) {}

/*Constructor with value initialization*/

Node ::Node(int x)
{
    value = x;
    ltree = NULL;
    rtree = NULL;
    lcount = rcount = 0;
}

/*Returns Value*/

int Node::getValue(Node *root)
{
    return root->value;
}

/*Helper Function to build the tree from given inorder and postorder sequences*/

Node *Node::builder(int in[], int post[], int start, int end, int *postIndex)
{
    if (start > end)
    {
        return NULL;
    }

    Node *b = new Node(post[*postIndex]);
    (*postIndex)--;

    if (start == end)
    {
        return b;
    }

    int i;
    for (i = start; i <= end; i++)
    {
        if (in[i] == (b->value))
        {
            break;
        }
    }
    b->lcount = i;
    b->rcount = (end - i - 1);

    b->rtree = builder(in, post, i + 1, end, postIndex);
    b->ltree = builder(in, post, start, i - 1, postIndex);

    return b;
}

/*Function that generates the tree from given inorder and postorder arrays using a helper function*/

Node *Node::generateTree(int inorder[], int postorder[], int n)
{
    int postIndex = n - 1;
    return builder(inorder, postorder, 0, n - 1, &postIndex);
}

/*Function that finds a particular node in the Node*/

Node *Node::Find(int x, Node *root)
{
    cout << root->value << "->";
    if (root->ltree == NULL && root->rtree == NULL && root->value != x)
    {
        return NULL;
    }
    else if (root->value == x)
    {
        return root;
    }
    else if (root->value > x)
    {
        return Find(x, root->ltree);
    }
    return Find(x, root->rtree);
}

/*Function that inserts a node in the Node*/

Node *Node::InsertinTree(int x, Node *root)
{
    if (root == NULL)
    {
        return new Node(x);
    }

    if (x > root->value)
    {
        root->rcount++;
        root->rtree = InsertinTree(x, root->rtree);
    }
    else if (x < root->value)
    {
        root->lcount++;
        root->ltree = InsertinTree(x, root->ltree);
    }
    return root;
}

/*Function that deletes a node in the Node*/

Node *Node::DeleteNode(int x, Node *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->value < x)
    {
        root->rcount--;
        root->rtree = DeleteNode(x, root->rtree);
    }
    else if (root->value > x)
    {
        root->lcount--;
        root->ltree = DeleteNode(x, root->ltree);
    }
    else
    {
        if (root->ltree == NULL && root->rtree == NULL) // When the node is a leaf
        {
            delete root;
            root = NULL;
        }
        else if (root->ltree == NULL) // When the node has a right child
        {
            Node *temp = root;
            root = root->rtree;
            delete temp;
        }
        else if (root->rtree == NULL) // When the node has a left child
        {
            Node *temp = root;
            root = root->ltree;
            delete temp;
        }
        else
        { // When the node has both children
            Node *temp = root->rtree;
            while (temp->ltree != NULL)
            {
                temp = temp->ltree;
            }
            root->value = temp->value;
            root->rtree = DeleteNode(temp->value, root->rtree);
        }
    }
    return root;
}

/*Function to perform Inorder Traversal*/

void Node::InorderTraverse(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    InorderTraverse(root->ltree);
    cout << root->value << " ";
    InorderTraverse(root->rtree);
    return;
}

/*Function to perform Preorder Traversal*/

void Node::PreorderTraverse(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    cout << root->value << " ";
    PreorderTraverse(root->ltree);
    PreorderTraverse(root->rtree);
    return;
}

/*Function to perform Postorder Traversal*/

void Node::PostorderTraverse(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    PostorderTraverse(root->ltree);
    PostorderTraverse(root->rtree);
    cout << root->value << " ";
    return;
}

/*Function to perform Level-order Traversal*/

void Node::LevelorderTraverse(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        int n = q.size();

        for (int i = 0; i < n; i++)
        {
            Node *temp = q.front();
            q.pop();
            cout << temp->value << " ";
            if (temp->ltree != NULL)
            {
                q.push(temp->ltree);
            }
            if (temp->rtree != NULL)
            {
                q.push(temp->rtree);
            }
        }
    }
}

/*Helper function for determining if a given tree is a Node*/

bool Node::checkBST(Node *root, Node **prev)
{
    if (root == NULL)
    {
        return true;
    }
    if (!checkBST(root->ltree, prev))
    {
        return false;
    }
    if (*prev != NULL && (*prev)->value >= root->value)
    {
        return false;
    }
    *prev = root;
    return checkBST(root->rtree, prev);
}

/*Function to check if a given binary tree is a Node or not*/

bool Node::isBST(Node *root)
{
    Node *prev = NULL;
    return checkBST(root, &prev);
}

/*Helper function to find the predecessor of a node*/

Node *Node::FindPrevious(Node **head, int x, Node *prev)
{
    Node *root = *head;
    if (root == NULL)
    {
        return NULL;
    }
    if (root->value == x)
    {
        if (root->ltree != NULL)
        {
            Node *temp = root->ltree;
            while (temp->rtree != NULL)
            {
                temp = temp->rtree;
            }
            return temp;
        }
        else
        {
            return prev;
        }
    }
    else if (root->value > x)
    {
        return FindPrevious(&(root->ltree), x, prev);
    }
    return FindPrevious(&(root->rtree), x, root);
}

/*Function that returns the predecessor of a node*/

Node *Node::Predecessor(int x, Node *root)
{
    return FindPrevious(&root, x, NULL);
}

/*Helper function to find the successor of a node*/

Node *Node::FindNext(Node **head, int x, Node *next)
{
    Node *root = *head;
    if (root == NULL)
    {
        return NULL;
    }
    if (root->value == x)
    {
        if (root->rtree != NULL)
        {
            Node *temp = root->rtree;
            while (temp->ltree != NULL)
            {
                temp = temp->ltree;
            }
            return temp;
        }
        else
        {
            return next;
        }
    }
    else if (root->value > x)
    {
        return FindNext(&(root->ltree), x, root);
    }
    return FindNext(&(root->rtree), x, next);
}

/*Function that returns the successor of a node*/

Node *Node::Successor(int x, Node *root)
{
    return FindNext(&root, x, NULL);
}

Node *Node::Select(int k, Node *root)
{
    if (root != NULL)
    {
        if ((root->lcount) + 1 == k)
        {
            return root;
        }
        else if (k <= root->lcount)
        {
            return Select(k, root->ltree);
        }
        return Select(k - (root->lcount) - 1, root->rtree);
    }
    return NULL;
}

/*Function to return the diameter of the tree*/

int Node::Diameter(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }

    int left = Diameter(root->ltree);
    int right = Diameter(root->rtree);

    return (max(Height(root->ltree) + Height(root->rtree) + 1, max(left, right)));
}

/*Function that returns the height of the tree*/

int Node::Height(Node *root)
{
    if (root == NULL)
    {
        return -1;
    }
    return (1 + max(Height(root->ltree), Height(root->rtree)));
}

/*Function to return the lowest common ancestor*/

int Node::LowestCommonAncestor(Node *root, int x, int y)
{
    int i = (x < y) ? x : y;
    int j = x + y - i;
    if (i <= root->value && j >= root->value)
    {
        return root->value;
    }
    else if (j < root->value)
    {
        return LowestCommonAncestor(root->ltree, x, y);
    }
    return LowestCommonAncestor(root->rtree, x, y);
}

/*Helper function for maximum path sum*/

int Node::MaxFind(Node *root, int &res)
{
    if (root == NULL)
    {
        return 0;
    }
    int l = MaxFind(root->ltree, res);
    int r = MaxFind(root->rtree, res);

    int max1 = max(max(l, r) + root->value, root->value);
    int max2 = max(max1, l + r + root->value);

    res = max(res, max2);

    return max1;
}

/*Function to return the maxiumum path sum*/

int Node::MaxPathSum(Node *root)
{
    int res = INT_MIN;
    MaxFind(root, res);
    return res;
}
