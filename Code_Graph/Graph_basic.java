import java.util.ArrayList;

public class Graph_basic{

    public static void main(String [] args){
        solve();
        solve2();
    }

    public static class Edge{
        int v;
        int w;

        Edge(int v,int w){
            this.v = v;
            this.w = w;
        }
    }

    public static int N = 7;
    public static ArrayList<Edge>[] graph;

    public static void addEdge(ArrayList<Edge>[] gp,int u,int v,int w){
        gp[u].add(new Edge(v,w));
        gp[v].add(new Edge(u,w));
    }

    public static void display(ArrayList<Edge>[] gp){
        for(int i=0;i<gp.length;i++)
        {
            System.out.print(i + " -> ");
            for(Edge j:gp[i])
                System.out.print("(" + j.v + ", " + j.w + ") ");
            System.out.println();
        }
        System.out.println();
    }

    public static int findEdge(int u,int v)
    {
        int vtx = -1;
        for(int i=0;i<graph[u].length;i++)
        {
            if(graph[u].get(i).v==v)
            {
                vtx = i;
                break;
            }
        }
        return vtx;
    }

    public static void removeEdge(int u,int v){
        int idx1 = findEdge(u, v);
        int idx2 = findEdge(v, u);

        graph[u].remove(idx1);
        graph[v].remove(idx2);
    }

    public static void removeVertex(int u){
        while(graph[u].size() != 0)
        {
            Edge e = graph[u].get(0);
            removeEdge(u,e.v);
        }
    }

    public static void constructGraph(){
        graph = new ArrayList[N];
        for (int i = 0; i < N; i++) {
			graph[i] = new ArrayList < Edge > ();
		}

        addEdge(graph, 0, 1, 10);
        addEdge(graph, 0, 3, 10);
        addEdge(graph, 1, 2, 10);
        addEdge(graph, 2, 3, 40);
        addEdge(graph, 3, 4, 2);
        addEdge(graph, 4, 5, 2);
        addEdge(graph, 4, 6, 3);
        addEdge(graph, 5, 6, 8);
        addEdge(graph, 2, 5, 4);

        display(graph);

    }

    public static void solve(){
        constructGraph();

        // removeVertex(3);

        // display(graph);
    }

//Question=================================================

//determine if there is a continuous path between given source and destination

    public static boolean hasPath(int src,int dest,boolean[] vis)
    {
        if(src==dest)
            return true;

        vis[src] = true;
        boolean res = false;
        for(Edge e:graph[src])
        {
            if(!vis[e.v])
                res = res || hasPath(e.v, dest, vis);
        }

        return res;
    }

    public static int allPath(int src,int dest,boolean[] vis, int w,String ans)
    {
        if(src==dest)
        {
            System.out.println(ans + dest + "@" + w);
            return 1;
        }

        vis[src] = true;
        int count = 0;
        for(Edge e:graph[src]){
            if(vis[e.v]==false)
            {
                count += allPath(e.v, dest, vis, w+e.w, ans+ src + " ");
            }
        }
        vis[src] = false;

        return count;
    }

    public static class allSolutionPair
    {
        int lightW = 1000;
        int heavyW = 0;
        int ceil = 1000;
        int floor = 0;
    };

    public static void allSolution(int src, int dest, boolean[] vis, int w,String ans,allSolutionPair pair, int data){
        if (src == dest)
        {
            pair.heavyW = Math.max(pair.heavyW, w);
            pair.lightW = Math.min(pair.lightW, w);

            if (w > data)
                pair.ceil = Math.min(pair.ceil, w);
            if (w < data)
                pair.floor = Math.max(pair.floor, w);
            return;
        }

        vis[src] = true;

        for (Edge e : graph[src])
        {
            if (!vis[e.v])
                allSolution(e.v, dest, vis, w + e.w, ans + src + " ", pair,data);
        }

        vis[src] = false;
    }

    public static void hamiltonianPath(int src,int osrc,boolean[] vis,int count,String ans){
        if(count == N-1){

            int idx = findEdge(src, osrc);
            if(idx == -1)
                System.out.println("Path: " + ans + src);
            else
                System.out.println("Cycle: " + ans + src);

            return;
        }
        vis[src] = true;
        for(Edge e:graph[src])
        {
            if(vis[e.v] == false)
            {
                hamiltonianPath(e.v, osrc, vis, count+1, ans+src+" ");
            }
        }
        vis[src] = false;
    }

    public static void solve2(){
        boolean[] vis  = new boolean[N];

        // System.out.print(allPath(0, 6, vis, 0, ""));
        // allSolutionPair pair = new allSolutionPair();
        // allSolution(0, 6, vis, 0, "", pair, 30);
        // System.out.print(pair.heavyW + " -> " + pair.lightW + " -> " + pair.ceil + " -> " + pair.floor);

        hamiltonianPath(2,2,vis,0,"");
    }

    // public static class pair{
	// 	int vtx;
	// 	String psf;     //path so far
	// 	int level=0;

	// 	pair(int vtx,String psf){
	// 		this.vtx=vtx;
	// 		this.psf=psf;
	// 	}

	// 	pair(int vtx,String psf,int level){
	// 		this.vtx=vtx;
	// 		this.psf=psf;
	// 		this.level=level;
	// 	}
	// } 

	// public static void BFS(int src,boolean[] vis){
	// 	LinkedList<pair> que=new LinkedList<>();
	// 	// LinkedList<int[]> que=new LinkedList<>();
	// 	// que.addLast(new int[]{1,0});

	// 	que.addLast(new pair(src, src + " "));
	// 	que.addLast(null);
	// 	int desti=6;

	// 	int level=0;
	// 	while(que.size()!=1){
	// 		pair rvtx=que.removeFirst();
			
	// 		if(vis[rvtx.vtx]){
	// 			System.out.println("Cycle: " + rvtx.psf);
	// 			continue;
	// 		}

	// 		if(rvtx.vtx==desti){
	// 			System.out.println("destinantion: " + rvtx.psf + " -> " + level);
	// 		}
			
	// 		vis[rvtx.vtx]=true;

	// 		for(Edge e: graph[rvtx.vtx]){
	// 			if(!vis[e.v])
	// 			   que.addLast(new pair(e.v,rvtx.psf+ e.v));
	// 		}

	// 		if(que.getFirst()==null){
	// 			level++;
	// 			que.removeFirst();
	// 			que.addLast(null);
	// 		}
	// 	}
    // }
    
    // public static void BFS_02(int src,boolean[] vis){
	// 	LinkedList<pair> que=new LinkedList<>();
	// 	que.addLast(new pair(src,src+"",0));
	// 	int desti=6;

	// 	// int level=0;
	// 	while(que.size()!=0){
	// 		pair rvtx=que.removeFirst();
			
	// 		if(vis[rvtx.vtx]){
	// 			System.out.println("Cycle: " + rvtx.psf);
	// 			continue;
	// 		}

	// 		if(rvtx.vtx==desti){
	// 			System.out.println("destinantion: " + rvtx.psf + " -> " + rvtx.level);
	// 		}
			
	// 		vis[rvtx.vtx]=true;

	// 		for(Edge e: graph[rvtx.vtx]){
	// 			if(!vis[e.v])
	// 			   que.addLast(new pair(e.v,rvtx.psf+ e.v, rvtx.level+1));
	// 		}
	// 	}
}