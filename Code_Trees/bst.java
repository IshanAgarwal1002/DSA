public class bst {
    
    public static void main(String[] args)
    {

    }

    class Node{
        int data;
        Node left;
        Node right;

        Node(){}

        Node(int data)
        {
            this.data = data;
            left = null;
            right = null;
        }
    };

    public static Node construct(int[] arr,int si, int ei)
    {
        if(si > ei) return null;

        mid = (si+ei)>>1;

        Node root = new Node(arr[mid]);
        root.left = construct(arr, si, mid-1);
        root.right = construct(arr, mid+1, ei);

        return root;
    }

    public static void display(Node root)
    {
        if(root == null)    return;

        if(root.left != null)   System.out.print(root.left + " -> ");
        else System.out.print(". -> ");
        System.out.print(root);
        if(root.right != null)   System.out.print(" <- " + root.right);
        else System.out.print("<- .");

        display(root.left);
        display(root.right);
    }

    //basic------------------------------------------------------------
    public static int height(Node root)
    {
        if(root==null)  return -1;
        return Math.max(height(root.left),height(root.right)) + 1;
    }

    public static int size(Node root)
    {
        if(root==null)  return 0;
        return size(root.left) + size(root.right) + 1;
    }

    public static boolean find(Node root, int data)
    {
        Node curr = root;
        while(curr != null)
        {
            if(data == curr.data)   return true;
            else if(data > curr.data)    curr = curr.right;
            else   curr = curr.left;
        }
        return false;
    }

    public static boolean findRec(Node root, int data)
    {
        if(root == null) return false;
        
        if(data == root.data)   return true;
        else if(data > root.data)    return findRec(root.right,data);
        else   return findRec(root.left,data);
    }

    public static Node maximum(Node root)
    {
        if(root == null)    return null;

        Node curr = root;
        while(curr.right!=null)
            curr = curr.right;
        
        return curr;
    }

    public static Node minimum(Node root)
    {
        if(root == null)    return null;

        Node curr = root;
        while(curr.left!=null)
            curr = curr.left;
        
        return curr;
    }

    //LCA================================
    public static Node LCA(Node root, int p, int q)     //p < q
    {
        if(root == null)    return null;

        Node curr = root;
        while(curr != null)
        {
            if(q < curr.data)     curr = curr.left;
            else if(p > curr.data)    curr = curr.right;
            else    return (find(curr,p) && find(curr,q))?curr:null;
        }
        return null;
    }

    public static int LCAoFBST_Rec(Node root, int a, int b) // a<b
    {
        if (root == null)
            return -1;

        if (b < root.data)
            return LCAoFBST_Rec(root.left, a, b);
        else if (a > root.data)
            return LCAoFBST_Rec(root.right, a, b);
        else
            return (find(root,p) && find(root,q))?root:null; //LCA point.
    }

    //in order
    static ArrayList<Integer> ans;
    public static void allNodeInRange_01(Node root,int a,int b)     // a < b
    {
        if(root == null)    return;

        allNodeInRange_01(root.left, a, b);
        if(root.data >= a && b <= root.data)  ans.add(root.data);
        allNodeInRange_01(root.right, a, b);
    }

    //pre order
    public static void allNodeInRange_02(Node root,int a,int b)     // a < b
    {
        if(root == null)    return;

        if(root.data >= a && b <= root.data)  
            ans.add(root.data);

        if (a > root.data)          allNodeInRange_02(root.right, a, b);
        else if (b < root.data)     allNodeInRange_02(root.left, a, b);
        else{
            allNodeInRange_02(root.right, a, b);
            allNodeInRange_02(root.left, a, b);
        }
    }

    //predecessor and successor in a binary search tree
    public static void predAndSucc_InOrder(Node root, int data)
    {
        Node curr = root;
        Node pred = null;
        Node succ = null;
        while(curr != null)
        {
            if(curr.data == data)
            {
                if(curr.left == null)
                    System.out.println("Pred: " + (pred != null)?pred.data:"null");
                else{
                    pred = curr.left;
                    while(pred.right != null)   pred = pred.right;
                    System.out.println("Pred: " + pred.data);
                }

                if(curr.right == null)
                    System.out.println("Succ: " + (succ != null)?succ.data:"null");
                else{
                    succ = curr.right;
                    while(succ.left != null)   succ = succ.left;
                    System.out.println("Succ: " + succ.data);
                }

                break;
            }
            else if(data < curr.data)
            {
                succ = curr;
                curr = curr.left;
            }
            else{
                pred = curr;
                curr = curr.right;
            }
        }
    }

    static int idx = 0;
    public static Node constructTreeFromPreOrder(int[] arr,int lb, int rb)
    {
        if(idx == arr.length || arr[idx] < lb || arr[idx] > rb)
            return null;

        Node root = new Node(arr[idx++]);
        root.left = constructTreeFromPreOrder(arr, lb, root.data);
        root.right = constructTreeFromPreOrder(arr, root.data, rb);

        return root;
    }

    public static int heightOfBSTFromPreOrder(int[] arr, int lb, int rb)
    {
        if(idx == arr.length || arr[idx] < lb || arr[idx] > rb)
            return -1;

        int ele = arr[idx++];

        int lh = heightOfBSTFromPreOrder(arr, lb, ele);
        int rh = heightOfBSTFromPreOrder(arr, ele, rb);

        return Math.max(lh,rh) + 1;
    }

    public static Node addData(Node root, int data)
    {
        if(root == null)
            return new Node(data);
        if(data < root.data) 
            root.left = addData(root.left,data);
        else
            root.right = addData(root.right,data);

        return root;
    }

    public static Node removeData(Node root, int data)
    {
        if(root == null)    return null;    //never found data

        if(root.data == data)
        {
            if(root.left == null || root.right == null)
                return (root.left != null)?root.left:root.right;

            Node maxInLeft = maximum(root.left);
            root.data = maxInLeft.data;
            root.left = removeData(root.left, maxInLeft.data);
        }
        else if(data < root.data)
            root.left = removeData(root.left, data);
        else
            root.right = removeData(root.right, data);
        
        return root;
    }
}