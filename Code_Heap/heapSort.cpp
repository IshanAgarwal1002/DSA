#include<iostream>
#include<vector>
using namespace std;

//on changing < to > in line 12 and 14, this function will create minHeap instead of maxHeap
// pi - parent index
void downHeapify(vector<int> &arr, int pi, int n)
{
    int lci = 2*pi +1;
    int rci = 2*pi + 2;
    int maxIdx = pi;

    if(lci<n && arr[maxIdx]<arr[lci])
        maxIdx = lci;
    if(rci<n && arr[maxIdx]<arr[rci])
        maxIdx = rci;
    
    if(maxIdx != pi)
    {
        swap(arr[pi],arr[maxIdx]);
        downHeapify(arr,maxIdx,n);
    }
}

//if maxHeap is created -> ascending order, if minHeap is created -> descending order 
void heapSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = n-1; i >= 0; i--)
        downHeapify(arr, i, n);

    while (n != 0)
    {
        swap(arr[0], arr[--n]);
        downHeapify(arr, 0, n);
    }

    for (int ele : arr)
        cout << ele << " ";
}

void solve()
{
    vector<int> arr{10, 20, 30, -2, -3, -4, 5, 6, 7, 8, 9, 22, 11, 13};
    heapSort(arr);
}

int main()
{
    solve();
    return 0;
}