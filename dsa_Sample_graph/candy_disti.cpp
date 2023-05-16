class Solution
{
    public:
    int distributeCandyUtil(Node* root, int& ans)
    {
    	// Base Case
    	if (root == NULL)
    		return 0;
    
    	// Traverse left subtree
    	int l = distributeCandyUtil(root->left, ans);
    
    	// Traverse right subtree
    	int r = distributeCandyUtil(root->right, ans);
    
    	// Update number of moves
    	ans += abs(l) + abs(r);
    
    	// Return number of moves to balance
    	// current node
    	return root->key + l + r - 1;
    }
    
    
    public:
    int distributeCandy(Node* root)
    {
        int ans = 0;

    	distributeCandyUtil(root, ans);
    
    	return ans;
    }
};