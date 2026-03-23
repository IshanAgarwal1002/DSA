#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Edge{
    public:
        int v, w;

        Edge(int v,int w)
        {
            this->v = v;
            this->w = w;
        }
};

int N = 7;
vector<vector<Edge>> graph(N,vector<Edge>());

void addEdge(vector<vector<Edge>> &gp, int u, int v, int w)
{
    gp[u].push_back(Edge(v,w));
    gp[v].push_back(Edge(u,w));
}

int findEdge(int u, int v)
{
    int idx = -1;
    for(int i=0;i<graph[u].size();i++)
    {
        Edge e = graph[u][i];
        if(e.v == v)
        {
            idx = i;
            break;
        }
    }
    return idx;
}

void removeEdge(int u, int v)
{
    int idx1 = findEdge(u,v);
    int idx2 = findEdge(v,u);

    graph[u].erase(graph[u].begin() + idx1);
    graph[v].erase(graph[v].begin() + idx2);
}

void removeVertex(int vtx)
{
    while(graph[vtx].size()!=0)
    {
        Edge e = graph[vtx].back();
        removeEdge(vtx,e.v);
    }
}

void display(vector<vector<Edge>> &gp)
{
    for(int i=0;i<gp.size();i++)
    {
        cout<<i<<" -> ";
        for(Edge j:gp[i])
        {
            cout<<"("<<j.v<<","<<j.w<<")";
        }
        cout<<"\n";
    }
    cout<<"\n";
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

//Question=================================================

//determine if there is a continuous path between given source and destination
bool hasPath(int src, int dest, vector<bool> &vis)
{
    if(src == dest)
        return true;

    bool res = false;
    vis[src] = true;
    for(Edge e:graph[src])
    {
        if(!vis[e.v])
            res = res || hasPath(e.v, dest, vis);
    }
    return res;
}

int allPath(int src, int dest, vector<bool> &vis, int w, string ans)
{
    if(src == dest)
    {
        cout<< ans << dest << "@" << w <<"\n";
        return 1;
    }
 
    vis[src] = true;
    int count = 0;
    for(Edge e:graph[src])
    {
        if(!vis[e.v])
            count += allPath(e.v, dest, vis, w + e.w, ans + to_string(src) + " ");
    }
    vis[src] = false;

    return count;
}

class allSolutionPair
{
public:
    int lightW = 1e7;
    int heavyW = 0;
    int ceil = 1e7;
    int floor = 0;
};

void allSolution(int src, int dest, vector<bool> &vis, int w, string ans, allSolutionPair &pair, int data)
{
    if (src == dest)
    {
        pair.heavyW = max(pair.heavyW, w);
        pair.lightW = min(pair.lightW, w);

        if (w > data)
            pair.ceil = min(pair.ceil, w);
        if (w < data)
            pair.floor = max(pair.floor, w);
        return;
    }

    vis[src] = true;

    for (Edge e : graph[src])
    {
        if (!vis[e.v])
            allSolution(e.v, dest, vis, w + e.w, ans + to_string(src) + " ", pair,data);
    }

    vis[src] = false;
}

class grp{
    public:
        int weight = 0;
        string path = "";

        grp(int w, string s)
        {
            this->weight = w;
            this->path = s;
        }
};


//similarly, lightest weight path can be found
grp heavyWeightPath(int src, int dest, vector<bool> &vis)
{
    if(src == dest)
    {
        return grp(0,to_string(src));
    }

    vis[src] = true;
    grp ans(0,"");

    for(Edge e:graph[src])
    {
        if(!vis[e.v])
        {
            grp recAns = heavyWeightPath(e.v,dest,vis);
            if(recAns.weight + e.w > ans.weight)
            {
                ans.weight = recAns.weight + e.w;
                ans.path = to_string(src) + " " + recAns.path;
            }
        }
    }

    vis[src] = false;
    return ans;
}

//DFS========================================================================

//hamiltonian path
int hamiltonianPathAndCycle(int src, int osrc,vector<bool> &vis,string path, int edgeCount)
//osrc - original source
{
    if(edgeCount==vis.size()-1)
    {
        int idx = findEdge(src,osrc);
        if(idx == -1)
            cout<<"Path: "<<path<<src<<"\n";
        else
            cout<<"Cycle: "<<path<<src<<"\n";
        
        return 1;
    }

    vis[src] = true;
    int count = 0;

    for(Edge e:graph[src])
    {
        if(!vis[e.v])
            count += hamiltonianPathAndCycle(e.v, osrc, vis, path + to_string(src) + " ", edgeCount + 1);
    }

    vis[src] = false;
    return count;
}

//GCC - Get number of Connected Components
void GCC_DFS(int vtx, vector<bool> &vis)
{
    vis[vtx] = true;;
    for(Edge e:graph[vtx])
    {
        if(!vis[e.v])
            GCC_DFS(e.v,vis);
    }
}

int GCC()
{
    vector<bool> vis(N,false);
    int count = 0;
    for(int i=0;i<N;i++)
    {
        if(!vis[i])
        {
            ++count;
            GCC_DFS(i,vis);
        }
    }
    return count;
}


void set1()
{
    // removeEdge(3,4);
    // removeVertex(3);

    vector<bool> vis(N, false);
    // cout << hasPath(0, 6, vis)<<endl;
    cout << allPath(0, 6, vis, 0, "") << endl;

    // allSolutionPair pair;
    // allSolution(0, 6, vis, 0, "", pair, 30);
    // cout << pair.heavyW << " -> " << pair.lightW << " -> " << pair.ceil << " -> " << pair.floor << " -> " << endl;

    // hamiltonianPath(2,2,vis,0,"");
    // display(graph);
}

//BFS=====================================================
int dest = 6;

void BFS(int src,vector<bool>&vis){
    queue<pair<int,string>> que;
    que.push({src,to_string(src)+" "});

    while(que.size() != 0)
    {
        pair <int,string> vtx = que.front();
        que.pop();

        if(vis[vtx.first])      //cycle
        {
            cout<<"Cycle: "<<vtx.second<<"\n";
            continue;
        }

        if(vtx.first == dest)
        {
            cout<<"Destination: "<<vtx.second<<"\n";
        }

        vis[vtx.first] = true;
        for(Edge e:graph[vtx.first])
        {
            if(!vis[e.v])
            {
                que.push({e.v,vtx.second + to_string(e.v) + " "});
            }
        }

    }
}

void BFS2(int src,vector<bool>&vis)
{
    queue<pair<int,string>> que;
    que.push({src, to_string(src)+" "});
    que.push({-1,""});

    int level = 0;
    while(que.size() != 1)
    {
        pair<int,string> vtx = que.front();
        que.pop();

        if(vis[vtx.first])
        {
            cout<<"Cycle: "<<vtx.second<<"\n";
            continue;
        }

        if(vtx.first == dest)
        {
            cout<<"Destinaton: "<<vtx.second<<" -> "<<level<<"\n";
        }

        vis[vtx.first] = true;
        for(Edge e:graph[vtx.first])
        {
            if(!vis[e.v])
            {
                que.push({e.v, vtx.second + to_string(e.v) + " "});
            }
        }

        if(que.front().first == -1)
        {
            level++;
            que.pop();
            que.push({-1,""});
        }
    }
}

class Pair{
    public: 
        int src;
        string psf; //path so far
        int level;

        Pair(int src,string psf,int level)
        {
            this->src = src;
            this->psf = psf;
            this->level = level;
        }
};

void BFS3(int src,vector<bool>&vis)
{
    queue<Pair> que;
    que.push({src, to_string(src)+" ",0});

    while(que.size() != 0)
    {
        Pair vtx = que.front();
        que.pop();

        if(vis[vtx.src])
        {
            cout<<"Cycle: "<<vtx.psf<<"\n";
            continue;
        }

        if(vtx.src == dest)
        {
            cout<<"Destinaton: "<<vtx.psf<<" -> "<<vtx.level<<"\n";
        }

        vis[vtx.src] = true;
        for(Edge e:graph[vtx.src])
        {
            if(!vis[e.v])
            {
                que.push({e.v, vtx.psf + to_string(e.v) + " ",vtx.level+1});
            }
        }
    }
}

void BFS4(int src, vector<bool> &vis)
{
    queue<int> que;
    que.push(src);

    int level = 0;
    int cycle = 0;

    while (que.size() != 0)
    {
        int size = que.size();

        while (size--)
        {
            int rvtx = que.front();
            que.pop();

            if (vis[rvtx]) //cycle.
            {
                cout << "Cycle No. " + to_string(cycle) + ": " << rvtx << endl;
                cycle++;
                continue;
            }

            if (rvtx == dest)
            {
                cout << "destination: " << level << endl;
            }

            vis[rvtx] = true;
            for (Edge e : graph[rvtx])
            {
                if (!vis[e.v])
                {
                    que.push(e.v);
                }
            }
        }
        level++;
    }
}

void BFS5(int src, vector<bool> &vis)
{
    queue<int> que;
    que.push(src);
    vis[src] = true;

    int level = 0;

    while (que.size() != 0)
    {
        int size = que.size();

        while (size--)
        {
            int rvtx = que.front();
            que.pop();

            if (rvtx == dest)
                cout << "destination: " << level << endl;

            for (Edge e : graph[rvtx])
            {
                if (!vis[e.v])
                {
                    que.push(e.v);
                    vis[e.v] = true;
                }
            }
        }
        level++;
    }
}

//bipartite graph============================================
bool isBipartite_(int src,vector<int> &vis)
{
    // vis[x]={-1(non visited),0(visited with red),1(visited with green)}
    queue<pair<int,int>> que;
    que.push({src,0});  // vtx, color (0 - red, 1 - green)

    while(que.size()!=0)
    {
        int size=que.size();
        while(size--)
        {
            pair<int,int> p = que.front();
            que.pop();    
              
            int rvtx=p.first;
            int color=p.second; 

            if(vis[rvtx] != -1)
            {   // conflict? (either same color/Set or different colors/Set)
                if(color != vis[rvtx]) 
                    return false;
                continue;
            }

            vis[rvtx]=color;    
            for(Edge e: graph[rvtx])
            {
                if(!vis[e.v])
                   que.push({e.v,(color+1)%2});
            }
        }
    }

    return true;
}

bool isBipartite() 
{
    vector<int> vis(N,-1);

    for(int i=0;i<N;i++)
    {
        if(vis[i] == -1)
        {
            if(!isBipartite_(i,vis))
                return false;
        }
    }

    return true;
}

void set2()
{
    vector<bool> vis(N, false);

    // BFS(0,vis);
    // BFS2(0,vis);
    // BFS3(0,vis);
    BFS5(0,vis);
}

void solve()
{
    constructGraph();
    // set1();
    set2();
}

int main()
{
    
    solve();
    return 0;
}