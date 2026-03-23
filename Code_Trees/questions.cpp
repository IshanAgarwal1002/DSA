#include<iostream>
#include<vector>
#include<stack>
using namespace std;

struct TreeNode 
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//leetcode 236 - LCA of a Binary Tree
TreeNode *LCANode = NULL;
bool LCA(TreeNode* root, TreeNode* p, TreeNode* q) 
{
    if(root == NULL)
        return false;

    bool selfDone = false;
    if((root->val == p->val) || (root->val == q->val))
        selfDone = true;
    
    bool leftDone = LCA(root->left,p,q);
    if(leftDone && selfDone)    LCANode = root;
    if(LCANode != NULL)     return true;

    bool rightDone = LCA(root->right,p,q);
    if((rightDone && selfDone) || (leftDone && rightDone))    LCANode = root;
    if(LCANode != NULL)     return true;

    return (selfDone || leftDone || rightDone);
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
{
    bool res = LCA(root, p ,q);
    return LCANode;
}

//leetcode 863 - All Nodes Distance K in Binary 
vector<int> ans;
void kDown(TreeNode *root, int k)
{
    if(root == NULL)   return;

    if(k == 0)
    {
        ans.push_back(root->val);
        return;
    }

    kDown(root->left, k-1);
    kDown(root->right, k-1);
}

int allNodeKAway(TreeNode *root, int k, TreeNode* target)
{
    if(root == NULL)    return -1;

    if(root == target)
    {
        kDown(root,k);
        return 1;
    }

    int leftDist = allNodeKAway(root->left,k,target);
    if(leftDist != -1)
    {
        if(k - leftDist == 0)   kDown(root,k - leftDist);
        else if(k - leftDist > 0)   kDown(root->right,k-leftDist-1);
        return leftDist + 1;
    } 

    int rightDist = allNodeKAway(root->right,k,target);
    if(rightDist != -1)
    {
        if(k - rightDist == 0)   kDown(root,k - rightDist);
        else if(k - rightDist > 0)   kDown(root->left,k-rightDist-1);
        return rightDist + 1;
    } 

    return -1;
}

vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {

    int n = allNodeKAway(root,K,target);
    return ans;
}

//leetcode 543 - Diameter of Binary 
int diameter = 0;
int DBT(TreeNode* root) 
{
    if(root == NULL)
        return -1;

    int lh = DBT(root->left);
    int rh = DBT(root->right);

    diameter = max(diameter, lh+rh+2);

    return max(lh,rh) + 1;
}

int diameterOfBinaryTree(TreeNode* root) {
    int n = DBT(root);
    return diameter;        
}

//leetcode 112 - Path Sum
bool hasPathSum(TreeNode* root, int sum) 
{
    if(root == NULL)
        return false;

    if((sum - root->val == 0) && (!root->left && !root->right)) return true;
    
    return hasPathSum(root->left,sum-root->val) || hasPathSum(root->right,sum-root->val);
}

//leetcode 113 - Path Sum II
void pathSum1(TreeNode* root, int sum, vector<vector<int>> &res, vector<int> &smallAns) {

    if(root == nullptr) return;
    if(sum-root->val == 0 && !root->left && !root->right)
    {
        vector<int> base(smallAns);
        base.push_back(root->val);
        res.push_back(base);
        return;
    }

    smallAns.push_back(root->val);
    pathSum1(root->left,sum-root->val,res,smallAns);
    pathSum1(root->right,sum-root->val,res,smallAns);
    smallAns.pop_back();
}

vector<vector<int>> pathSum(TreeNode* root, int sum) {
    vector<vector<int>> res;
    vector<int> smallAns;
    pathSum1(root,sum,res,smallAns);
    return res;
}

// GFG - Leaf to Leaf Sum
//https://www.geeksforgeeks.org/find-maximum-path-sum-two-leaves-binary-tree/
int maxSum = INT32_MIN;
int leafToLeafSum(TreeNode *root)
{
    if(root == NULL)    return 0;

    int ls = leafToLeafSum(root->left);
    int rs = leafToLeafSum(root->right);

    if(root->left && root->right){
        maxSum = max(maxSum, ls+rs+root->val);
        return max(ls,rs) + root->val;
    }

    return (root->left?ls:rs) + root->val;
}

int ltls(TreeNode *root)
{
    int n = leafToLeafSum(root);
    if(maxSum = INT32_MIN)  maxSum = n;
    //for testcase (basically there is only 1 leaf node in this testcase)
    //      1
    //     / \
    //  NULL  5
    return maxSum;
}

//leetcode 124 - Binary Tree Maximum Path Sum
int maxSum = INT32_MIN;
int mps(TreeNode* root)
{
    if(root == NULL)    return 0;

    int ls = mps(root->left);
    int rs = mps(root->right);

    int n = max(ls,rs) + root->val;
    maxSum = max(max(maxSum,root->val),max(n,ls+rs+root->val));

    return max(n,root->val);
}

int maxPathSum(TreeNode* root) 
{
    int a = mps(root);
    return maxSum;
}

//leetcode 98 - Valid BST
long p = -1e11;
bool isValidBST(TreeNode* root) 
{
    if(root == NULL)    return true;

    if(!isValidBST(root->left))     return false;

    if(p >= root->val)    return false;
    p = root->val;

    if(!isValidBST(root->right))     return false;

    return true;
}

//leetcode 99 - Recover Binary Search Tree
TreeNode *a = nullptr;
TreeNode *b = nullptr;
TreeNode *c = nullptr; // previous.

bool recoverTree_(TreeNode *root)
{
    if (root == nullptr)
        return false;

    if (recoverTree_(root->left))
        return true;

    if (c != nullptr && c->val > root->val)
    {
        b = root; // first time it may be wrong.
        if (a == nullptr)
            a = c; // a always br previous
        else
            return true;
    }
    
    c = root;  // set previous.

    if (recoverTree_(root->right))
        return true;

    return false;
}

void recoverTree(TreeNode *root)
{
    bool res = recoverTree_(root);
    if(a!=nullptr)
    {
        int temp = a->val;
        a->val = b->val;
        b->val = temp;
    }
}

//leetcode 285 - Inorder Successor in BST
TreeNode* inorderSuccessor(TreeNode *root, TreeNode *p)
{
    TreeNode *curr = root, *succ = NULL;

    while(curr!=NULL)
    {
        if(curr == p)
        {
            if(curr->right)
            {
                succ = curr->right;
                while(succ->left)
                    succ = succ->left;
            }
            break;
        }
        else if(curr->val > p->val)
        {
            succ = curr;
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    } 

    return succ;
}

//leetcode 510 - Inorder Successor in BST II
//Given a binary search tree and a node in it, find the in-order successor of that node in the BST.
// The successor of a node p is the node with the smallest key greater than p.val. 
// You will have direct access to the node but not to the root of the tree. 
// Each node will have a reference to its parent node. A node is defined as the following:
class Node {
    public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};

Node* inorderSuccessor(Node* node)
{
    Node *succ = nullptr;
    if(node->right)
    {
        succ = node->right;
        while(succ->left)
            succ = succ->left;
    }
    else
    {
        Node *curr = node;
        while(curr->parent != nullptr)
        {
            if(curr->parent->left == curr)
            {
                succ = curr->parent;
                break;
            }
            curr = curr->parent;
        }
    }

    return succ;
}

//leetcode 450 - Delete Node in a BST
int maxInLeft(TreeNode *root)
{
    TreeNode *curr = root->left;
    while(curr->right)
        curr = curr->right;
    
    return curr->val;
}

TreeNode* deleteNode(TreeNode* root, int key) 
{
    if(root == nullptr)    return nullptr;

    if(root->val > key)
        root->left = deleteNode(root->left,key);
    else if(root->val < key)
        root->right = deleteNode(root->right,key);
    else{
        if(!root->left || !root->right)
            return (root->left?root->left:root->right);

        int n = maxInLeft(root);
        root->val = n;
        root->left = deleteNode(root->left,n);
    } 

    return root;
}

//leetcode 987


//leetcode 173 - Binary Search Tree Iterator
class BSTIterator {

    stack<TreeNode*> st;

    void pushAllLeftEle(TreeNode *node)
    {
        while(node!=nullptr)
        {
            st.push(node);
            node = node->left;
        }
    }

public:

    BSTIterator(TreeNode* root) {
        pushAllLeftEle(root);
    }
    
    /* @return the next smallest number */
    int next() {
        TreeNode *rn = st.top();
        st.pop();
        pushAllLeftEle(rn->right);
        return rn->val;
    }
    
    /* @return whether we have a next smallest number */
    bool hasNext() {
        return st.size()!=0;
    }
};

//leetcode 105 - Construct Binary Tree from Preorder and Inorder Traversal
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) 
{
    
}

//leetcode 1469
void fun(TreeNode *root, vector<int> &ans)
{
    if(!root->left && !root->right) return;

    if(root->left && !root->right)  ans.push_back(root->left->val); 
    else if(!root->left && root->right)  ans.push_back(root->right->val); 

    if(root->left) fun(root->left, ans);
    if(root->right) fun(root->right, ans);
}

vector<int> findLonelyNodes(TreeNode *root)
{
    vector<int> ans;
    if(root == nullptr || (!root->left && !root->right)) return ans;

    fun(root, ans);
    return ans;
}

//Josh Technology Group Interview 1
//Given a tree. Find the maximum sum of nodes such that no two nodes are linked to each other
// Ex.         1
//            /  \
//           2     3
//          / \   / \
//         4  5   6  7
// MaxSum = 23
// Note - Can't use global var, reference var
//https://www.geeksforgeeks.org/maximum-sum-nodes-binary-tree-no-two-adjacent/

pair<int,int> maxSumOfUnlinkedNodes_helper(TreeNode *root)
{
    if(root == nullptr) return {0,0};

    pair<int, int> l = maxSumOfUnlinkedNodes_helper(root->left);
    pair<int, int> r = maxSumOfUnlinkedNodes_helper(root->right);

    pair<int, int> ans;
    //ans.first = sum including the current data
    //ans.second = sum exlcuding the current data
    
    ans.first = root->val + l.second + r.second;
    ans.second = max(l.first, l.second) + max(r.first, r.second);

    return ans; 
}

int maxSumOfUnlinkedNodes(TreeNode *root)
{
    pair<int,int> ans = maxSumOfUnlinkedNodes_helper(root);
    return max(ans.first, ans.second);
}

//