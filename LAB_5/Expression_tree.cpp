#include <bits/stdc++.h>
using namespace std;
#define fr(o, n) for (int i = o; i < n; i++)
class node
{
public:
    char ch;
    node *left;
    node *right;
    node(char c)
    {
        ch = c;
        left = nullptr;
        right = nullptr;
    }
};
stack<char> op;
stack<node *> val;
node *value(node *head) {}

void pushchar(char k)
{
    if (k == '*' || k == '/' || k == '(' || k == ')' || k == '+' || k == '-')
    {
        if (k == '*' || k == '/' || k == '(')
            op.push(k);
        else if (op.empty())
            op.push(k);
        else if (op.top() == '+' || op.top() == '-' || op.top() == '(')
            op.push(k);
        else
        {
            // cout<<"printed";
            node *newnode = new node(op.top());
            newnode->right = val.top();
            val.pop();
            if (!val.empty())
            {
                newnode->left = val.top();
                val.pop();
            }
            val.push(newnode);
            op.pop();
            op.push(k);
        }
    }
    else
    {
        node *newnode = new node(k);
        val.push(newnode);
    }
}

void popop()
{
    char k;
    while (!op.empty())
    {
        k = op.top();
        op.pop();
        if (k == '(')
            break;
        node *newnode = new node(k);
        newnode->right = val.top();
        val.pop();
        if (!val.empty())
        {
            newnode->left = val.top();
            val.pop();
        }
        val.push(newnode);
    }
}
int logic(int a, int b, char c)
{
    if (c == '+')
        return a + b;
    else if (c == '-')
        return a - b;
    else if (c == '*')
        return a * b;
    else
        return a / b;
}
int output(node *head)
{
    char k = head->ch;
    if (k == '*' || k == '/' || k == '(' || k == ')' || k == '+' || k == '-')
    {
        char l = head->left->ch;
        char r = head->right->ch;
        int a = output(head->left);
        int b = output(head->right);

        if (isdigit(l) && isdigit(r))
        {
            return logic(l + '0', r + '0', k);
        }
        else
        {
            return a + b;
        }
    }
    else
        return k + '0';
}

int findval(node *t)
{
    if (!t->left && !t->right)
        return t->ch - '0';
    char op = t->ch;
    int l = findval(t->left);
    int r = findval(t->right);
    cout << l << " is lval, rval = " << r << endl;
    if (op == '*')
        return l * r;
    else if (op == '/')
        return l / r;
    else if (op == '+')
        return l + r;
    else
        return l - r;
}

int main()
{
    string s = "3+4";
    char k;
    fr(0, s.size())
    {
        k = s.at(i);
        if (k == ')')
            popop();
        else
        {
            pushchar(k);
        }
    }
    popop();

    // cout<<val.top()->ch;
    cout << findval(val.top());
}
