import java.util.ArrayList;

public class heap_basic{

    public static int height(int[] arr, int idx)
    {
        if(idx >= arr.length)
            return -1;

        int lh = height(arr,2*idx+1);
        int rh = height(arr,2*idx+2);

        return Math.max(lh,rh) + 1;
    }

    public static int size(int[] arr, int idx)
    {
        if(idx >= arr.length)
            return 0;

        int ls = size(arr,2*idx+1);
        int rs = size(arr,2*idx+2);

        return ls + rs + 1;
    }

    //heap==============================================
    
    public static class Heap
    {
        ArrayList<Integer> arr = new ArrayList<>();
        boolean isMaxHeap = true;

        public Heap(int[] list, boolean isMaxHeap) {
            this.isMaxHeap = isMaxHeap;
            for (int ele : list)
                this.arr.add(ele);

            int n = arr.size();
            for (int i = n - 1; i >= 0; i--) {// (nlogn -> o(n)) , i = (n/2) + 1
                downHeapify(i, n);
            }
        }

        public Heap(int[] list)
        {
          this.heap(list, true);
        }

        public Heap() {
            arr.clear();
        }

        // Basic_Util.=============================================================================
        
        public void swap(int x, int y)
        {
            int ele1 = arr.get(x);
            int ele2 = arr.get(y);

            arr.set(x,ele2);
            arr.set(y,ele1);
        }

        public int compareTo(int x, int y) {
            if (isMaxHeap) {
                return this.arr.get(x) - this.arr.get(y); // this-other , default behaviour, in CPP '-' replace wit '<'
            } else {
                return this.arr.get(y) - this.arr.get(x); // other - this
            }
        }

        //on changing > to < in line 62 and 64, this function will create minHeap instead of maxHeap
        public void downHeapify(int pi,int n)           //creates MaxHeap
        {
            int lci = 2*pi+1;   //left child index
            int rci = 2*pi+2;   //right child index
            int maxIdx = pi;

            if(lci<n && compareTo(lci, maxIdx)>0)
                maxIdx = lci;
            if(rci<n && compareTo(rci, maxIdx)>0)
                maxIdx = rci;
        
            if(pi!=maxIdx)
            {
                swap(pi,maxIdx);
                downHeapify(maxIdx,n);
            }
        }

        public void upHeapify(int ci)
        {
            int pi = (ci-1)/2;
            if(pi>=0 && compareTo(ci, pi)>0)
            {
                swap(ci,pi);
                upHeapify(pi);
            }
        }

        //user functions==================================

        public boolean isEmpty()
        {
            return arr.size()==0;
        }

        public int size()
        {
            return arr.size();
        }

        public int top()
        {
            if(isEmpty())   return -1;
            return arr.get(0);
        }

        public void push(int val)
        {
            arr.add(val);
            upHeapify(arr.size()-1);
        }

        public void pop()
        {
            if(isEmpty())   return;
            
            swap(0,arr.size() - 1);
            arr.remove(arr.size() - 1);
            downHeapify(0,arr.size());
        }

    }

    public static void main(String[] args) {
        int[] arr2 = { 10, 20, 30, -2, -3, -4, 5, 6, 7, 8, 9, 22, 11, 13 };
        // System.out.println(height(arr2, 0));
        // System.out.println(size(arr2, 0));

        Heap pq = new Heap();
        for (int ele : arr2)
            pq.push(ele);

        // Heap pq = new Heap(arr2, true);
        pq.push(100);
        pq.push(25);
        while (pq.size() != 0) { // nlog(n)
            System.out.print(pq.top() + " ");
            pq.pop();
        }
    }

}