#include <bits/stdc++.h>
using namespace std;
int counter = 0;
long long int p = 1e9 + 7;
int m = 10;
#define acc table[index]->sub_table
struct Node
{
    vector<pair<int, bool>> sub_table; // 1 - deleted, 0 - alive
    int sub_count;

    Node()
    {
        sub_count = 0;
    }
};

class HashMap
{
public:
    int count = 0;
    // bool markDeleted;
    vector<Node *> table;
    void Insert();
    void rehashall(vector<int> sub_table);
    int MappingFunction(int key, int t_ele);
    void Insert(int key);
    int find_element(vector<Node *> table, int index, int sub_index, int key);
    void rehash_subtable(vector<int> temp, int index);
    HashMap();
};
