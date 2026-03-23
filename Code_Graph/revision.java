import java.util.ArrayList;

public class revision{

    public static class Edge{
        int v,w;
        Edge(){}
        Edge(int v, int w)
        {
            this.v = v;
            this.w = w;
        }
    } 

    static int N = 7;
    static ArrayList<Edge>[] graph;

    public static void addEdge(ArrayList<Edge>[] gp, int u, int v, int w)
    {
        gp[u].add(new Edge(v,w));
        gp[v].add(new Edge(u,w));
    }

    public static void display(ArrayList<Edge>[] gp)
    {
        for(int i=0;i<gp.length;i++)
        {
            System.out.print(i + " -> ");
            for(Edge j:gp[i])
            {
                System.out.print("(" + j.v + "," + j.w + ") ");
            }
            System.out.println();
        }
        System.out.println();
    }

    public static void constructGraph()
    {
        graph = new ArrayList[N];
        for(int i=0;i<N;i++)
        {
            graph[i] = new ArrayList<Edge>();
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

    public static int findEdge(ArrayList<Edge>[] gp, int u, int v)
    {
        int idx = -1;
        for(int i=0;i<gp[u].size();i++)
        {
            if(gp[u].get(i).v == v)
            {
                idx = i;
                break;
            }
        }
        return idx;
    }

    public static void removeEdge(ArrayList<Edge>[] gp, int u, int v)
    {
        int i = findEdge(gp, u, v);
        int j = findEdge(gp, v, u);

        gp[u].remove(i);
        gp[v].remove(j);
    }

    public static void removeVertex(ArrayList<Edge>[] gp, int ver)
    {
        while(gp[ver].size() > 0)
        {
            Edge e = gp[ver].get(0);
            removeEdge(gp, ver, e.v);
        }
    }

    public static void solve()
    {
        constructGraph();
        removeVertex(graph, 3);
        display(graph);
    }

    public static void main(String[] args)
    {
        solve();
    }

}