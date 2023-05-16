#include <bits/stdc++.h>
#include "binary_tree.cpp"

int main()
{

    cout << "Welcome!" << endl;
    int n;
    cout << "Enter the number of elements in the existing tree: ";
    cin >> n;
    int inorder[n];
    int postorder[n];
    vector<int> v;
    cout << "Enter inorder elements of the tree: ";
    for (int i = 0; i < n; i++)
    {
        cin >> inorder[i];
        v.push_back(inorder[i]);
    }

    cout << "Enter postorder elements of the tree: ";
    for (int i = 0; i < n; i++)
    {
        cin >> postorder[i];
    }
    cout << "Generating Tree..." << endl;
    Node tree, *root = NULL;
    root = tree.generateTree(inorder, postorder, n);

    cout << "Tree Generated.\n"
         << endl;

    while (true)
    {
        int choice;
        int x;
        cout << "What operation do you want to perform on the tree?" << endl;
        cout << "1. Insert Element    2. Delete Element   3. Find Element   4. Inorder/Preorder/Postorder Traversal" << endl;
        cout << "5. Level-Order Traversal   6. Check if Node   7. Predecessor   8. Successor" << endl;
        cout << "9. Select   10. Diameter   11. Height   12. Lowest Common Ancestor" << endl;
        cout << "13. Maximum Path Sum   14. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;
        if (choice == 1)
        {
            cout << "Enter the number to insert: ";
            cin >> x;
            root = tree.InsertinTree(x, root);
            v.push_back(x);
            cout << "Element inserted successfully!" << endl;
        }
        else if (choice == 2)
        {
            cout << "Enter the number to delete: ";
            cin >> x;
            root = tree.DeleteNode(x, root);
            cout << "Element deleted successfully!" << endl;
        }
        else if (choice == 3)
        {
            cout << "Enter the number to find: ";
            cin >> x;
            Node *node;
            bool found = false;
            if (tree.isBST(root))
            {
                node = tree.Find(x, root);
                if (node != NULL)
                {
                    found = true;
                }
            }
            else
            {
                for (int j = 0; j < v.size(); j++)
                {
                    if (v[j] == x)
                    {
                        found = true;
                        break;
                    }
                }
            }

            if (found)
            {
                cout << "Element Found!" << endl;
            }
            else
            {
                cout << "Element does not exist in tree. " << endl;
            }
        }
        else if (choice == 4)
        {
            cout << "Do you want to print\n1. Inorder 2. Preorder 3. Postorder\nEnter choice: ";
            cin >> x;
            if (x == 1)
            {
                tree.InorderTraverse(root);
                cout << endl;
            }
            else if (x == 2)
            {
                tree.PreorderTraverse(root);
                cout << endl;
            }
            else if (x == 3)
            {
                tree.PostorderTraverse(root);
                cout << endl;
            }
            else
            {
                cout << "Invalid Choice!" << endl;
            }
        }
        else if (choice == 5)
        {
            tree.LevelorderTraverse(root);
            cout << endl;
        }
        else if (choice == 6)
        {
            if (tree.isBST(root))
            {
                cout << "Yes, it is a Node" << endl;
            }
            else
            {
                cout << "No, it is not a Node" << endl;
            }
        }
        else if (choice == 7)
        {
            if (tree.isBST(root))
            {
                cout << "Enter element whose predecessor you want: ";
                cin >> x;
                Node *node;
                node = tree.Predecessor(x, root);
                cout << "Predecessor: " << tree.getValue(node) << endl;
            }
            else
            {
                cout << "The tree is not a Node. We cannot run this function here." << endl;
            }
        }
        else if (choice == 8)
        {
            if (tree.isBST(root))
            {
                cout << "Enter element whose successor you want: ";
                cin >> x;
                Node *node;
                node = tree.Successor(x, root);
                cout << "Successor: " << tree.getValue(node) << endl;
            }
            else
            {
                cout << "The tree is not a Node. We cannot run this function here." << endl;
            }
        }
        else if (choice == 9)
        {
            if (tree.isBST(root))
            {
                cout << "Enter k to find kth smallest element: ";
                cin >> x;
                Node *node;
                node = tree.Select(x, root);
                cout << "The kth smallest element is: " << tree.getValue(node) << endl;
            }
            else
            {
                cout << "The tree is not a Node. We cannot run this function here." << endl;
            }
        }
        else if (choice == 10)
        {
            cout << "The diameter of the tree is: " << tree.Diameter(root) << endl;
        }
        else if (choice == 11)
        {
            cout << "The height of the tree is: " << tree.Height(root) << endl;
        }
        else if (choice == 12)
        {
            int m, n;
            cout << "Enter the first element: " << endl;
            cin >> m;
            cout << "Enter the second element: " << endl;
            cin >> n;
            cout << "The lowest common ancestor: " << tree.LowestCommonAncestor(root, m, n) << endl;
        }
        else if (choice == 13)
        {
            cout << "The Maximum Path Sum = " << tree.MaxPathSum(root) << endl;
        }
        else if (choice == 14)
        {
            cout << "\nExiting application...\n"
                 << endl;
            break;
        }
        else
        {
            cout << "Invalid Input. Try Again!" << endl;
        }
        cout << endl;
    }

    return 0;
}