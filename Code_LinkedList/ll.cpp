#include<iostream>
using namespace std;

class linkedlist
{
    class Node
    {
        public:
            int data;
            Node *next;

            Node(){}
            Node(int data)
            {
                this->data = data;
                next = nullptr;
            }
    };

    //retrieval
    Node* getNodeAt(int pos)
    {        
        Node *curr = head;  
        while(pos--)            //0 based indexing
            curr = curr->next;
        
        return curr;
    }

    //insertion
    void addFirstNode(Node *node)
    {
        if(size_ == 0)
            head = tail = node;
        else{
            node->next = head;
            head = node;
        }
        size_++;
    }

    void addLastNode(Node *node)
    {
        if(size_ == 0)
            head = tail = node;
        else{
            tail->next = node;
            tail = node;
        }
        size_++;
    }

    void addAtNode(Node *node, int pos)
    {
        if(pos == 0)
            addFirstNode(node);
        else if(pos == size_)
            addLastNode(node);
        else{
            Node *prev = getNodeAt(pos-1);
            Node *fwd = prev->next;

            prev->next = node;
            node->next = fwd;
            size_++;
        }
    }

    public:

        Node *head;
        Node *tail;
        int size_;

        linkedlist()
        {
            head = nullptr;
            tail = nullptr;
            size_ = 0;
        }

        int size()
        {
            return size_;
        }

        bool isEmpty()
        {
            return size_==0;
        }

        void display()
        {
            if(isEmpty())
            {
                cout<<"Empty List";
                return;
            }
            Node *curr = head;
            while(curr!=nullptr)
            {
                cout<<curr->data<<" -> ";
                curr = curr->next;
            }
            cout<<"\n";
        }

        //insertion=====================================
        
        void addFirst(int data)
        {
            Node *node = new Node(data);
            addFirstNode(node);
        }

        void addLast(int data)
        {
            Node *node = new Node(data);
            addLastNode(node);
        }

        void addAt(int data, int pos)
        {
            if(pos<0 || pos>size_)
            {
                cout<<"Null pointer exception";
                return;
            }
            Node *node = new Node(data);
            addAtNode(node,pos);
        }

        //deletion=======================================
        void removeFirst()
        {   
            if(isEmpty())
            {
                cout<<"Empty";
                return;
            }

            if(size_ == 1){
                delete head;
                head = tail = nullptr;
            }
            else{
                Node *node = head;
                head = head->next;
                delete node;
            }
            size_--;
        }

        void removeLast()
        {   
            if(isEmpty())
            {
                cout<<"Empty";
                return;
            }

            if(size_ == 1){
                delete head;
                head = tail = nullptr;
            }
            else{
                Node *node = tail;
                tail = getNodeAt(size_-2);
                tail->next = nullptr;
                delete node;
            }
            size_--;
        }

        void removeAt(int pos)
        {   
            if(pos<0 || pos>=size_)
            {
                cout<<"Null pointer exception";
                return;
            }

            if(pos == 0)
                removeFirst();
            else if(pos == size_-1)
                removeLast();
            else{
                Node *prev = getNodeAt(pos-1);
                Node *node = prev->next;
                prev->next = node->next;
                delete node;
                size_--;
            }
        }

        //retrieval========================================
        Node* getFirst()
        {
            if(isEmpty())
            {
                cout<<"Empty List";
                return nullptr;
            }
            return head;
        }

        Node* getLast()
        {
            if(isEmpty())
            {
                cout<<"Empty List";
                return nullptr;
            }
            return tail;
        }

        Node* getAt(int pos)
        {
            if(pos<0 || pos>=size_)
            {
                cout<<"Null pointer exception";
                return nullptr;
            }
            
            getNodeAt(pos);
        }

        //garbage collection (automatically done in java but not in C++)
        ~linkedlist()
        {
            Node *curr = head;
            Node *next;
            while(curr!=nullptr)
            {
                next = curr->next;
                delete curr;
                curr = next;
            }
        }
};


int main(){
    linkedlist ll;
    for(int i=1;i<10;i++){
        ll.addFirst(i*10);
    }
    ll.display();

    return 0;
}