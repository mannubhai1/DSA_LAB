// implement alpha quantile using RBtree
//  MANNU

#include <bits/stdc++.h> // not working properly
using namespace std;

enum class colour
{
    red,
    black
};

struct Node
{
    int value;
    int weight;
    Node *left;
    Node *right;
    Node *parent;
    colour color; // red or black defined using enum
    double LS;    // left sum of each node
    double RS;    // right sum of each node

    Node(int value, int weight) : value(value), weight(weight), left(NULL), right(NULL), parent(NULL), color(colour::red) {}
};

class RBT
{
public:
    Node *root;

    RBT() : root(NULL) {}

    void LR(Node *node) // left rotate with an addition of calculation of LS and RS
    {
        Node *temp = node->right;
        node->right = temp->left;
        if (temp->left != NULL)
        {
            temp->left->parent = node;
        }
        temp->parent = node->parent;
        if (node->parent == NULL)
        {
            root = temp;
        }
        else if (node == node->parent->left)
        {
            node->parent->left = temp;
        }
        else
        {
            node->parent->right = temp;
        }
        temp->left = node;
        node->parent = temp;

        temp->LS += temp->weight + node->LS;
        node->RS -= temp->LS + temp->weight;
    }

    void RR(Node *node) // left rotate with an addition of calculation of LS and RS
    {
        Node *temp = node->left;
        node->left = temp->right;
        if (temp->right != NULL)
        {
            temp->right->parent = node;
        }
        temp->parent = node->parent;
        if (node->parent == NULL)
        {
            root = temp;
        }
        else if (node == node->parent->right)
        {
            node->parent->right = temp;
        }
        else
        {
            node->parent->left = temp;
        }
        temp->right = node;
        node->parent = temp;

        temp->RS += temp->weight + node->RS;
        node->LS -= temp->RS + temp->weight;
    }

    void insertFixup(Node *node)
    {
        while (node->parent != NULL && node->parent->color == colour::red)
        {
            if (node->parent == node->parent->parent->left)
            {
                Node *temp = node->parent->parent->right;
                if (temp != NULL && temp->color == colour::red)
                {
                    node->parent->color = colour::black;
                    temp->color = colour::black;
                    node->parent->parent->color = colour::red;
                    node = node->parent->parent;
                }
                else
                {
                    if (node == node->parent->right)
                    {
                        node = node->parent;
                        LR(node);
                    }
                    node->parent->color = colour::black;
                    node->parent->parent->color = colour::red;
                    RR(node->parent->parent);
                }
            }
            else
            {
                Node *temp = node->parent->parent->left;
                if (temp != NULL && temp->color == colour::red)
                {
                    node->parent->color = colour::black;
                    temp->color = colour::black;
                    node->parent->parent->color = colour::red;
                    node = node->parent->parent;
                }
                else
                {
                    if (node == node->parent->left)
                    {
                        node = node->parent;
                        RR(node);
                    }
                    node->parent->color = colour::black;
                    node->parent->parent->color = colour::red;
                    LR(node->parent->parent);
                }
            }
        }
        root->color = colour::black;
    }

    Node *Search(Node *node, int value)
    {
        if (node == NULL || node->value == value)
        {
            return node;
        }
        if (value < node->value)
        {
            node = Search(node->left, value);
        }
        else
        {
            node = Search(node->right, value);
        }
        return node;
    }

    Node *getRoot()
    {
        return root;
    }

    Node *search(int value) // search helper function
    {
        return Search(root, value);
    }

    void insert(int value, int weight)
    {
        Node *node = new Node(value, weight);
        Node *temp = NULL;
        Node *y = root;
        while (y != NULL)
        {
            temp = y;
            if (node->value < y->value)
            {
                y = y->left;
            }
            else
            {
                y = y->right;
            }
        }
        node->parent = temp;
        if (temp == NULL)
        {
            root = node;
        }
        else if (node->value < temp->value)
        {
            temp->left = node;
        }
        else
        {
            temp->right = node;
        }
        node->left = NULL;
        node->right = NULL;
        node->color = colour::red;
        insertFixup(node);
    }

    double quantile(double alpha, double &accumulated_weight) // O(log(n)) approach
    {
        double LS = 0, RS = 0;
        Node *temp = root;

        while (!temp)
        {
            LS = LS + temp->LS;
            RS = RS + temp->RS;
            accumulated_weight += temp->weight;

            if (LS + accumulated_weight * temp->value > alpha * (LS + RS + accumulated_weight))
            {
                return temp->value;
            }

            temp = temp->right;
        }

        return -1;
    }

    // Node *inorder(Node *node, double alpha, double &accumulated_weight) // O(n) approach      backup
    // {
    //     if (node == NULL)
    //     {
    //         return NULL;
    //     }
    //     Node *left = inorder(node->left, alpha, accumulated_weight);
    //     if (left != NULL)
    //     {
    //         return left;
    //     }
    //     accumulated_weight += node->weight;
    //     cout << node->weight << " " << node->value << endl;
    //     cout << accumulated_weight << endl;
    //     if (accumulated_weight >= alpha)
    //     {
    //         return node;
    //     }
    //     return inorder(node->right, alpha, accumulated_weight);
    // }

    // Node *a_quantile(double alpha) // helper function of inorder
    // {
    //     double accumulated_weight = 0.0;
    //     // return inorder(root, alpha, accumulated_weight);
    // }

    double a_quantile(double alpha) // helper function of quantile function
    {
        double accumulated_weight = 0.0;
        return quantile(alpha, accumulated_weight);
    }
};

int main()
{
    vector<int> values = {1, 3, 4, 9, 2, 7};
    vector<double> weights = {0.1, 0.2, 0.1, 0.15, 0.05, 0.4};
    RBT();
    RBT tree;
    // cout << values.size() << endl;
    for (int i = 0; i < values.size(); i++)
    {
        tree.insert(values[i], weights[i]);
    }

    double alpha = 0.9;
    // cin >> alpha;
    // Node *NODE = tree.a_quantile(alpha);
    // cout << NODE->value << endl;
    double ans = tree.a_quantile(alpha);
    cout << ans << endl;

    return 0;
}