#include<iostream>
#include<vector>
using namespace std;

class Edge{
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
vector<vector<Edge>> graph(N, vector<Edge>());

void addEdge(vector<vector<Edge>> &gp, int u, int v, int w)
{
    gp[u].push_back(Edge(v,w));
    gp[v].push_back(Edge(u,w));
}

void display(vector<vector<Edge>> &gp)
{
    for(int i=0;i<gp.size();i++)
    {
        cout<<i<<" -> ";
        for(Edge i:gp[i])
        {
            cout<<"("<<i.v<<","<<i.w<<") ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

int findEdge(vector<vector<Edge>> &gp, int u, int v)
{
    int idx = -1;
    for(int i=0;i<gp[u].size();i++)
    {
        if(gp[u][i].v == v)
        {
            idx = i;
            break;
        }
    }
    return idx;
}

void removeEdge(vector<vector<Edge>> &gp, int u, int v)
{
    int i = findEdge(gp, u, v);
    int j = findEdge(gp, v, u);

    gp[u].erase(gp[u].begin() + i);
    gp[v].erase(gp[v].begin() + j);
}

void removeVertex(vector<vector<Edge>> &gp, int ver)
{
    while(gp[ver].size() > 0)
    {
        Edge e = gp[ver].back();
        removeEdge(gp, ver, e.v);
    }
}

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

void solve1()
{
    constructGraph();
    removeVertex(graph, 3);
    display(graph);
}

int main()
{
    solve1();
    return 0;
}