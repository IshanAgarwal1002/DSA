import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Arrays;
import java.util.Stack;

public class GT{
    
    public static class Node{
        int data;
        ArrayList<Node> children = new ArrayList<>();
        
        Node(){}
        Node(int data){
            this.data = data;
        }    
    };

    public static Node construct(int[] arr){
        Stack<Node> st = new Stack<>();
        
        for(int i=0;i<arr.length - 1;i++)
        {
            if(arr[i] != -1)
            {
                Node node = new Node(arr[i]);
                st.push(node);
            }
            else
            {
                Node node = st.pop();
                st.peek().children.add(node);
            }
        }
        return st.pop();
    }

    public static void preOrder(Node root){
        System.out.print(root.data + " ");

        for(Node child:root.children){
            preOrder(child);
        }
    }

    public static void display(Node root)
    {
        System.out.print(root.data + " -> ");
        for(Node child : root.children)
        {
            System.out.print(child.data + " ");
        }
        System.out.println();
        for(Node child : root.children)
        {
            display(child);
        }
    }

    public static int height(Node root)
    {
        int h=0;
        for(Node child:root.children)
        {
            h = Math.max(h, height(child));
        }
        return h+1;
    }

    public static int size(Node root)
    {
        int s=0;
        for(Node child:root.children)
        {
            s+=size(child);
        }
        return s+1;
    }

    public static boolean find(Node root, int data)
    {
        if(root.data == data)   return true;
        boolean res = false;
        for(Node child : root.children)
        {
            res = res || find(child,data);
        }
        return res;
    }

    public static int maximum(Node root)
    {
        int max = root.data;
        for(Node child:root.children)
        {
            max = Math.max(max,maximum(child));
        }
        return max;
    }

    public static int minimum(Node root)
    {
        int min = root.data;
        for(Node child:root.children)
        {
            min = Math.min(min,minimum(child));
        }
        return min;
    }
       
    static int ceil = Integer.MAX_VALUE;
    public static void ceil(Node root,int val)
    {
        if(root.data>val && root.data<ceil){
            ceil = root.data;
        }
        for(Node n:root.children){
            ceil(n,val);
        }
    }

    static int floor = Integer.MIN_VALUE;
    public static void floor(Node root,int val)
    {
        if(root.data<val && root.data>floor){
            floor = root.data;
        }
        for(Node n:root.children){
            floor(n,val);
        }
    }
    
    public static boolean rootToNodePath(Node node,int data,ArrayList<Node> path)
    {
        if(node.data==data){
            path.add(node);
            return true;
        }
        boolean res=false;
        path.add(node);
    
        for(Node child: node.children){
            res=res|| rootToNodePath(child,data,path);
        }
    
        if(!res) path.remove(path.size()-1);
        return res;
    }
    
    public static void levelOrder(Node node){
        LinkedList<Node> que=new LinkedList<>();// addLast, removeFirst.
        que.addLast(node);
        
        int level = 0;

        while(que.size()!=0){
            System.out.print("Level " + level + ": ");
            int size=que.size();
            while(size-- > 0){
                Node rnode=que.removeFirst();
                System.out.print(rnode.data + " ");
    
                for(Node child: rnode.children)
                   que.addLast(child);
            }
            level++;
            System.out.println();
        }
    }
    
    public static boolean isMirror(Node root1,Node root2)   //O(n)     
    {
        if(root1.children.size() != root2.children.size() || root1.data !=root2.data) return false;

        for(int i=0,j=root1.children.size()-1; j >=0; i++,j--)
        {
            Node first=root1.children.get(i);
            Node last=root2.children.get(j);
            if(!isMirror(first,last)) return false;
        }
    
        return true;
    }

    public static boolean isSymmetric(Node root1,Node root2)   //O(n)     
    {
        if(root1.children.size() != root2.children.size()) return false;

        for(int i=0,j=root1.children.size()-1; j >=0; i++,j--)
        {
            Node first=root1.children.get(i);
            Node last=root2.children.get(j);
            if(!isSymmetric(first,last)) return false;
        }
    
        return true;
    }
    
    public static Node linearize(Node node){
        if(node.children.size()==0) return node;
    
        int n=node.children.size();
        Node lastTail=linearize(node.children.get(n-1));
        for(int i = n-2;i>=0;i--){
            Node secondLastTail=linearize(node.children.get(i));
            
            secondLastTail.children.add(node.children.get(i+1));  // connection between two linearize structure.
            
            node.children.remove(node.children.size()-1); //remove last node.
        }
    
        return lastTail;
    }
    
    public static void flattern(Node node){
        ArrayList<Node> nchilds=new ArrayList<>();
        
        for(Node child: node.children){
            flattern(child);
    
            nchilds.add(child);
            for(Node ch: child.children){
              nchilds.add(ch);
            }
            child.children.clear();
        }
    
        node.children.clear();
        node.children=nchilds;
    }

    static int diam = 0;     
    public static int diameter(Node root)
    {
        if(root.children.size() == 0)  return 1;

        int h=0, max1 = 0, max2 = 0;
        for(Node child:root.children)
        {
            h = diameter(child);
            if(h>max1)
            {
                max2 = max1;
                max1 = h;
            }
            else if(h>max2)
                max2 = h;
        }
        diam = Math.max(diam,max1+max2+1);

        return max1+1;
    }

    public static void set1(Node root){
        // levelOrder(root);
        // linearize(root);
        // flattern(root);
        // display(root);
        diameter(root);
        System.out.println(diam);
    }
    
    public static void solve(){
        int[] arr={10, 20, 50, -1, 60, -1, -1, 30, 70, -1, 80, 100, -1, 110, -1, -1, 90, -1, -1, 40, 120, 140, -1, 150, -1, -1, -1,-1};
        Node root = construct(arr);
        display(root);

        // ceil(root,10);
        // floor(root,10);
        // System.out.println(ceil);
        // System.out.println(floor);
    
        set1(root);
    }
    

    public static void main(final String[] args)
    {
        solve();
    }
}