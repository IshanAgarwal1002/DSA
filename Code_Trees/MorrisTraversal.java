import java.util.Stack;
public class MorrisTraversal{

    public static void main(String[] args)
    {
        
    }

    public static class Node {
        int data;
        Node left = null; // Node* left=nullptr;   
        Node right = null; // Node* right=nullptr;

        Node() {}
        Node(int data) {
            this.data = data;
        }
    }

    public static class tpair{         //traversal pair
        Node node;
        boolean selfDone = false;
        boolean leftDone = false;
        boolean rightDone = false;

        tpair(Node node,boolean selfDone,boolean leftDone,boolean rightDone){
            this.node=node;
            this.leftDone=leftDone;
            this.selfDone=selfDone; 
            this.rightDone=rightDone;
        }
    }

    public static void ItrTraversalOfTree(Node node){
        Stack<tpair> st=new Stack<>();
        st.push(new tpair(node,false,false,false));
        
        while(st.size()!=0){                        //preoderder tarversal (for inorder swap if and first else if statements)
            if(st.peek().selfDone==false){
                st.peek().selfDone = true;
                System.out.print(st.peek().node.data+" ");
            }else if(st.peek().leftDone==false){
                st.peek().leftDone = true;
                if(st.peek().node.left!=null){
                    st.push(new tpair(st.peek().node.left,false,false,false));
                }
            }else if(st.peek().rightDone==false){
                st.peek().rightDone = true;
                if(st.peek().node.right!=null){
                    st.push(new tpair(st.peek().node.right,false,false,false));
                }
            }else {
                st.pop();
            }
        }
    }

    public static class tpair_{  //traversalPair
        Node node=null;
        boolean selfDone=false;
        boolean leftDone=false;
        boolean rightDone=false;
        
        int ld = -1;
        int rd = -1;
        int sd = -1;
        boolean isleft=false;

        tpair_(Node node,boolean selfDone,boolean leftDone,boolean rightDone,boolean isleft){
            this.node=node;
            this.leftDone=leftDone;
            this.selfDone=selfDone; 
            this.rightDone=rightDone;
            this.isleft=isleft;
        }
    }

    public static void ItrHeightOfTree(Node node){
        Stack<tpair_> st=new Stack<>();
        st.push(new tpair_(node,false,false,false,false));
        
        tpair_ rpair=null;
        while(st.size()!=0){
            if(st.peek().leftDone==false){
                st.peek().leftDone = true;
                if(st.peek().node.left!=null){
                    st.push(new tpair_(st.peek().node.left,false,false,false,true));
                }
            }else if(st.peek().rightDone==false){
                st.peek().rightDone = true;
                if(st.peek().node.right!=null){
                    st.push(new tpair_(st.peek().node.right,false,false,false,false));
                }
            }else if(st.peek().selfDone==false){
                st.peek().selfDone = true;
                st.peek().sd=Math.max(st.peek().ld,st.peek().rd)+1;
            }else {
                rpair=st.pop();
                if(st.size()!=0){
                    if(st.peek().isleft)
                        st.peek().ld=rpair.sd;
                    else 
                       st.peek().rd=rpair.sd;
                }
            }
        }

        System.out.println(rpair.sd);
    }

    public static Node rightMost_of_LeftNode(Node lnode,Node curr){
        while(lnode.right!=null && lnode.right!=curr){
            lnode=lnode.right;
        }
        return lnode;
    }

    public static void morrisInOrder(Node node){
        Node curr=node;
        while(curr!=null){
            if(curr.left==null){
                System.out.print(curr.data+" ");
                curr=curr.right;
            }else{
                Node leftNode=curr.left;
                Node rightMost=rightMost_of_LeftNode(leftNode,curr);
                if(rightMost.right==null){ // thread create
                   rightMost.right=curr;
                   curr=curr.left;
                }else{ // thread break
                    rightMost.right=null;
                    System.out.print(curr.data+" ");
                    curr=curr.right;
                }
            }
        }
        System.out.println();
    }

    public static void morrisPreOrder(Node node){
        Node curr=node;
        while(curr!=null){
            if(curr.left==null){
                System.out.print(curr.data+" ");
                curr=curr.right;
            }else{
                Node leftNode=curr.left;
                Node rightMost=rightMost_of_LeftNode(leftNode,curr);
                if(rightMost.right==null){ // thread create
                   rightMost.right=curr;
                   System.out.print(curr.data+" ");
                   curr=curr.left;
                }else{ // thread break
                    rightMost.right=null;
                    curr=curr.right;
                }
            }
        }
        System.out.println();
    }
    
    //Leetcode 105: construct-binary-tree-from-preorder-and-inorder-traversal.========================

    // psi = preStartIndex, pei=preEndIndex, isi=inStartIndex, iei=inEndIndex
    public TreeNode ConstructFromPreAndIn(int[] pre, int psi, int pei, int[] in , int isi, int iei) {
        if (psi > pei || isi > iei) return null;

        TreeNode node = new TreeNode(pre[psi]);

        int idx = isi;
        while ( in [idx] != pre[psi]) {
            idx++;
        }
        int tnel = idx - isi; // total no of elements between isi and idx

        node.left = ConstructFromPreAndIn(pre, psi + 1, psi + tnel, in , isi, idx - 1);
        node.right = ConstructFromPreAndIn(pre, psi + tnel + 1, pei, in , idx + 1, iei);

        return node;
    }

    public TreeNode buildTree(int[] pre, int[] in ) {
        return ConstructFromPreAndIn(pre, 0, pre.length - 1, in , 0, in .length - 1);
    }

    //Leetcode 106 : construct-binary-tree-from-inorder-and-postorder-traversal.
    // psi = postStartIndex, pei=postEndIndex, isi=inStartIndex, iei=inEndIndex
    public TreeNode ConstructFromPostAndIn(int[] post, int psi, int pei, int[] in , int isi, int iei) {
        if (psi > pei || isi > iei) return null;

        TreeNode node = new TreeNode(post[pei]);

        int idx = isi;
        while ( in [idx] != post[pei]) {
            idx++;
        }
        int tnel = idx - isi; // total no of elements between isi and idx

        node.left = ConstructFromPostAndIn(post, psi, psi + tnel - 1, in , isi, idx - 1);
        node.right = ConstructFromPostAndIn(post, psi + tnel, pei - 1, in , idx + 1, iei);

        return node;
    }

    public TreeNode buildTree(int[] in , int[] post) {
        return ConstructFromPostAndIn(post, 0, post.length - 1, in , 0, in .length - 1);
    }

    // Leetcode 889: construct-binary-tree-from-preorder-and-postorder-traversal
    // psi = preStartIndex, pei=preEndIndex, ppsi=postStartIndex, ppei=postEndIndex
    public TreeNode ConstructFromPreAndPost(int[] pre, int psi, int pei, int[] post, int ppsi, int ppei) {
        if (psi > pei || ppsi > ppei) return null;

        if (ppsi == ppei) {
            return new TreeNode(post[ppsi]);
        }

        TreeNode node = new TreeNode(pre[psi]);

        int idx = ppsi;
        while (post[idx] != pre[psi + 1]) {
            idx++;
        }

        int tnel = idx - ppsi + 1; // total no of elements between isi and idx

        node.left = ConstructFromPreAndPost(pre, psi + 1, psi + tnel, post, ppsi, idx);
        node.right = ConstructFromPreAndPost(pre, psi + tnel + 1, pei, post, idx + 1, ppei - 1);

        return node;
    }

    public TreeNode constructFromPrePost(int[] pre, int[] post) {
        return ConstructFromPreAndPost(pre, 0, pre.length - 1, post, 0, post.length - 1);
    }
  



    public static void set2(Node node) {

        // ItrHeightOfTree(node);
        morrisInOrder(node);
        morrisPreOrder(node);
    }
}