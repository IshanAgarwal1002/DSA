#include<iostream>
#include<vector>
using namespace std;

class Node
{
    public:
        int data;
        Node *left;
        Node *right;

        Node(int data, Node *left, Node *right)
        {
            this->data = data;
            this->left = left;
            this->right = right;
        }
};

int idx = 0; 

Node* create(vector<int> arr)
{
    if(arr[idx] == -1 || idx == arr.size())
    {
        idx++;
        return NULL;
    }
    Node *root = new Node(arr[idx],NULL,NULL);
    idx++;
    root->left = create(arr);
    root->right = create(arr);

    return root;
}

void solve()
{
    vector<int> arr = {10, 20, 30, -1, -1, 40, -1, -1, 50, 60, 80, -1, -1, -1, 70, 90, -1, 100, -1, -1, -1};
    Node *root = create(arr);
    
}

int main()
{
    solve(); 
    return 0;
}