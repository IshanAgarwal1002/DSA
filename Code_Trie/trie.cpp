#include<iostream>
#include<vector>
using namespace std;

class Node{
public:
    int wordEnd;
    vector<Node*> childs;

    Node()
    {
        this->wordEnd = 0;
        this->childs.assign(26,nullptr);
    }
};

Node *root = nullptr;

void insert(string word)
{
    Node *curr = root;
    int n = word.length();
    for(int i=0;i<n;i++)
    {
        int idx = word[i] - 'a';
        if(curr->childs[idx]==nullptr)
            curr->childs[idx] = new Node();
        curr = curr->childs[idx];
    }
    curr->wordEnd++;
}

int main()
{

}