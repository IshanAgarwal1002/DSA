#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Node{
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

int idx = 0;
Node* constructTree(vector<int> &arr)
{
    if(arr[idx] == -1 || idx >= arr.size()){
        idx++;
        return nullptr;
    }
    Node *root = new Node(arr[idx++]);
    root->left = constructTree(arr);
    root->right = constructTree(arr);

    return root;
}

void display(Node *root)
{
    if(root == nullptr)
        return;

    (root->left == nullptr)?(cout<<"."):(cout<<root->left->data);
    cout<<" -> "<<root->data<<" <- ";
    (root->right == nullptr)?(cout<<"."):(cout<<root->right->data);
    cout<<"\n";

    display(root->left);
    display(root->right);
}

//Basic==============================================================

int size(Node *root)
{
    if(root == nullptr)    return 0;
    return (size(root->left) + size(root->right) + 1);
}

int height(Node *root)
{
    if(root == nullptr)    return 0; // return -1, height w.r.t edge, return 0, height w.r.t node.
    return (max(height(root->left),height(root->right)) + 1);
}

int maximum(Node *root)
{
    if(root == nullptr)    return INT32_MIN; 
    return max(max(maximum(root->left),maximum(root->right)),root->data);
}

int minimum(Node *root)
{
    if(root == nullptr)    return INT32_MAX; 
    return min(min(minimum(root->left),minimum(root->right)),root->data);
}

int minimum2(Node* root)
{
    int min_=root->data;
       
    if(root->left!=nullptr) min_= min(min_,minimum2(root->left));
    if(root->right!=nullptr) min_= min(min_,minimum2(root->right));
       
    return min_;
}

bool find(Node *root, int ele){
    if(root == nullptr)    return false;
    if(root->data == ele)   return true;

    return find(root->left,ele) || find(root->right,ele);
}

//Traversal=================================================

void preOrder(Node *root)
{
    if(root==nullptr)  return;

    cout<<root->data<<" ";
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(Node *root)
{
    if(root==nullptr)  return;

    inOrder(root->left);
    cout<<root->data<<" ";
    inOrder(root->right);
}

void postOrder(Node *root)
{
    if(root==nullptr)  return;

    postOrder(root->left);
    postOrder(root->right);
    cout<<root->data<<" ";
}

//root to node path===================================
bool rootToNodePath(Node *root,int ele,vector<Node*> &path)
{
    if(root == nullptr)    return false;
    if(root->data == ele)
    {
        path.push_back(root);
        return true;
    }

    bool res = rootToNodePath(root->left,ele,path) || rootToNodePath(root->right,ele,path);
    if(res) path.push_back(root);

    return res;
}

vector<Node*> rootToNodePath_02(Node *root,int data)
{
    vector<Node*> base;
    if(root==nullptr){
        return base;
    }
        
    if(root->data==data){
        base.push_back(root);
        return base;
    }
  
    vector<Node*> left=rootToNodePath_02(root->left,data);
    if(left.size()!=0){
        left.push_back(root);
        return left;
    }
   
    vector<Node*> right=rootToNodePath_02(root->right,data);
    if(right.size()!=0){
        right.push_back(root);
        return right;
    }
        
    return base;
}

void rootToNodePath_(Node *root,int data){
    vector<Node*> path;
    bool ans = rootToNodePath(root,data,path);
    for(Node* n: path)
        cout<<n->data << " -> ";
    
    cout<<"\n";
}

//LCA========================================================
Node* lowestCommonAncestor(Node *root, int p, int q) {
    vector<Node*> path1;
    vector<Node*> path2;
        
    rootToNodePath(root,p,path1);
    rootToNodePath(root,q,path2);

    Node *prev=nullptr;
    int i=path1.size()-1;
    int j=path2.size()-1;
        
    while(i>=0 && j>=0)
    {
        if(path1[i]->data != path2[j]->data) break;
          
        prev=path1[i];
        i--;
        j--;
    }

    return prev;
} 

Node *LCANode = nullptr;
bool lowestCommonAncestor2(Node *root, int p,int q)
{
    if(root==nullptr)  return false;
    
    bool selfDone = false;
    if(root->data == p || root->data == q)
        selfDone = true;

    bool leftDone = lowestCommonAncestor2(root->left,p,q);
    if(selfDone && leftDone)    LCANode = root;
    if(LCANode != nullptr) return true;

    bool rightDone = lowestCommonAncestor2(root->right,p,q);
    if((selfDone && rightDone) || (leftDone && rightDone))    LCANode = root;
    if(LCANode != nullptr) return true;

    return (selfDone || rightDone || leftDone);
} 

//to print all nodes at kth distance from a ceratin node==========
void kDown(Node *root,int k,Node *blocknode)
{
    if((root == nullptr) || (root == blocknode))    return;

    if(k==0)
    {
        cout<<root->data<<" ";
        return;
    }

    kDown(root->left,k-1,blocknode);
    kDown(root->right,k-1,blocknode);
}

void allNodeKAway(Node *root,int target, int k)
{
    vector<Node*> path;
    bool ans = rootToNodePath(root,target,path);

    if(!ans)    return;

    Node *blocknode = nullptr;
    for(int i=0;i<path.size();i++)
    {
        if(k-i < 0) break;
        kDown(path[i],k-i,blocknode);
        blocknode = path[i];
    }
}

int allNodeKAway2(Node *root,int target, int k)
{
    if(root == nullptr) return -1;

    if(root-> data == target)
    {
        kDown(root,k,nullptr);
        return 1;
    }

    int leftDistance = allNodeKAway2(root->left,target,k);
    if(leftDistance != -1)
    {
        if(k - leftDistance >= 0)    kDown(root,k-leftDistance,root->left);
        return leftDistance+1;
    }

    int rightDistance = allNodeKAway2(root->right,target,k);
    if(rightDistance != -1)
    {
        if(k - rightDistance >= 0)    kDown(root,k-rightDistance,root->right);
        return rightDistance+1;
    }

    return -1;
}

void kDown(Node *root,int k)
{
    if(root == nullptr || k<0)    return;

    if(k==0)
    {
        cout<<root->data<<" ";
        return;
    }

    kDown(root->left,k-1);
    kDown(root->right,k-1);
}

int allNodeKAway3(Node *root, int target, int k)
{
    if(root == nullptr) return -1;

    if(root->data == target)
    {
        kDown(root,k);
        return 1;
    }

    int leftDistance = allNodeKAway3(root->left,target,k);
    if(leftDistance != -1)
    {
        if(k - leftDistance == 0)
            cout<<root->data<<" ";
        else
            kDown(root->right,k-leftDistance-1);
        return leftDistance+1;
    }

    int rightDistance = allNodeKAway3(root->right,target,k);
    if(rightDistance != -1)
    {
        if(k - rightDistance == 0)
            cout<<root->data<<" ";
        else
            kDown(root->left,k-rightDistance-1);
        return rightDistance+1;
    }

    return -1;
}

int diameter1(Node* root)
{
    if(root == nullptr) return 0;
    
    int ld = diameter1(root->left);
    int rd = diameter1(root->right);

    int lh = height(root->left);
    int rh = height(root->right);

    int myDia = lh + rh + 2;
    return max(max(ld,rd),myDia);
}

class diaPair{
    public:
    int dia=0;
    int hei=0;

    diaPair(int dia,int hei){
        this->dia=dia;
        this->hei=hei;
    }
};

diaPair diameter_02(Node *root){
    if(root==nullptr) return diaPair(0,-1) ;

    diaPair lr=diameter_02(root->left); // left result
    diaPair rr=diameter_02(root->right); // right result

    diaPair myRes(0,-1);
    myRes.dia = max(max(lr.dia,rr.dia), (lr.hei+rr.hei+2));
    myRes.hei = max(lr.hei,rr.hei)+1;
    
    return myRes;
}

static int diameter=0;
int diameter_03(Node *root){
    if(root==nullptr) return -1 ;

    int lh = diameter_03(root->left); // left height
    int rh = diameter_03(root->right); // right height
    
    diameter=max(diameter,lh+rh+2);
    return max(lh,rh)+1;
}

void set1(Node *root)
{    
    rootToNodePath_(root,100);
    
    // cout<<"LCA: "<<lowestCommonAncestor(root,110,120)->data;
    
    bool ans = lowestCommonAncestor2(root,40,50);
    cout<<"LCA: " << ((LCANode!=nullptr)?to_string(LCANode->data):"-1")<<"\n";

    // allNodeKAway(root,50,1);
    // allNodeKAway2(root,30,2);
    allNodeKAway3(root,90,6);
    diameter_03(root);
    cout<<"\n"<<diameter;
}

//level Order Series(BFS)========================================================    

//prints all elements in a single line
void leverOrder00(Node *root)
{
    queue <Node*> que;
    que.push(root);

    while(que.size() != 0)
    {
        Node *rNode = que.front();
        que.pop();
        cout<<rNode->data<<" ";
        if(rNode->left != nullptr)  que.push(rNode->left);
        if(rNode->right != nullptr)  que.push(rNode->right);
    }
}

//using parent and child queue
void leverOrder01(Node *root)
{
    queue <Node*> pQue;
    queue <Node*> cQue;
    pQue.push(root);

    int count = 0;
    cout<<"\nLevel "<<count<<": ";

    while(pQue.size() != 0)
    {
        Node *rNode = pQue.front();
        pQue.pop();
        cout<<rNode->data<<" ";
        if(rNode->left != nullptr)  cQue.push(rNode->left);
        if(rNode->right != nullptr)  cQue.push(rNode->right);

        if(pQue.size() == 0)
        {
            queue <Node*> temp = pQue;
            pQue = cQue;
            cQue = temp;
            count++;
            cout<<"\nLevel "<<count<<": ";
        }
    }
}

//using delimiter method
void leverOrder02(Node *root)
{
    queue <Node*> que;
    que.push(root);
    que.push(nullptr);

    int count = 0;
    cout<<"\nLevel "<<count<<": ";

    while(que.size() != 1)
    {
        Node *rNode = que.front();
        que.pop();
        cout<<rNode->data<<" ";
        if(rNode->left != nullptr)  que.push(rNode->left);
        if(rNode->right != nullptr)  que.push(rNode->right);

        if(que.front()==nullptr)
        {
            que.pop();
            que.push(nullptr);
            count++;
            cout<<"\nLevel "<<count<<": ";
        }
    }
}

//2 while loop method
void leverOrder03(Node *root)
{
    queue <Node*> que;
    que.push(root);

    int count = 0;

    while(que.size() != 0)
    {
        cout<<"\nLevel "<<count<<": ";
        int size = que.size();
        while(size--)
        {
            Node *rNode = que.front();
            que.pop();
            cout<<rNode->data<<" ";
            if(rNode->left != nullptr)  que.push(rNode->left);
            if(rNode->right != nullptr)  que.push(rNode->right);
        }
        count++;
    }
}

void levelOrderSeries(Node *root)
{
    // leverOrder00(root);
    // leverOrder01(root);
    // leverOrder02(root);
    leverOrder03(root);
}

//Views in tree=======================================================

//left view of tree
void leftView(Node *root)
{
    queue <Node*> que;
    que.push(root);

    while(que.size() != 0)
    {
        cout<<que.front()->data<<" ";
        int size = que.size();
        while(size--)
        {
            Node *rNode = que.front();
            que.pop();
            if(rNode->left != nullptr)  que.push(rNode->left);
            if(rNode->right != nullptr)  que.push(rNode->right);
        }
    }
    cout<<"\n";
}

//right view----------------------------------
void rightView(Node *root)
{
    queue <Node*> que;
    que.push(root);

    while(que.size() != 0)
    {
        cout<<que.back()->data<<" ";
        int size = que.size();
        while(size--)
        {
            Node *rNode = que.front();
            que.pop();
            if(rNode->left != nullptr)  que.push(rNode->left);
            if(rNode->right != nullptr)  que.push(rNode->right);
        }
    }
    cout<<"\n";
}

//width of tree======================
int leftMinValue = (int)1e8;
int rightMaxValue = (int)-1e8;
void width(Node *root,int lev)          //here lev is vertical level
{
    if(!root)   return;

    leftMinValue = min(leftMinValue,lev);
    rightMaxValue = max(rightMaxValue,lev);

    width(root->left,lev-1);
    width(root->right,lev+1);
}

class pairVO
{
    public:
        Node *root;
        int vl;     //vertical level
        pairVO(Node *root,int vl)
        {
            this->root = root;
            this->vl = vl;
        }
};

void verticalOrder(Node *root)
{
    width(root,0);
    int n = rightMaxValue - leftMinValue + 1;
    vector<vector<int>> ans(n);

    queue<pairVO> que;
    que.push(pairVO(root,-leftMinValue));
    while(que.size()!=0)
    {
        int size = que.size();
        while(size--)
        {
            pairVO rNode = que.front();
            que.pop();
            ans[rNode.vl].push_back(rNode.root->data);
            if(rNode.root->left)    que.push(pairVO(rNode.root->left,rNode.vl - 1));
            if(rNode.root->right)    que.push(pairVO(rNode.root->right,rNode.vl + 1));
        }
    }

    for(vector<int> ar:ans)
    {
        cout<<"[ ";
        for(int i:ar)
            cout<<i<<" ";
        cout<<"]\n";
    }
}

//vertical order sum=======================================================
void verticalOrderSum(Node *root)
{
    width(root, 0);
    vector<int> ans(rightMaxValue - leftMinValue + 1,0);

    queue<pairVO> que;
    que.push(pairVO(root,-leftMinValue));

    while(que.size() != 0)
    {
        int size = que.size();
        while(size--)
        {
            pairVO rNode = que.front();
            que.pop();
            ans[rNode.vl] += rNode.root->data;
            if(rNode.root->left)    que.push(pairVO(rNode.root->left,rNode.vl - 1));
            if(rNode.root->right)    que.push(pairVO(rNode.root->right,rNode.vl + 1));
        }
    }

    for(int i:ans)
        cout<<i<<" ";
}

//bottom view========================================
void bottomView(Node *root)
{
    width(root,0);
    vector<int> ans(rightMaxValue - leftMinValue + 1);

    queue<pairVO> que;
    que.push(pairVO(root,-leftMinValue));

    while(que.size() != 0)
    {
        int size = que.size();
        while(size--)
        {
            pairVO rNode = que.front();
            que.pop();
            ans[rNode.vl] = rNode.root->data;
            if(rNode.root->left)    que.push(pairVO(rNode.root->left,rNode.vl - 1));
            if(rNode.root->right)    que.push(pairVO(rNode.root->right,rNode.vl + 1));
        }
    }

    for(int i:ans)
        cout<<i<<" ";
    cout<<"\n";
}

//top view----------------------------------------------
void topView(Node *root)
{
    width(root,0);
    vector<int> ans(rightMaxValue - leftMinValue + 1,(int)-1e8);

    queue<pairVO> que;
    que.push(pairVO(root,-leftMinValue));

    while(que.size() != 0)
    {
        int size = que.size();
        while(size--)
        {
            pairVO rNode = que.front();
            que.pop();
            if(ans[rNode.vl] == (int)-1e8)
                ans[rNode.vl] = rNode.root->data;
            if(rNode.root->left)    que.push(pairVO(rNode.root->left,rNode.vl - 1));
            if(rNode.root->right)    que.push(pairVO(rNode.root->right,rNode.vl + 1));
        }
    }

    for(int i:ans)
        cout<<i<<" ";
    cout<<"\n";
}

//no. of diagonals in tree------------------------------------
void widthDiagonal(Node *root,int lev)      //lev is diagonal level
{
    if(!root)   return;

    leftMinValue = min(leftMinValue,lev);

    width(root->left,lev-1); 
    width(root->right,lev);  
}

//diagonal order-----------------------------------------------
void diagonalOrder(Node *root)
{
    widthDiagonal(root,0);
    vector<vector<int>> ans(-leftMinValue + 1);

    queue<pairVO> que;
    que.push(pairVO(root,-leftMinValue));

    while(que.size() != 0)
    {
        int size = que.size();
        while(size--)
        {
            pairVO rNode = que.front();
            que.pop();
            ans[rNode.vl].push_back(rNode.root->data);
            if(rNode.root->left)    que.push(pairVO(rNode.root->left,rNode.vl - 1));
            if(rNode.root->right)    que.push(pairVO(rNode.root->right,rNode.vl));
        }
    }

    for(vector<int> ar:ans)
    {
        cout<<"[ ";
        for(int i:ar)
            cout<<i<<" ";
        cout<<"]\n";
    }
}

//diagonal order sum---------------------------------------
void diagonalOrderSum(Node *root)
{
    widthDiagonal(root,0);
    vector<int> ans(-leftMinValue + 1,0);

    queue<pairVO> que;
    que.push(pairVO(root,-leftMinValue));

    while(que.size() != 0)
    {
        int size = que.size();
        while(size--)
        {
            pairVO rNode = que.front();
            que.pop();
            ans[rNode.vl] += rNode.root->data;
            if(rNode.root->left)    que.push(pairVO(rNode.root->left,rNode.vl - 1));
            if(rNode.root->right)    que.push(pairVO(rNode.root->right,rNode.vl));
        }
    }

    for(int i:ans)
        cout<<i<<" ";
    cout<<"\n";
}

void View(Node *root)
{
    // leftView(root);
    // rightView(root);
    // verticalOrder(root);
    // verticalOrderSum(root);
    bottomView(root);
    topView(root);
    diagonalOrder(root);
    diagonalOrderSum(root);
}

//tree to doubly linked list===============================
Node *DLLhead = nullptr;
Node *DLLprev = nullptr;

void DLL(Node *root)
{
    if(!root)   return;

    DLL(root->left);

    if(!DLLhead)    DLLhead = root;
    else{
        DLLprev->right = root;
        root->left = DLLprev;
    }
    DLLprev = root;

    DLL(root->right);
}

class allSolution{
    public:
        int height = 0;
        int size=0;
        bool find=false;
 
        Node *pred=nullptr;
        Node *succ=nullptr;
        Node *prev=nullptr;
};
 
void allSol(Node *node,int data,int level,allSolution pair){
     if(node==nullptr) return;
     pair.size++;
     pair.height=max(pair.height,level);
     pair.find= pair.find || node->data==data;
     
     if(node->data==data && pair.pred==nullptr) pair.pred=pair.prev;
     if(pair.prev!=nullptr && pair.prev->data == data && pair.succ==nullptr) pair.succ=node;
     pair.prev=node;
     
      allSol(node->left,data,level+1,pair);
      allSol(node->right,data,level+1,pair);
}

Node* linearize(Node* root){
    if(root == nullptr){
        return nullptr;
    }

    if(root->left == nullptr && root->right == nullptr){
        return root;
    }

    Node* leftTail = linearize(root->left);
    Node* rightTail = linearize(root->right);
    if(leftTail == nullptr){
        root->left = root->right;
    }
    else{
        leftTail->left = root->right;
    }
    root->right=nullptr;
    return rightTail != nullptr ? rightTail : leftTail;
}

void solve()
{
    vector<int> arr = {10, 20, 40, -1, -1, 50, 80, -1, -1, 90, -1, -1, 30, 60, 100, -1, -1, -1, 70, 110, -1, -1, 120, -1, -1};
    Node *root = constructTree(arr);
    display(root);
    // set1(root);
    // levelOrderSeries(root);
    View(root);
}

int main()
{
    solve();
    return 0;
}