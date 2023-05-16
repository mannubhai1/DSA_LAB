#include <bits/stdc++.h>
#include <queue>

using namespace std;

struct Node
{
       char key;
       int priority;
       Node *left;
       Node *right;
       int height = 0;
};

/Function to return the height of a given Node Node/

int Height(Node* root)
{
    if (root==NULL)
    {
        return -1;
    }
    return root->height;
}

/Function to Create an Node Node/

Node* CreateNode(char key, int priority)
{
    struct Node* node = new Node();
    node->key = key;
    node->priority = priority;
    node->left = NULL;
    node->right = NULL;
    node->height = 0; 
    return(node);
}

/Function to Left Rotate/

Node* LL(Node* root)
{
    Node* rc = root->right;
    Node* xrl = rc->left;
    rc->left = root;
    root->right = xrl;
    root->height = max(Height(root->left), Height(root->right)) + 1;
    rc->height = max(Height(rc->left), Height(rc->right)) + 1;
    root = rc;
    return root;
}

/Function to Right Rotate/

Node* RR(Node* root)
{
    Node* lc = root->left;
    Node* xrc = lc->right;
    lc->right = root;
    root->left = xrc;
    root->height = max(Height(root->left), Height(root->right)) + 1;
    lc->height = max(Height(lc->left), Height(lc->right)) + 1;
    root = lc;
    return root;
}

/Balances the given node in a tree using rotations/

void Balancing(Node** root)
{
    if ((*root)->left==NULL && (*root)->right==NULL)
    {
        return;
    }
    else if ((*root)->left!=NULL && (*root)->right==NULL)
    {
        if ((*root)->left->priority > (*root)->priority)
        {
            (*root) = RR(*root);
        }
    }
    else if ((*root)->left==NULL && (*root)->right!=NULL)
    {
        if ((*root)->right->priority > (*root)->priority)
        {
            (*root) = LL(*root);
        }
    }
    else
    {
        if (((*root)->left->priority > (*root)->priority) && ((*root)->right->priority < (*root)->priority))
        {
            (*root) = RR(*root);
        }
        else if (((*root)->left->priority < (*root)->priority) && ((*root)->right->priority > (*root)->priority))
        {
            (*root) = LL(*root);
        }
        else if (((*root)->left->priority > (*root)->priority) && ((*root)->right->priority > (*root)->priority))
        {
            if ((*root)->left->priority > (*root)->right->priority)
            {
                (*root) = RR(*root);
                (*root)->right = LL((*root)->right);
            }
            else if ((*root)->left->priority < (*root)->right->priority)
            {
                (*root) = LL(*root);
                (*root)->left = RR((*root)->left);
            }
        }
    }
    return;
}

/Function that inserts a node in the Node Tree/

Node* Insert(Node** root, char key, int priority)
{
    if (*root==NULL) {
        cout<<"Inserting "<<key<<"... "<<endl;
        return CreateNode(key, priority);
    }
 
    if ((int)key >= (int)((*root)->key)) {
        (*root)->right = Insert(&(*root)->right, key, priority);
    }
    else if ((int)key < (int)((*root)->key)){
        (*root)->left = Insert(&(*root)->left, key, priority);
    }
    (*root)->height = 1+max(Height((*root)->left), Height((*root)->right));

    Balancing(root);

    return *root;
}

/Function to perform Level-order Traversal/

void LevelorderTraverse(Node* root)
{
    if (root == NULL) {
        return;
    }

    queue<Node*> q;
    q.push(root);
    while (!q.empty())
    {
        int n = q.size();
        for (int i = 0; i < n; i++) {
            Node* temp = q.front();
            q.pop();
            cout << temp->key << " ";
            if (temp->left != NULL) {
                q.push(temp->left);
            }
            else if (temp->left == NULL && temp->key!='-'){
                q.push(CreateNode('-', 0));
            }
            if (temp->right != NULL) {
                q.push(temp->right);
            }
            else if (temp->right == NULL && temp->key!='-'){
                q.push(CreateNode('-', 0));
            }
        }
    }
}

/Helper function to find the predecessor of a node/

Node* FindPrevious(Node** head, char x, Node* prev)
{
    Node* root = *head;
    if (root == NULL) {
        return NULL;
    }
    if (root->key == x) {
        if (root->left != NULL) {
            Node* temp = root->left;
            while (temp->right != NULL) {
                temp = temp->right;
            }
            return temp;
        }
        else {
            return prev;
        }
    }
    else if ((int)(root->key) > (int)(x)) {
        return FindPrevious(&(root->left), x, prev);
    }
    return FindPrevious(&(root->right), x, root);
}

/Function that returns the predecessor of a node/

Node* Predecessor(char x, Node* root)
{
    return FindPrevious(&root, x, NULL);
}

/Helper function to find the successor of a node/

Node* FindNext(Node** head, char x, Node* next) {
    Node* root = *head;
    if (root == NULL) {
        return NULL;
    }
    if (root->key == x) {
        if (root->right != NULL) {
            Node* temp = root->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            return temp;
        }
        else {
            return next;
        }
    }
    else if ((int)(root->key) > (int)(x)) {
        return FindNext(&(root->left), x, root);
    }
    return FindNext(&(root->right), x, next);
}

/Function that returns the successor of a node/

Node* Successor(char x, Node* root)
{
    return FindNext(&root, x, NULL);
}

Node* DeleteNode(char x, Node* root)
{
    if (root==NULL)
    {
        return NULL;
    }
    if ((int)(root->key) < (int)x)
    {
        root->right = DeleteNode(x, root->right);
    }
    else if ((int)(root->key) > (int)x)
    {
        root->left = DeleteNode(x, root->left);
    }
    else{
        if (root->left==NULL && root->right==NULL)  //When the node is a leaf
        {
            delete root;
            root = NULL;
        }
        else if (root->left==NULL)                  //When the node has a right child
        {
            Node* temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right==NULL)                  //When the node has a left child
        {
            Node* temp = root;
            root = root->left;
            delete temp;
        }
        else{                                        //When the node has both children
            Node* temp = root->right;
            while (temp->left!=NULL)
            {
                temp = temp->left;
            }
            root->key = temp->key;
            root->priority = temp->priority;
            root->right = DeleteNode(temp->key, root->right);
        }
    }
    // Balancing(&root);
    return root;
}

Node* help(Node* root)
{
    if (root==NULL)
    {
        return NULL;
    }
    Balancing(&root);
    root->left = help(root->left);
    root->right = help(root->right);
    return root;
}

Node* extractMaxpriority(Node* root)
{
    cout<<"Max priority Element is: "<<endl;
    cout<<"Key: "<<(root)->key<<", Priority: "<<(root)->priority<<endl;
    root = DeleteNode(root->key, root);
    root = help(root);
    return root;
}

// /Function to remove Maximum Priority Element/
// Node* extractMaxpriority(Node** root)
// {
//     cout<<"Max priority Element is: "<<endl;
//     cout<<"Key: "<<(*root)->key<<", Priority: "<<(*root)->priority<<endl;
//     Node* left = (*root)->left;
//     if ((*root)->right!=NULL)
//     {
//         if ((*root)->right->left==NULL)
//         {
//             (*root)->right->left = left;
//             Node* newroot = (*root)->right;
//             delete (*root);
//             Balancing(&newroot);
//             return newroot;
//         }
//         else {
//             Node* extra = (*root)->right->left;
//             Node* newroot = (*root)->right;
//             newroot->left = (*root)->left;
//             Node* pred = Predecessor(newroot->key, newroot);
//             pred->right = extra;
//             Balancing(&extra);
//         }
//     }
//     return *root;
// }


int main()
{
    int n=0;
    cout<<"How many elements do you want to enter?"<<" : ";
    cin>>n;
    cout<<"Initiating Loop..."<<endl;
    struct Node* root = NULL;
    for (int i=0; i<n; i++)
    {
        char c;
        int x;
        cout<<"Iteration "<<i<<") Enter key and priority: ";
        cin>>c>>x;
        root = Insert(&root, c, x);
    }

    LevelorderTraverse(root);
    cout<<endl;
    root = extractMaxpriority(root);
    LevelorderTraverse(root);
    cout<<endl;
    return 0;
}