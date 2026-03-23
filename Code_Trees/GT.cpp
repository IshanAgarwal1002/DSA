#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;

class Node{
    public:
        int data;
        vector<Node*> children;

        Node(){}
        Node(int data)
        {
            this->data = data;
        }
};

Node* constructGT(vector<int> &arr)
{
    stack<Node*> st;

    for(int i=0;i<arr.size() - 1;i++)
    {
        if(arr[i]!=-1)
        {
            Node* root = new Node(arr[i]);
            st.push(root);
        }
        else{
            Node *node = st.top();
            st.pop();
            st.top()->children.push_back(node);
        }
    }

    return st.top();
}

void preOrder(Node *root)
{
    cout<<root->data<<" ";

    for(Node* child:root->children)
        preOrder(child);
}

void display(Node *root)
{
    cout<<root->data<<" -> ";
    for(Node* child:root->children)
    {
        cout<<child->data<<" ";
    }
    cout<<"\n";
    for(Node* child:root->children)
    {
        display(child);
    }
}

int height(Node *root)
{
    int h = 0;
    for(Node* child:root->children)
    {
        h = max(h,height(child));
    }
    return h+1;
}

int size(Node *root)
{
    int s = 0;
    for(Node* child:root->children)
    {
        s += size(child);
    }
    return s+1;
}

bool find(Node *root, int data)
{
    if(root->data == data)
        return true;
    
    bool res = false;
    for(Node* child:root->children)
    {
        res = res || find(child,data);
    }
    return res;
}

int maximum(Node *root)
{
    int M = root->data;
    for(Node* child:root->children)
    {
        M = max(M,maximum(child));
    }
    return M;
}

int minimum(Node *root)
{
    int M = root->data;
    for(Node* child:root->children)
    {
        M = min(M,minimum(child));
    }
    return M;
}

int Ceil = INT32_MAX;
void ceil(Node *root, int val)
{
    if(root->data > val && root->data < Ceil)
        Ceil = root->data;

    for(Node* child:root->children)
        ceil(child,val);
}

int Floor = INT32_MIN;
void floor(Node *root, int val)
{
    if(root->data < val && root->data > Floor)
        Floor = root->data;

    for(Node* child:root->children)
        floor(child,val);
}

void set1(Node *root)
{
    cout<<height(root)<<"\n";
    cout<<size(root)<<"\n";
    cout<<find(root,55)<<"\n";
    cout<<maximum(root)<<"\n";
    ceil(root,71);
    cout<<Ceil<<"\n";
    floor(root,71);
    cout<<Floor<<"\n";
}

bool rootToNodePath(Node *root, int data, vector<Node*> &path)
{
    if(root->data == data)
    {
        path.push_back(root);
        return true;
    }

    path.push_back(root);
    bool res = false;
    for(Node* child:root->children)
    {
        res = res || rootToNodePath(child,data,path);
    }

    if(!res)    path.pop_back();
    return res;
}

void levelOrder(Node* root)
{
    queue<Node*> que;
    que.push(root);

    int level= 0;
    while(que.size()!=0)
    {
        cout<<"Level "<<level<<": ";
        int size = que.size();
        while(size--)
        {
            Node* rNode = que.front();
            que.pop();
            cout<<rNode->data<<" ";

            for(Node* child:rNode->children)
                que.push(child);
        }
        ++level;
        cout<<"\n";
    }
}

bool isMirror(Node* root1, Node* root2)         //O(n)
{
    if(root1->children.size() != root2->children.size() || root1->data != root2->data)
        return false;

    for(int i=0, j = root1->children.size()-1; j>=0; i++, j--)
    {
        if(!isMirror(root1->children[i],root2->children[j]))
            return false;
    }    
    return true;
}

bool isSymmetric(Node* root1, Node* root2)         //O(n)
{
    if(root1->children.size() != root2->children.size())
        return false;

    for(int i=0, j = root1->children.size()-1; j>=0; i++, j--)
    {
        if(!isMirror(root1->children[i],root2->children[j]))
            return false;
    }    
    return true;
}

Node* linearize(Node *root)
{
    if(root->children.size()==0)    return root;

    int n = root->children.size();
    Node* lastTail = linearize(root->children[n-1]);
    for(int i = n-2;i>=0;i--)
    {
        Node* secondLastTail = linearize(root->children[i]);

        secondLastTail->children.push_back(root->children[i+1]);    // connection between two linearize structure.

        root->children.pop_back();    //remove last node
    }

    return lastTail;
}

void flattern(Node *root)
{
    vector<Node*> nChildren;

    for(Node* child:root->children)
    {
        flattern(child);

        nChildren.push_back(child);
        for(Node* ch:child->children)
        {
            nChildren.push_back(ch);
        }
        child->children.clear();
    }

    root->children.clear();
    root->children = nChildren;
}

int diam = 0;
int diameter(Node *root)
{
    if(root->children.size() == 0)
        return 1;

    int h = 0, max1 = 0,max2 = 0;
    for(Node* child:root->children)
    {
        h = diameter(child);
        if(h>max1)
        {
            max2 = max1;
            max1 = h;
        } else if(h>max2)
            max2 = h;
    }

    diam = max(diam,max1+max2+1);
    return max1+1;
}

void set2(Node* root)
{
    // vector<Node*> path;
    // if(rootToNodePath(root,100,path))    
    // {
    //     for(Node* a:path)
    //         cout<<a->data<<" ";
    // }
    levelOrder(root);
}

void solve()
{
    vector<int> arr={10, 20, 50, -1, 60, -1, -1, 30, 70, -1, 80, 100, -1, 110, -1, -1, 90, -1, -1, 40, 120, 140, -1, 150, -1, -1, -1,-1};
    Node *root = constructGT(arr);
    display(root);
    // set1(root);
    set2(root);
}

int main()
{
    solve();
    return 0;
}