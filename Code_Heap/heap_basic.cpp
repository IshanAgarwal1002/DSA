#include<iostream>
#include<vector>
using namespace std;

int height(vector<int> &arr, int idx)
{
    if(idx>=arr.size())
        return -1;

    int lh = height(arr,2*idx+1); 
    int rh = height(arr,2*idx+2);

    return max(lh,rh)+1; 
}

int Size(vector<int> &arr, int idx)
{
    if(idx>=arr.size())
        return 0;

    int ls = Size(arr,2*idx+1); 
    int rs = Size(arr,2*idx+2);

    return ls+rs+1; 
}

class Heap{

    vector<int> arr;
    bool isMaxHeap = true;

    public:

        Heap(){
            arr.clear();
        }

        Heap(vector<int> &list)
        {
            arr = list;

            int n = arr.size();
            for(int i=n-1;i>=0;i--)
            {
                downHeapify(i,n);
            }
        }

        Heap(vector<int> &list, bool isMaxHeap)
        {
            this->isMaxHeap = isMaxHeap;

            arr = list;

            int n = arr.size();
            for(int i=n-1;i>=0;i--)
            {
                downHeapify(i,n);
            }
        }

        //basic_util======================================================================

        bool compareTo(int x, int y) {
            if (isMaxHeap) {
                return this->arr[x] > this->arr[y]; // this-other , default behaviour, in CPP '-' replace wit '<'
            } else {
                return this->arr[y] > this->arr[x]; // other - this
            }
        }

        void downHeapify(int pi, int n)
        {
            int lci = 2*pi+1;
            int rci = 2*pi+2;
            int maxIdx = pi;

            if(lci<n && compareTo(lci,maxIdx))
                maxIdx = lci;
            if(rci<n && compareTo(rci,maxIdx))
                maxIdx = rci;

            if(pi!=maxIdx)
            {
                swap(arr[pi],arr[maxIdx]);
                downHeapify(maxIdx, n);
            }
        }

        void upHeapify(int ci)
        {
            int pi = (ci-1)/2;
            if(pi>=0 && compareTo(ci,pi))
            {
                swap(arr[ci],arr[pi]);
                upHeapify(pi);
            }
        }

        //user functions===================================================

        bool isEmpty()
        {
            return arr.size()==0;
        }

        int Size()
        {
            return arr.size();
        }

        int top()
        {
            if(isEmpty()) return -1;
            return arr[0];
        }

        void push(int val)
        {
            arr.push_back(val);
            upHeapify(arr.size()-1);
        }

        void pop()
        {
            if(isEmpty())   return;

            swap(arr[0],arr[arr.size()-1]);
            arr.erase(arr.end()-1);
            downHeapify(0,arr.size());
        }

};

void solve() 
{
    vector<int> arr = { 10, 20, 30, -2, -3, -4, 5, 6, 7, 8, 9, 22, 11, 13 };
    // cout<<height(arr, 0)<<"\n";
    // cout<<Size(arr, 0)<<"\n";

    // Heap pq;
    // for (int ele : arr)
    //     pq.push(ele);

    // Heap pq(arr);

    Heap pq(arr,false);
    pq.push(100);
    pq.push(25);
    while (pq.Size() != 0) 
    { // nlog(n)
        cout<<pq.top()<<" ";
        pq.pop();
    }
}

int main()
{
    solve();
    return 0;
}