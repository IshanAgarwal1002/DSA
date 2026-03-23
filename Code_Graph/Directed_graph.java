import java.util.ArrayList;
import java.util.LinkedList;

public class Directed_graph {

    public static void main(String[] args){
        solve();

    }

    static int N = 7;
    public static ArrayList<Integer>[] graph;

    public static void constructGraph(){
        graph = new ArrayList[N];
        for(int i=0;i<N;i++)
        {
            graph[i] = new ArrayList<Integer>();
        }

        graph[0].add(1);
        graph[0].add(2);
        graph[1].add(4);
        graph[1].add(6);
        graph[2].add(5);
        graph[3].add(0);
        graph[3].add(1);
        graph[3].add(2);
        graph[3].add(5);
        graph[3].add(6);
        graph[6].add(4);
        graph[6].add(5);

        display();
    }

    public static void display(){
        for(int i=0;i<N;i++)
        {
            System.out.print(i + " -> ");
            for(Integer e:graph[i])
            {
                System.out.print(e + " ");
            }
            System.out.println();
        }
        System.out.println();
    }

    public static void tSortDFS(int src,boolean[] vis,ArrayList<Integer> ans){
        
        vis[src] = true;
        for(Integer e:graph[src])
        {
            if(!vis[e])
                tSortDFS(e,vis,ans);
        }
        ans.add(src);
    }

    public static void tSort(boolean[] vis){       //topologicalSort function

        ArrayList<Integer> ans = new ArrayList<>();
        for(int i=0;i<N;i++)
        {
            if(!vis[i]){
                tSortDFS(i,vis,ans);
            }
        }
        for(int i=ans.size()-1;i>=0;i--) 
            System.out.print(ans.get(i)+ " ");
    }   

    public static void KahnsAlgo(){
        int[] indegree=new int[N];
        for(int i=0;i<N;i++){
            for(Integer e: graph[i])
               indegree[e]++;
        }

        LinkedList<Integer> que=new LinkedList<>();
        for(int i=0;i<N;i++){
            if(indegree[i]==0) que.addLast(i);
        }

        ArrayList<Integer> ans=new ArrayList<>();

        while(que.size()!=0){
            int size=que.size();
            while(size--> 0){
                int rvtx=que.removeFirst();
                ans.add(rvtx);
      
                for(int e: graph[rvtx]){
                    if(--indegree[e]==0)
                       que.addLast(e);
                }
            }
        }

        if(ans.size()!=N) System.out.println("Cycle");
        else System.out.println(ans);
    }

    
    public static boolean topologiaclSortCycle_(int src,int[] vis,ArrayList<Integer> ans){ // faith: it will detect cycle.
        if(vis[src]==1) return true; //cycle.
        if(vis[src]==2) return false;// already visited vertex.

        vis[src]=1;
        boolean res=false;
        for(int e:graph[src])
            res=res || topologiaclSortCycle_(e,vis,ans);

        vis[src]=2;
        ans.add(src);
        return res;
    }

    public static void topologiaclSortCycle(){
        int[] vis=new int[N];
        ArrayList<Integer> ans=new ArrayList<>();
        
        boolean res=false;
        for(int i=0;i<N && !res;i++){
            if(vis[i]==0)
            res=res||topologiaclSortCycle_(i,vis,ans);
        }
        
        if(!res)
           for(int i=ans.size()-1;i>=0;i--) 
              System.out.print(ans.get(i)+ " ");
        else 
           System.out.print("Cycle");
    }

    public static void solve(){
        constructGraph();

        boolean[] vis = new boolean[N];
        tSort(vis);
    }

    //leetcode 329
    public static int longestIncreasingPath(int[][] matrix) {
        int m = matrix.length;
        int n = matrix[0].length;

        int[][] dir = {{-1,0},{0,1},{1,0},{0,-1}};
        int[][] indegree = new int[m][n];
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                for(int k=0;k<4;k++)
                {
                    int r = i + dir[k][0];
                    int c = j + dir[k][1];
                    if(r>=0 && c>=0 && r<m && c<n && matrix[r][c]>matrix[i][j]){
                        ingdegree[r][c]++;
                    }
                }
            }
        }

        LinkedList<Integer> que=new LinkedList<>();
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(indegree[i][j]==0)  
                    que.addLast(i*m + j);
            }
        }

        while(que.size()!=0){
            int size = que.size();
            while(size--)
            {
                
            }
        }
    }
}