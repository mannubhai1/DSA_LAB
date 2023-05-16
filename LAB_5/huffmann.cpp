#include <bits/stdc++.h>
#include "huffmann.h"
using namespace std;

map<char, int> fq;
map<char, string> huff_code;

void Cal_fq_tree(string s)
{
    for (int i = 0; i < s.size(); i++)
        fq[s[i]]++;
}

void code_file(int size)
{
    node_min *left, *right, *top;
    for (auto v : fq)
    {
        minHeap.push(new node_min(v.first, v.second));
    }

    // making minheap
    while (minHeap.size() != 1)
    {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();

        top = new node_min('@', left->fq + right->fq);
        top->rtree = right;
        top->ltree = left;
        minHeap.push(top);
    }
    store_huff(minHeap.top(), "");
}

void store_huff(struct node_min *root, string s)
{
    if (root == NULL)
        return;
    if (root->data != '@')
        huff_code[root->data] = s;
    store_huff(root->ltree, s + "0");
    store_huff(root->rtree, s + "1");
}

string Decode_file(struct node_min *root, string s)
{
    string final = "";
    struct node_min *p = root;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '0')
            p = p->ltree;
        else
            p = p->rtree;

        if (p->ltree == NULL && p->rtree == NULL)
        {
            final += p->data;
            p = root;
        }
    }
    cout << final;
    return final;
}

int main()
{

    fstream file;
    string word, t, q, filename, filename1;
    filename = "huffman.txt";
    filename1 = "huffman_codess.txt";

    file.open(filename.c_str());

    string str, encodedString, decodedString;

    getline(file, str);

    Cal_fq_tree(str);
    code_file(str.length());

    for (auto v = huff_code.begin(); v != huff_code.end(); v++)
        cout << v->first << ' ' << v->second << endl;
    file.close();

    file.open(filename1.c_str());

    for (auto i : str)
        encodedString += huff_code[i];

    file << encodedString << endl;

    file << Decode_file(minHeap.top(), encodedString);
    file.close();

    return 0;
}