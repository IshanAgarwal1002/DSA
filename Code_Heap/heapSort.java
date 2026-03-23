import java.util.ArrayList;

public class heapSort {
    
    public static void swap(ArrayList<Integer> arr,int x, int y)
    {
        int ele1 = arr.get(x);
        int ele2 = arr.get(y);

        arr.set(x,ele2);
        arr.set(y,ele1);
    }

    //on changing > to < in line 21 and 23, this function will create minHeap instead of maxHeap
    public static void downHeapify(ArrayList<Integer> arr,int pi,int n)
    {
        int lci = 2*pi+1;   //left child index
        int rci = 2*pi+2;   //right child index
        int maxIdx = pi;

        if(lci<n && arr.get(lci) > arr.get(maxIdx))
            maxIdx = lci;
        if(rci<n && arr.get(rci) > arr.get(maxIdx))
            maxIdx = rci;
        
        if(pi!=maxIdx)
        {
            swap(arr,pi,maxIdx);
            downHeapify(arr,maxIdx,n);
        }
    }

    //if maxHeap is created -> ascending order, if minHeap is created -> descending order 
    public static void HeapSort(ArrayList<Integer> arr)
    {
        int n = arr.size();
        for(int i = n-1;i>=0;i--)
        {
            downHeapify(arr, i, n);
        }

        while(n!=0)
        {
            swap(arr,0,--n);
            downHeapify(arr,0,n);
        }

        for(int i:arr)
            System.out.print(i + " ");
    }

    public static void solve()
    {
        int[] list = {10, 20, 30, -2, -3, -4, 5, 6, 7, 8, 9, 22, 11, 13};
        ArrayList<Integer> arr = new ArrayList<>();
        for(int ele:list)
            arr.add(ele);
        HeapSort(arr);
    }

    public static void main(String[] args)
    {
        solve();
    }
}