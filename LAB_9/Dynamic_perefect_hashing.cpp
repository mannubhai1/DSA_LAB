#include "Dynamic_perefect_hashing.h"

int HashMap::MappingFunction(int key, int t_ele)
{
    srand(time(0));
    int a = rand() % 1000;
    int b = rand() % 1000;
    int val = ((a * key + b) % p) % t_ele;
    return val;
}

int HashMap::find_element(vector<Node *> table, int index, int sub_index, int key)
{

    if (table[index]->sub_table[sub_index].first == key)
        return 1;

    return -1;
}

void HashMap::rehash_subtable(vector<int> temp, int index)
{
    int size = table[index]->sub_table.size();
    bool status = true;
    while (status)
    {
        status = false;
        table[index]->sub_table.clear();
        table[index]->sub_table.resize(size);
        for (int i = 0; i < size; i++)
        {
            acc[i].first = INT_MAX;
        }
        for (int i : temp)
        {
            int sub_index = MappingFunction(i, size);
            if (acc[sub_index].first == INT_MAX)
            {
                acc[sub_index] = {i, 0};
            }
            else
            {
                status = true;
                break;
            }
        }
    }
}

HashMap::HashMap()
{
    this->table.resize(m);
    for (int i = 0; i < m; i++)
    {
        table[i] = new Node();
    }
}

void HashMap::Insert(int x)
{
    count++;
    if (count > m)
    {
        vector<int> temp_list;
        for (Node *i : table)
        {
            for (pair<int, bool> j : i->sub_table)
            {
                if (j.second == 0)
                {
                    temp_list.push_back(j.first);
                }
            }
        }
        int n = temp_list.size();

        table.erase(table.begin(), table.end());
        table.resize(2 * n);
        m = 2 * n;
        for (int i = 0; i < 2 * n; i++)
        {
            table[i] = new Node();
        }
        count = 0;
        rehashall(temp_list);
        Insert(x);
    }
    else
    {
        int j = MappingFunction(x, m);
        if (!table[j]->sub_table.size())
        {
            table[j]->sub_table.resize(1);
            table[j]->sub_table[0].first = INT_MAX;
        }
        int subindex = MappingFunction(x, table[j]->sub_table.size());
        // int bucket_index = find_element(table, j, sub_index, x);
        if (find_element(table, j, subindex, x) != -1)
        {
            if (table[j]->sub_table[subindex].second == 1)
            {
                table[j]->sub_table[subindex].second == 0;
            }
        }
        else
        {
            table[j]->sub_count++;
            if (table[j]->sub_count <= table[j]->sub_table.size())
            {
                if (table[j]->sub_table[subindex].first == INT_MAX)
                {
                    table[j]->sub_table[subindex] = {x, 0};
                }
                else
                {
                    vector<int> temp(table[j]->sub_count);
                    for (pair<int, bool> i : table[j]->sub_table)
                    {
                        if (i.second == 0)
                            temp.push_back(i.first);
                    }
                    temp.push_back(x);
                    rehash_subtable(temp, j);
                }
            }
            else
            {
                int total_subsize = pow(table[j]->sub_table.size(), 2);
                for (Node *i : table)
                {
                    total_subsize += i->sub_table.size();
                }
                total_subsize -= table[j]->sub_table.size();

                if (total_subsize > 4 * count) // c (constant) = 4
                {
                    vector<int> temp_list;
                    for (Node *i : table)
                    {
                        for (pair<int, bool> j : i->sub_table)
                        {
                            if (j.second == 0)
                            {
                                temp_list.push_back(j.first);
                            }
                        }
                    }
                    int n = temp_list.size();

                    // double alpha = (double)n / m;
                    // double c = 4;
                    // int new_m = 1 + c * max(n, 4);
                    table.erase(table.begin(), table.end());
                    table.resize(n);
                    for (int i = 0; i < n; i++)
                    {
                        table[i] = new Node();
                    }
                    count = 0;
                    rehashall(temp_list);
                    Insert(x);
                }
                else
                {
                    vector<int> temp(table[j]->sub_count);
                    for (pair<int, bool> i : table[j]->sub_table)
                    {
                        if (i.second == 0)
                            temp.push_back(i.first);
                    }
                    temp.push_back(x);

                    table[j]->sub_table.erase(table[j]->sub_table.begin(), table[j]->sub_table.end());
                    table[j]->sub_table.resize(pow(temp.size(), 2));
                    rehash_subtable(temp, j);
                }
            }
        }
    }
}

void HashMap::rehashall(vector<int> list)
{
    for (int i : list)
    {
        Insert(i);
    }
}