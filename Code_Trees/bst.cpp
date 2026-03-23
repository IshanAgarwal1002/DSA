#include<iostream>
#include<vector>
using namespace std;

class Node
{
    public:
        int data;
        Node *left;
        Node *right;

        Node(){}

        Node(int data)
        {
            this->data = data;
            this->left = nullptr;
            this->right = nullptr;
        }
};

//bst construction, time complexity O(n), recursion space O(log n)
Node* construct(vector<int> &arr, int si, int ei)
{
    if(si>ei)   return nullptr;

    int mid = (si+ei)>>1;   //(si+ei)/2

    Node *root = new Node(arr[mid]);
    root->left = construct(arr,si,mid-1);
    root->right = construct(arr,mid+1,ei);

    return root;
}

void display(Node *root)
{
    if(root == nullptr) return;

    (root->left == nullptr)?cout<<".":cout<<root->left->data;
    cout<<" -> "<<root->data<<" <- ";
    (root->right == nullptr)?cout<<".\n":cout<<root->right->data<<"\n";

    display(root->left);
    display(root->right);
}

//basic=====================================================================
int height(Node *root)
{
    if(root==nullptr)   return -1;  //in terms of edges
    return max(height(root->left),height(root->right)) + 1;
}

int size(Node *root)
{
    if(root == nullptr) return 0;
    return (size(root->left) + size(root->right) + 1);
}

bool find(Node *root, int &data)
{
    Node *curr = root;
    while(curr != nullptr)
    {
        if(curr->data == data) return true;
        else if(data > curr->data)    curr = curr->right;
        else curr = curr->left;
    }

    return false;
}

bool findRec(Node *root,int &data)
{
    if(root == nullptr) return false;

    if(root->data == data)   return true;
    else if(data > root->data)  return findRec(root->right, data);
    else    return findRec(root->left, data);
}

Node* maximum(Node *root)
{
    if(root==nullptr)   return nullptr;

    Node *curr = root;

    while(curr->right != nullptr)
        curr = curr->right;
    
    return curr;
}

Node* minimum(Node *root)
{
    if(root==nullptr)   return nullptr;

    Node *curr = root;

    while(curr->left != nullptr)
        curr = curr->left;
    
    return curr;
}

//lowest common ancestor
Node* LCA(Node *root,int p, int q)          //assuming (p < q)
{
    Node *curr = root;
    while(curr != nullptr)
    {
        if(q < curr->data)  curr = curr->left; 
        else if(p > curr->data)  curr = curr->right;
        else return (find(curr,p) && find(curr,q))?curr:nullptr;  
    }
    return nullptr;
}

int LCAoFBST_Rec(Node *node, int a, int b) // a<b
{
    if (node == nullptr)
        return -1;

    if (b < node->data)
        return LCAoFBST_Rec(node->left, a, b);
    else if (a > node->data)
        return LCAoFBST_Rec(node->right, a, b);
    else
        return node->data; //LCA point.
}

//In Order
void allNodesInRange_01(Node *node, int a, int b, vector<int> &ans)
{
    if (node == nullptr)
        return;

    allNodesInRange_01(node->left, a, b, ans);

    // sorted Region.
    if (node->data >= a && node->data <= b)
        ans.push_back(node->data);
    
    allNodesInRange_01(node->right, a, b, ans);
}

//pre Order
void allNodesInRange_02(Node *node, int a, int b, vector<int> &ans)
{
    if (node == nullptr)
        return;
    if (node->data >= a && node->data <= b)
        ans.push_back(node->data);

    if (b < node->data && a < node->data)
        allNodesInRange_02(node->left, a, b, ans);
    else if (a > node->data && b > node->data)
        allNodesInRange_02(node->right, a, b, ans);
    else //LCA Region.
    {
        allNodesInRange_02(node->left, a, b, ans);
        allNodesInRange_02(node->right, a, b, ans);
    }
}

//predecessor and successor in a binary search tree
void predAndSucc_InOrder(Node *node, int data)
{
    Node *curr = node;
    Node *pred = nullptr;
    Node *succ = nullptr;
    while (curr != nullptr)
    {
        if (curr->data == data)
        {
            if (curr->left == nullptr)
                cout << "Pred: " << (pred != nullptr ? pred->data : -1) << endl;
            else
            {
                pred = curr->left;
                while (pred->right != nullptr)
                    pred = pred->right;
                cout << "Pred: " << pred->data << endl;
            }

            if (curr->right == nullptr)
                cout << "Succ: " << (succ != nullptr ? succ->data : -1) << endl;
            else
            {
                succ = curr->right;
                while (succ->left != nullptr)
                    succ = succ->left;
                cout << "Succ: " << succ->data << endl;
            }

            break;
        }
        else if (data < curr->data)
        {
            succ = curr;
            curr = curr->left;
        }
        else
        {
            pred = curr;
            curr = curr->right;
        }
    }
}

int idx = 0;
Node *constructTreeFromPreOrder(vector<int> &preOrder, int lb, int ele, int rb)
{
    if (ele < lb || ele > rb || idx == preOrder.size())
        return nullptr;

    Node *node = new Node(ele);
    idx++;

    if (idx < preOrder.size())
        node->left = constructTreeFromPreOrder(preOrder, lb, preOrder[idx], ele);
    if (idx < preOrder.size())
        node->right = constructTreeFromPreOrder(preOrder, ele, preOrder[idx], rb);

    return node;
}

Node *constructTreeFromPreOrder(vector<int> &preOrder, int lb, int rb)
{
    if (idx == preOrder.size() || preOrder[idx] < lb || preOrder[idx] > rb)
        return nullptr;

    Node *node = new Node(preOrder[idx++]);
    node->left = constructTreeFromPreOrder(preOrder, lb, node->data);
    node->right = constructTreeFromPreOrder(preOrder, node->data, rb);
    return node;
}

int heightOfBSTPreorder(vector<int> &preOrder, int lb, int rb)
{
    if (idx == preOrder.size() || preOrder[idx] < lb || preOrder[idx] > rb)
        return -1;

    int ele = preOrder[idx++];

    int lh = heightOfBSTPreorder(preOrder, lb, ele);
    int rh = heightOfBSTPreorder(preOrder, ele, rb);
    return max(lh, rh) + 1;
}

Node *constructTreeFromPreOrder_(vector<int> &preOrder)
{
    return constructTreeFromPreOrder(preOrder, -1e8, 1e8);
}

Node *addData(Node *root, int data)
{
    if (root == nullptr)
        return new Node(data);
    if (data < root->data)
        root->left = addData(root->left, data);
    else
        root->right = addData(root->right, data);

    return root;
}

Node *removeData(Node *root, int data)
{
    if (root == nullptr)
        return nullptr;  // never found data;
    
    if (data < root->data)
        root->left = removeData(root->left, data);
    else if(data > root->data)
        root->right = removeData(root->right, data);
    else{  // data found.
      
       if(root->left == nullptr || root->right == nullptr) 
        return root->left!=nullptr?root->left:root->right;
       
       Node* maxInleft=maximum(root->left);
       root->data=maxInleft->data;
       root->left=removeData(root->left,maxInleft->data);
    }
    return root;
}

Node *addDataItr(Node *root, int data)
{
    if(root==nullptr) return new Node(data);
    Node *curr = root;
    Node *prev = nullptr;
    while (curr != nullptr)
    {
        prev = curr;
        if (data < curr->data)
            curr = curr->left;
        else
            curr = curr->right;
    }

    if(data < prev->data) prev->left=new Node(data);
    else prev->right=new Node(data);
    return root;
}

void solve()
{

}

void main()
{
    solve();
}