public class avl{

    public static class Node{

        int data;
        Node left = null;
        Node right = null;

        int bal = 0;
        int height = 0;

        Node(int data)
        {
            this.data = data;
        }
    }

    public static void UpdateHeightAndBalance(Node node)
    {
        int lh = -1;
        int rh = -1;

        if(node.left != null)   lh = node.left.height;
        if(node.right != null)   rh = node.right.height;

        node.height = Math.max(lh,rh) + 1;
        node.bal = lh - rh;
    }

    //ll structure, right rotation
    public static Node ll(Node A)
    {
        Node B = A.left;
        Node BKaRight = B.right;

        B.right = A;
        A.left = BKaRight;

        UpdateHeightAndBalance(A);
        UpdateHeightAndBalance(B);

        return B;
    }

    //rr structure, left rotation
    public static Node rr(Node A)
    {
        Node B = A.right;
        Node BKaLeft = B.left;

        B.left = A;
        A.right = BKaLeft;

        UpdateHeightAndBalance(A);
        UpdateHeightAndBalance(B);

        return B;
    }

    //get rotation
    public static Node getRotation(Node node)
    {
        UpdateHeightAndBalance(node);
        if(node.bal == 2)           //ll or lr structure
        {
            if(node.left.bal== 1)   //ll
                return ll(node);
            else                    //lr
            {
                node.left = rr(node.left);
                return ll(node);
            }
        }
        else if(node.bal == -2)     //rr or rl structure
        {
            if(node.right.bal== -1)   //rr
                return rr(node);
            else                    //rl
            {
                node.right = ll(node.right);
                return rr(node);
            }
        }
        return node;
    }

    //BST====================================================

    public static Node construct(int[] arr,int si,int ei)
    {
        if(si>ei)   return null;

        int mid = (si+ei)>>1;   //(si+ei)/2

        Node root = new Node(arr[mid]);
        root.left = construct(arr, si, mid-1);
        root.right = construct(arr, mid+1, ei);

        UpdateHeightAndBalance(root);
        return root;
    }

    public static void display(Node root)
    {
        if(root == null)    return;

        if(root.left != null)   System.out.print(root.left.data + "[" + root.left.bal + "," + root.left.height + "]");
        else    System.out.print(".");

        System.out.print(" -> " + root.data + " <- ");

        if(root.right != null)   System.out.print(root.right.data + "[" + root.right.bal + "," + root.right.height + "]");
        else    System.out.print(".");

        System.out.print("\n");

        display(root.left);
        display(root.right);
    }

    public static Node addData(Node root, int data)
    {
        if(root==null)
            return new Node(data);

        if(data > root.data)    
            root.right = addData(root.right, data);
        else       
            root.left = addData(root.left, data);

        return getRotation(root);
    }

    public static int maximum(Node root)
    {
        Node curr = root;
        while(curr.right != null)
        {
            curr = curr.right;
        }
        return curr.data;
    }

    public static Node removeData(Node root, int data)
    {
        if(root == null)    return null;

        if(root.data == data){

            if(root.left == null || root.right == null)
                return (root.left!=null)?root.left:root.right;
            
            int maxInLeft = maximum(root.left);
            root.data = maxInLeft;
            root.left = removeData(root.left, maxInLeft);

        }else if(data < root.data){
            root.left = removeData(root.left, data);
        }else{
            root.right = removeData(root.right, data);
        }

        return getRotation(root);
    }

    public static void solve()
    {
        int[] arr = {100, 40, 20, 70, 30, 80, 10, 60, 90, 50, 130, 120, 110};
        // Node root = constructBST(arr, 0, arr.length - 1);

        Node root = null;
        for (int i = 0; i < arr.length; i++)
        {
            root = addData(root, arr[i]);
            display(root);
            System.out.print("\n\n\n");
        }

        display(root);
    }
    
    public static void main(String[] args)
    {
        solve();
    }


}