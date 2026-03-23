#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;

class Edge
{
    public:
        int v,w;
        Edge(){}
        Edge(int v, int w)
        {
            this->v = v;
            this->w = w;
        }
};

int N = 7;
vector<vector<Edge>> graph(N);

void addEdge(vector<vector<Edge>> &gp, int u, int v, int w)
{
    gp[u].push_back(Edge(v,w));
}

void display(vector<vector<Edge>> &gp)
{
    for(int i=0;i<N;i++)
    {
        cout<<i<<" -> ";
        for(Edge e:gp[i])
        {
            cout<<"("<<e.v<<","<<e.w<<") ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

//topological Order===============================================
void dfs_topo(int vtx, vector<bool> &vis, stack<int> &st)
{
    vis[vtx] = true;
    for(Edge e:graph[vtx])
    {
        if(!vis[e.v])
            dfs_topo(e.v,vis,st);
    }
    st.push(vtx);
}

void topologicalOrder()
{
    vector<bool> vis(N,false);
    stack<int> st;
    for(int i=0;i<N;i++)
    {
        if(!vis[i])
            dfs_topo(i,vis,st);
    }

    while(st.size()!=0)
    {
        cout<<st.top()<<" ";
        st.pop();
    }
}

//Kahns Algorithm=================================================
void KahnsAlgo()
{
    vector<int> indegree(N,0);
    for(int i=0;i<N;i++)
    {
        for(Edge e:graph[i])
            ++indegree[e.v];
    }

    queue<int> que;
    vector<int> ans;

    for(int i=0;i<N;i++)
        if(!indegree[i])
            que.push(i);
    
    while(que.size()!=0)
    {
        int rVtx = que.front();
        que.pop();

        ans.push_back(rVtx);
        for(Edge e:graph[rVtx])
        {
            if(--indegree[e.v]==0)
                que.push(e.v);
        }
    }

    if(ans.size()!=N)   ans.clear();

    for(int i:ans)
        cout<<i<<" ";
}

//graph construction==============================================
void constructGraph()
{
    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 3, 10);
    addEdge(graph, 1, 2, 10);
    addEdge(graph, 2, 3, 40);
    addEdge(graph, 3, 4, 2);
    addEdge(graph, 4, 5, 2);
    addEdge(graph, 4, 6, 8);
    addEdge(graph, 5, 6, 3);
    // addEdge(graph, 2, 5, 4);

    display(graph);
}

void solve()
{
    
}

int main()
{
    constructGraph();
    solve();
    return 0;
}