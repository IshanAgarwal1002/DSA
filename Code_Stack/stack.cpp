#include<iostream>
using namespace std;

class Stack
{
    int N = 10000;
    int *arr;
    int tos = -1;        //top of stack
    int Size = 0;

    public:
        Stack()
        {
            arr = new int[N];
        }

        Stack(int size)
        {
            arr = new int[size];
            N = size;
        }

        int size()
        {
            return Size;
        }

        bool isEmpty()
        {
            return Size==0; 
        }

        void push(int data)
        {
            if (Size == N)
                return;
            tos++;
            Size++;
            arr[tos] = data;
        }

        void pop()
        {
            if(Size == 0)
                return;
            Size--;
            tos--;
        }
        
        int top()
        {
            if(Size==0)
                return -1;
            return arr[tos];
        }


        ~Stack()
        {
            delete arr;
        }
};

void solve()
{
    Stack st(10); //stack
    // Mystack* st=new Mystack(); // heap

    for (int i = 1; i <= 10; i++)
        st.push(10 + i);

    while (st.size() != 0)
    {
        cout << st.top() << " ";
        st.pop();
    }
    
}

int main()
{
    solve();
    return 0;
}