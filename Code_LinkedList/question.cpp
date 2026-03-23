#include<iostream>
#include<unordered_map>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//1290. Convert Binary Number in a Linked List to Integer
int getDecimalValue(ListNode* head) {
        if(head == nullptr) return 0;
        
        int ans = head->val;
        head = head->next;
        while(head)
        {
            ans = (ans<<1)|head->val;
            head = head->next;
        }
        return ans;
}

//1721. Swapping Nodes in a Linked List
ListNode* swapNodes(ListNode* head, int k) {
        ListNode *node1, *node2;
        
        //kth from end
        ListNode *slow = head, *fast = head;
        
        int tk = k;
        while(tk--)
            fast = fast->next;
        
        while(fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
            
        node2 = slow;
        
        //kth from start
        slow = head;
        tk = k;
        while(tk-- > 1)
        {
            slow = slow->next;
        }
        
        node1 = slow;

        //swap
        int val = node1->val;
        node1->val = node2->val;
        node2->val = val;
        
        return head;
}

//leetcode 1171

// Time - O(N*N)  Space - O(1)
// Brute Force Approach
ListNode* removeZeroSumSublists(ListNode* head) {
    ListNode *dummy = new ListNode(0);
    dummy->next = head;
    ListNode *prev = dummy;

    while(head)
    {
        ListNode *curr = head;
        int sum = 0, flag = 0;
        while(curr)
        {
            sum+=curr->val;
            curr = curr->next;
            if(sum==0)
            {
                flag = 1;
                break;
            }
        }

        if(flag)
        {
            prev->next = curr;
            head = curr;
            continue;
        }

        prev = head;
        head = head->next;
    }

    return dummy->next;
}

// Time - O(2N)  Space - O(N)
// Using HashMap
//but still this method is slow, beacuse we haven't taken into account the time complexity of operations done on map
ListNode* removeZeroSumSublists(ListNode* head) {

    ListNode *dummy = new ListNode(0);
    dummy->next = head;

    unordered_map<int, ListNode*> map;
    map[0] = dummy;

    int sum = 0;
    while(head)
    {
        sum += head->val;

        if(map.find(sum) != map.end())
        {
            int tempSum = sum;
            ListNode *NodeToBeDeleted = map[sum]->next;
            while(NodeToBeDeleted != head)
            {
                tempSum += NodeToBeDeleted->val;
                map.erase(tempSum);
                NodeToBeDeleted = NodeToBeDeleted->next;
            }

            map[sum]->next = head->next;
        }
        else{
            map[sum] = head;
        }

        head = head->next;
    }

    return dummy->next;
}

//Josh Technology Group Interview 1
//Flattening a Linked List
//https://www.geeksforgeeks.org/flattening-a-linked-list/
// Given a linked list where every node represents a linked list and contains two pointers of its type: 
// (i) Pointer to next node in the main list (we call it ‘right’ pointer in the code below) 
// (ii) Pointer to a linked list where this node is headed (we call it the ‘down’ pointer in the code below). 
// All linked lists are sorted. See the following example  
//        5 -> 10 -> 19 -> 28
//        |    |     |     |
//        V    V     V     V
//        7    20    22    35
//        |          |     |
//        V          V     V
//        8          50    40
//        |                |
//        V                V
//        30               45
// Write a function flatten() to flatten the lists into a single linked list. The flattened linked list should also be sorted. 
//For example, for the above input list, output list should be 5->7->8->10->19->20->22->28->30->35->40->45->50. 

class Node{
    public:
        int data;
        Node* next;
        Node* bottom;

        Node(){
            next = bottom = nullptr;
        }

        Node(int n)
        {
            data = n;
            next = bottom = nullptr;
        }
};

Node* mergeTwoLists(Node *l1, Node *l2)
{
    if(!l1) return l2;
    if(!l2) return l1;

    Node *ans = new Node(0);

    Node *curr1 = l1, *curr2 = l2, *curr3 = ans;

    while(curr1 && curr2)
    {
        if(curr1->data <= curr2->data)
        {
            curr3->bottom = curr1;
            curr1 = curr1->bottom;
        }
        else{
            curr3->bottom = curr2;
            curr2 = curr2->bottom;
        }
        curr3 = curr3->bottom;
    }

    if(curr1)   curr3->bottom = curr1;
    else  curr3->bottom = curr2;

    return ans->bottom;
}

Node* flatten(Node *head)
{
    if(!head || !head->next)
        return head;

    Node *curr = head;

    while(curr->next)
    {
        Node *temp = curr->next->next;
        Node *fwd = curr->next;
        curr->next = curr->next->next = nullptr;

        curr = mergeTwoLists(curr, fwd);
        curr->next = temp;
    }

    return curr;
}