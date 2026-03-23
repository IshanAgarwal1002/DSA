import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Arrays;

public class tree{

    public static void main(String[] args){
        solve();
    }

   public static class Node{
       int data;  
       Node left=null;   // Node* left=nullptr;   
       Node right=null;  // Node* right=nullptr;

       Node(int data){
           this.data=data;
       } 
       
       Node(){
       }
   }

   static int idx=0;
   public static Node constructTree(int[] arr){
      if(idx == arr.length || arr[idx]==-1) {
        idx++;  
        return null;
      }

      Node node=new Node(arr[idx++]);   // Node* node=new Node(arr[idx++]);
      node.left=constructTree(arr);
      node.right=constructTree(arr);
      
      return node;
   }

   public static void display(Node node){
       if(node==null) return;

       String str="";
       str += ((node.left!=null)?node.left.data:".");
       str+=  " <- " + node.data + " -> ";
       str += ((node.right!=null)?node.right.data:".");
       System.out.println(str);

       display(node.left);
       display(node.right);
   }

   //Basic.================================================================

   public static int size(Node node){
     if(node==null) return 0;
     return (size(node.left) + size(node.right) + 1);
   }

   
   public static int height(Node node){
    if(node==null) return -1; // return -1, height w.r.t edge, return 0, height w.r.t node.
    return Math.max(height(node.left), height(node.right)) + 1;
   }

   public static int Maximum(Node node){
    if(node==null) return (int)-1e8;  // java: Integer.MIN_VALUE, c++: INT_MIN; 
    return Math.max(Math.max(Maximum(node.left), Maximum(node.right)),node.data);  // max(leftSubtree,rightSubtree,myself);
   }

   
   public static int Minimum(Node node){
    if(node==null) return (int)1e8;  // java: Integer.MAX_VALUE, c++: INT_MAX; 
    return Math.min(Math.min(Minimum(node.left), Minimum(node.right)),node.data);
   }

   public static int Minimum_02(Node node){
       int min_=node.data;
       
       if(node.left!=null) min_=Math.min(min_,Minimum_02(node.left));
       if(node.right!=null) min_=Math.min(min_,Minimum_02(node.right));
       
       return min_;
   }

   public static boolean find(Node node,int data){
       if(node==null) return false;
       
       if(node.data==data) return true;
       return find(node.left,data) || find(node.right,data);   

        // if(find(node.left,data)) return true;
        // if(find(node.rigth,data)) return true;
    }

   //Traversal.============================================================

    public static void preOrder(Node node){
         if(node==null) return;

         System.out.print(node.data+ " ");
         preOrder(node.left);
         preOrder(node.right);
    }

    
    public static void inOrder(Node node){
        if(node==null) return;

        inOrder(node.left);
        System.out.print(node.data+ " ");
        inOrder(node.right);
   }

   public static void postOrder(Node node){
    if(node==null) return;

    postOrder(node.left);
    postOrder(node.right);
    System.out.print(node.data+ " ");
   
    }

    //root to node path......................................................
    public static boolean rootToNodePath_(Node root,int data,ArrayList<Node> path){
      if(root==null) return false;
      if(root.data==data){
          path.add(root);
          return true;
      }

      boolean res = rootToNodePath_(root.left,data,path) || rootToNodePath_(root.right,data,path);
     if(res) path.add(root);
      return res;
    }

    public static ArrayList<Node> rootToNodePath_02(Node root,int data){
        
        if(root==null){
            return new ArrayList<>();
        }
        
        if(root.data==data){
            ArrayList<Node> base=new ArrayList<>();
            base.add(root);
            return base;
        }
  
        ArrayList<Node> left=rootToNodePath_02(root.left,data);
        if(left.size()!=0){
            left.add(root);
            return left;
        }
   
        ArrayList<Node> right=rootToNodePath_02(root.right,data);
        if(right.size()!=0){
            right.add(root);
            return right;
        }
        
        return new ArrayList<>();
      }

    public static void rootToNodePath(Node root,int data){
        ArrayList<Node> path=new ArrayList<>();
        rootToNodePath_(root,data,path);
        for(Node n: path){
            System.out.print(n.data + " -> ");
        }
    }

    public Node lowestCommonAncestor(Node root, int p, int q) {
        ArrayList<Node> path1=new ArrayList<>();
        ArrayList<Node> path2=new ArrayList<>();
        
        rootToNodePath_(root,p,path1);
        rootToNodePath_(root,q,path2);

        Node prev=null;
        int i=path1.size()-1;
        int j=path2.size()-1;
        
        while(i>=0 && j>=0){
          if(path1.get(i).data!=path2.get(j).data) break;
          
          prev=path1.get(i);
          i--;
          j--;
        }

        return prev;
    } 

    static Node LCANode=null;
    public static boolean lowestCommonAncestor_02(Node root, int p, int q) {
        if(root==null) return false;
        
        boolean selfDone=false;
        if(root.data==p || root.data==q){
            selfDone=true;
        }

        boolean leftDone=lowestCommonAncestor_02(root.left,p,q);
        if(LCANode!=null) return true;

        boolean rightDone=lowestCommonAncestor_02(root.right,p,q);
        if(LCANode!=null) return true;
        
        if((selfDone && leftDone) || (selfDone && rightDone) || (leftDone && rightDone))
          LCANode=root;


        return selfDone || leftDone || rightDone; 
    }

    public static void kDown(Node root,int level,Node blockNode){
       if(root==null || root==blockNode) return;

       if(level==0){
         System.out.print(root.data + " ");
         return;  
       }

       kDown(root.left,level-1,blockNode);
       kDown(root.right,level-1,blockNode);

    }

    public static void allNodeKAway(Node root, int target, int K) {
        ArrayList<Node> path=new ArrayList<>();
        rootToNodePath_(root,target,path);

        Node blockNode=null;
        for(int i=0;i<path.size();i++){
            if(K-i<0) break;
            kDown(path.get(i),K-i,blockNode);
            blockNode=path.get(i);
        }
    }
    
    public static int allNodeKAway_02_(Node root, int target, int K) {
         if(root==null) return -1;

         if(root.data == target){
            kDown(root,K,null);
            return 1;
         }

         int leftdistance=allNodeKAway_02_(root.left,target,K);
         if(leftdistance!=-1){
            if(K-leftdistance >= 0) kDown(root,K-leftdistance,root.left);
            return leftdistance+1;
         }
         
         int rightdistance=allNodeKAway_02_(root.right,target,K);
          if(rightdistance!=-1){
            if(K-rightdistance >= 0) kDown(root,K-rightdistance,root.right);
            return rightdistance+1;
        }

        return -1;
    
    }

    public static void kDown(Node root,int level){
        if(root==null) return;
 
        if(level==0){
          System.out.print(root.data + " ");
          return;  
        }
 
        kDown(root.left,level-1);
        kDown(root.right,level-1);
 
     }

    public static int allNodeKAway_03_(Node root, int target, int K) {
        if(root==null) return -1;

        if(root.data == target){
           kDown(root,K);
           return 1;
        }

        int leftdistance=allNodeKAway_03_(root.left,target,K);
        if(leftdistance!=-1){
           if(K-leftdistance == 0)  
              System.out.print(root.data + " ");
           else
              kDown(root.right,K-leftdistance-1);
           return leftdistance+1;
        }
        
        int rightdistance=allNodeKAway_03_(root.right,target,K);
        if(rightdistance!=-1){
            if(K-rightdistance == 0)
               System.out.print(root.data + " ");
            else
               kDown(root.left,K-rightdistance-1);
            return rightdistance+1;
         }

       return -1;
   
    }

    public static int diameter_01(Node node){
       if(node==null) return 0;

       int ld=diameter_01(node.left);
       int rd=diameter_01(node.right);

       int lh=height(node.left);
       int rh=height(node.right);

       int myDia = lh + rh + 2;
       return Math.max(Math.max(ld,rd), myDia);
    }

    public static class diaPair{
       int dia=0;
       int hei=0;

       diaPair(int dia,int hei){
           this.dia=dia;
           this.hei=hei;
       }
    }

    public static diaPair diameter_02(Node node){
        if(node==null) return new diaPair(0,-1) ;

        diaPair lr=diameter_02(node.left); // left result
        diaPair rr=diameter_02(node.right); // right result

        diaPair myRes=new diaPair(0,-1);
        myRes.dia = Math.max(Math.max(lr.dia,rr.dia), (lr.hei+rr.hei+2));
        myRes.hei = Math.max(lr.hei,rr.hei)+1;
    
        return myRes;
    }

    static int diameter=0;
    public static int diameter_03(Node node){
        if(node==null) return -1 ;

        int lh = diameter_03(node.left); // left height
        int rh =diameter_03(node.right); // right height
    
        diameter=Math.max(diameter,lh+rh+2);
        return Math.max(lh,rh)+1;
    }
  
    public static void set1(Node node){
        //   rootToNodePath(node,100);
    
        //   lowestCommonAncestor_02(node,200,30);
        //   System.out.println("LCA: " + (LCANode!=null?LCANode.data:"-1"));
        // allNodeKAway(node,20,1);


        System.out.println(diameter_01(node));
        System.out.println(diameter_02(node).dia);
        diameter_03(node);
        System.out.println(diameter);

    }

    //level Order Series(BFS)========================================================    

    //prints all elements in a single line
    public static void levelOrder00(Node root){
        LinkedList<Node> Que = new LinkedList<>();
        Que.addLast(root);

        while(Que.size() != 0)
        {
            Node rNode = Que.removeFirst();
            System.out.print(rNode.data + " ");
            if(rNode.left != null)   Que.addLast(rNode.left);
            if(rNode.right != null)   Que.addLast(rNode.right);
        }
    }

    //prints level by level, uses 2 queue
    public static void levelOrder01(Node root){
        LinkedList<Node> pQue = new LinkedList<>();
        LinkedList<Node> cQue = new LinkedList<>();
        pQue.addLast(root);

        int count = 0;
        System.out.print("Level " + count + ": ");

        while(pQue.size() != 0)
        {
            Node rNode = pQue.removeFirst();
            System.out.print(rNode.data + " ");
            if(rNode.left != null)   cQue.addLast(rNode.left);
            if(rNode.right != null)   cQue.addLast(rNode.right);

            if(pQue.size() == 0){
                LinkedList<Node> temp = pQue;
                pQue = cQue;
                cQue = temp;
                count++;
                System.out.print("\nLevel " + count + ": ");
            }
        }
    }

    //prints level by level, uses delimiter method
    public static void levelOrder02(Node root){
        LinkedList<Node> Que = new LinkedList<>();
        Que.addLast(root);
        Que.addLast(null);

        int count = 0;
        System.out.print("Level " + count + ": ");

        while(Que.size() != 1)
        {
            Node rNode = Que.removeFirst();
            System.out.print(rNode.data + " ");
            if(rNode.left != null)   Que.addLast(rNode.left);
            if(rNode.right != null)   Que.addLast(rNode.right);

            if(Que.getFirst() == null){
                Que.removeFirst();
                Que.addLast(null);
                count++;
                System.out.print("\nLevel " + count + ": ");
            }
        }
    }

    //prints level by level, uses 2 while loops method
    public static void levelOrder03(Node root){
        LinkedList<Node> Que = new LinkedList<>();
        Que.addLast(root);

        int count = 0;
        
        while(Que.size() != 0)
        {
            System.out.print("Level " + count + ": ");
            int size = Que.size();
            while(size-- > 0)
            {
                Node rNode = Que.removeFirst();
                System.out.print(rNode.data + " ");
                if(rNode.left != null)   Que.addLast(rNode.left);
                if(rNode.right != null)   Que.addLast(rNode.right);
            }
            count++;
            System.out.println();
        }
    }

    public static void levelOrder(Node root){
        // levelOrder00(root);
        // levelOrder01(root);
        // levelOrder02(root);
        // levelOrder03(root);
    }

    //left View======================================================
    public static void leftView(Node root){
        LinkedList<Node> Que = new LinkedList<>();
        Que.addLast(root);
        
        while(Que.size() != 0)      //checks if there is a level or not
        {
            System.out.print(Que.getFirst().data + " ");
            int size = Que.size();
            while(size-- > 0)       //adds all elements of a level
            {
                Node rNode = Que.removeFirst();
                if(rNode.left != null)   Que.addLast(rNode.left);
                if(rNode.right != null)   Que.addLast(rNode.right);
            }
        }
        System.out.println();
    }

    //right View======================================================
    public static void rightView(Node root){
        LinkedList<Node> Que = new LinkedList<>();
        Que.addLast(root);

        while(Que.size() != 0)
        {
            System.out.print(Que.getLast().data + " ");
            int size = Que.size();
            while(size-- > 0)
            {
                Node rNode = Que.removeFirst();
                if(rNode.left != null)   Que.addLast(rNode.left);
                if(rNode.right != null)   Que.addLast(rNode.right);
            }
        }
        System.out.println();
    }

    //width of tree=================================================
    static int leftMinValue=0;
    static int rightMaxValue=0;
    public static void width(Node root,int lev){        //lev is vertical level
        if(root==null) return;

        leftMinValue=Math.min(leftMinValue,lev);
        rightMaxValue=Math.max(rightMaxValue,lev);
       
        width(root.left, lev - 1);
        width(root.right, lev + 1);
    } 

    public static class pairVO{
        Node node;  //actual Node
        int vl=0;  // vertical Level
        public pairVO(Node node,int vl){
            this.node=node;
            this.vl=vl;
        }
    }

    //prints all nodes of a tree in vertical order
    public static void verticalOrder(Node node){
        width(node,0);
        int n=rightMaxValue - leftMinValue + 1;
        ArrayList<ArrayList<Integer>> ans=new ArrayList<>(); // vector<vector<int>> (n,vector<int>());
        for(int i=0;i<n;i++)
            ans.add(new ArrayList<>());
      
        LinkedList<pairVO> que=new LinkedList<>();
        que.addLast(new pairVO(node,-leftMinValue));

        while(que.size()!=0){
            int size=que.size();
            while(size-- > 0){
                pairVO rpair=que.removeFirst();
                ans.get(rpair.vl).add(rpair.node.data);
                if(rpair.node.left!=null) que.addLast(new pairVO(rpair.node.left, rpair.vl - 1));
                if(rpair.node.right!=null) que.addLast(new pairVO(rpair.node.right,rpair.vl + 1));    
            }
        }

        for(ArrayList<Integer> ar: ans)
            System.out.println(ar);
    }

    public static void verticalOrderSum(Node node){
        width(node,0);
        int[] ans=new int[rightMaxValue - leftMinValue + 1];

        LinkedList<pairVO> que=new LinkedList<>();
        que.addLast(new pairVO(node,-leftMinValue));

        while(que.size()!=0){
            int size=que.size();
            while(size-- > 0){
                pairVO rpair=que.removeFirst();
                ans[rpair.vl] += rpair.node.data;
                if(rpair.node.left!=null) que.addLast(new pairVO(rpair.node.left, rpair.vl - 1));
                if(rpair.node.right!=null) que.addLast(new pairVO(rpair.node.right,rpair.vl + 1));    
            }
        }

        for(int ar: ans)
            System.out.print(ar + " ");
        System.out.println();
    }

    //bottom view of tree============================================
    public static void bottomView(Node root)
    {
        width(root,0);
        int[] ans = new int[rightMaxValue - leftMinValue + 1];

        LinkedList<pairVO> que = new LinkedList<>();
        que.addLast(new pairVO(root, -leftMinValue));

        while(que.size() != 0)
        {
            int size = que.size();
            while(size-- > 0)
            {
                pairVO rPair = que.removeFirst();
                ans[rPair.vl] = rPair.node.data;
                if(rPair.node.left != null) que.addLast(new pairVO(rPair.node.left, rPair.vl - 1));
                if(rPair.node.right != null) que.addLast(new pairVO(rPair.node.right, rPair.vl + 1));
            }
        }

        for(int i:ans)
            System.out.print(i + " ");
        System.out.println();
    }

    //top view of tree==========================
    public static void topView(Node root)
    {
        width(root,0);
        int[] ans = new int[rightMaxValue - leftMinValue + 1];
        Arrays.fill(ans,(int)-1e8);

        LinkedList<pairVO> que = new LinkedList<>();
        que.addLast(new pairVO(root, -leftMinValue));

        while(que.size() != 0)
        {
            int size = que.size();
            while(size-- > 0)
            {
                pairVO rPair = que.removeFirst();
                if(ans[rPair.vl] == (int)-1e8)
                    ans[rPair.vl] = rPair.node.data;
                if(rPair.node.left != null) que.addLast(new pairVO(rPair.node.left, rPair.vl - 1));
                if(rPair.node.right != null) que.addLast(new pairVO(rPair.node.right, rPair.vl + 1));
            }
        }

        for(int i:ans)
            System.out.print(i + " ");
        System.out.println();
    }

    //no. of diagonals in tree==================================
    public static void widthDiagonal(Node root,int lev)
    {
        if(root == null)    return;

        leftMinValue = Math.min(leftMinValue,lev);

        widthDiagonal(root.left, lev-1);
        widthDiagonal(root.right, lev+0);
    }

    //diagonal view=============================================
    public static void diagonalOrder(Node root)
    {
        widthDiagonal(root, 0);
        int n = -leftMinValue+1;
        ArrayList<ArrayList<Integer>> ans = new ArrayList<>();
        for(int i=0;i<n;i++)
            ans.add(new ArrayList<>());

        LinkedList<pairVO> que = new LinkedList<>();
        que.addLast(new pairVO(root, -leftMinValue));

        while(que.size() != 0)
        {
            int size = que.size();
            while(size-- > 0)
            {
                pairVO rPair = que.removeFirst();
                ans.get(rPair.vl).add(rPair.node.data);
                if(rPair.node.left != null) que.addLast(new pairVO(rPair.node.left, rPair.vl-1));
                if(rPair.node.right != null) que.addLast(new pairVO(rPair.node.right, rPair.vl+0));
            }
        }

        for(ArrayList<Integer> ar:ans)
            System.out.println(ar);
    }

    public static void diagonalSum(Node root)
    {
        widthDiagonal(root, 0);
        int[] ans = new int[-leftMinValue+1];

        LinkedList<pairVO> que = new LinkedList<>();
        que.addLast(new pairVO(root, -leftMinValue));

        while(que.size() != 0)
        {
            int size = que.size();
            while(size-- > 0)
            {
                pairVO rPair = que.removeFirst();
                ans[rPair.vl] += rPair.node.data;
                if(rPair.node.left != null) que.addLast(new pairVO(rPair.node.left, rPair.vl-1));
                if(rPair.node.right != null) que.addLast(new pairVO(rPair.node.right, rPair.vl+0));
            }
        }

        for(int i:ans)
            System.out.print(i + " ");
    }

    public static void view(Node root)
    {
        System.out.print("Left View: ");
        leftView(root);
        System.out.print("Right View: ");
        rightView(root);
        System.out.print("Vertical Order:\n");
        verticalOrder(root);
        System.out.print("Vertical Order Sum:");
        verticalOrderSum(root);
        System.out.print("Bottom View: ");
        bottomView(root);
        System.out.print("Top View: ");
        topView(root);
        System.out.print("Diagonal View:\n");
        diagonalOrder(root);
        System.out.print("Diagonal Order Sum:");
        diagonalSum(root);
    }

    //tree to doubly linked list
    static Node DLLhead=null;
    static Node DLLprev=null;

    public static void DLL(Node node){
        if(node==null) return;
     
        DLL(node.left);
     
        if(DLLhead==null){
            DLLhead=node;
        }else{
            DLLprev.right=node;
            node.left=DLLprev;
        }
        DLLprev=node;

        DLL(node.right);
    }
    
    public static class allSolution{
        int height = 0;
        int size=0;
        boolean find=false;
 
        Node pred=null;
        Node succ=null;
        Node prev=null;
    }
 
    public static void allSol(Node node,int data,int level,allSolution pair){
     if(node==null) return;
     pair.size++;
     pair.height=Math.max(pair.height,level);
     pair.find= pair.find || node.data==data;
     
     if(node.data==data && pair.pred==null) pair.pred=prev;
     if(pair.prev!=null && pair.prev.data == data && pair.succ==null) pair.succ=node;
     pair.prev=node;
     
      allSol(node.left,data,level+1,pair);
      allSol(node.right,data,level+1,pair);
    }
 

    public static void set2(Node root){
        
        
    
        
    }

    public static void solve(){
        int[] arr={10,20,40,-1,-1,50,80,-1,-1,90,-1,-1,30,60,100,-1,-1,-1,70,110,-1,-1,120,-1,-1};
        // int[] arr={10,20};
        Node root=constructTree(arr);
        display(root);
        // set1(root);
        // levelOrder(root);
        // view(root);
        set2(root);
    }
}