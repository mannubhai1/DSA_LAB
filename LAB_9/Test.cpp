#include "Dynamic_perefect_hashing.cpp"
using namespace std;
int main()
{

    HashMap *obj = new HashMap();
    bool status = true;
    while (status)
    {
        cout << "Do you want to Insert a single element ?, 0 - no, any other number -  yes?" << endl;
        int choice = 0;
        cin >> choice;
        if (choice == 0)
        {
            status = false;
        }
        else
        {
            cout << "Input an element: " << endl;
            int num;
            cin >> num;
            obj->Insert(num);
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (pair<int, bool> j : obj->table[i]->sub_table)
        {
            if (j.first != INT_MAX)
                cout << j.first << endl;
        }
    }
}