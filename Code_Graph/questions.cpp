#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
using namespace std;

//leetcode 200
void dfs(vector<vector<char>>& grid, int i, int j, int dir[][2])
{
    grid[i][j] = '2';

    for(int d=0;d<4;d++)
    {
        int r = i + dir[d][0];
        int c = j + dir[d][1];

        if(r>=0 && c>=0 && r < grid.size() && c < grid[0].size() && grid[r][c] == '1')
            dfs(grid,r,c,dir);
    }
}

int numIslands(vector<vector<char>>& grid) {

    int dir[4][2] = { {-1,0}, {0,-1}, {0,1}, {1,0}};

    int count = 0;
    for(int i=0;i<grid.size();i++)
    {
        for(int j=0;j<grid[0].size();j++)
        {
            if(grid[i][j]=='1')
            {
                ++count;
                dfs(grid,i,j,dir);
            }
        }
    }

    return count;
}

//leetcode 695
int dfs(vector<vector<int>>& grid, int i, int j, int dir[][2])
{
    grid[i][j] = 2;
    int count = 0;
    for(int d=0;d<4;d++)
    {
        int r = i + dir[d][0];
        int c = j + dir[d][1];

        if(r>=0 && c>=0 && r < grid.size() && c < grid[0].size() && grid[r][c] == 1)
            count += dfs(grid,r,c,dir);
    }
    return count+1;
}


int maxAreaOfIsland(vector<vector<int>>& grid) {
        
    int dir[4][2] = { {-1,0}, {0,-1}, {0,1}, {1,0}};

    int count = 0;
    for(int i=0;i<grid.size();i++)
    {
        for(int j=0;j<grid[0].size();j++)
        {
            if(grid[i][j]==1)
            {
                count = max(count,dfs(grid,i,j,dir));   
            }
        }
    }

    return count;
}

//leetcode 463
int islandPerimeter(vector<vector<int>>& grid) {
    
    int totalOnes = 0;
    int commonEdges = 0;

    for(int i=0;i<grid.size();i++)
    {
        for(int j=0;j<grid[0].size();j++)
        {
            if(grid[i][j]==1)
            {
                totalOnes++;
                if(j + 1 < grid[0].size() && grid[i][j+1]==1)
                    commonEdges++;
                if(i + 1 < grid.size() && grid[i+1][j]==1)
                    commonEdges++;
            }
        }
    }

    return totalOnes*4 - commonEdges*2;
}

//leetcode 130
void dfs(vector<vector<char>>& grid, int i, int j, int dir[][2])
{
    grid[i][j] = 'A';

    for(int d=0;d<4;d++)
    {
        int r = i + dir[d][0];
        int c = j + dir[d][1];

        if(r>=0 && c>=0 && r < grid.size() && c < grid[0].size() && grid[r][c] == 'O')
            dfs(grid,r,c,dir);
    }
}

void solve(vector<vector<char>>& board) {
    if(board.empty())   return;
    
    int m = board.size();
    int n = board[0].size();

    int dir[4][2] = { {-1,0}, {0,-1}, {0,1}, {1,0}};

    for(int i=0;i<n;i++)
    {
        if(board[0][i] == 'O')
            dfs(board,0,i,dir);
        if(board[m-1][i] == 'O')
            dfs(board,m-1,i,dir);
    }

    for(int i=0;i<m;i++)
    {
        if(board[i][0] == 'O')
            dfs(board,i,0,dir);
        if(board[i][n-1] == 'O')
            dfs(board,i,n-1,dir);
    }

    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(board[i][j] == 'O')
                board[i][j] = 'X';
            else if(board[i][j] == 'A')
                board[i][j] = 'O';
        }
    }
}

//leetcode 785
bool isBipartite_(vector<vector<int>>& graph, int src, vector<int> &vis)
{// vis[x]={-1(non visited),0(visited with red),1(visited with green)}
    queue<pair<int,int>> que;
    que.push({src,0});          // vtx, color (0 - red, 1 - green)

    while(que.size()!=0)
    {
        int size = que.size();
        while(size--)
        {
            pair<int,int> p = que.front();
            que.pop();

            int rvtx = p.first;
            int color = p.second;

            if(vis[rvtx] != -1)             // conflict? (either same color/Set or different colors/Set)
            {
                if(vis[rvtx] != color)
                    return false;
                continue;
            }

            vis[rvtx] = color;
            for(int i:graph[rvtx])
            {
                if(vis[i] == -1)
                {
                    que.push({i,(color+1)%2});
                }
            }
        }
    }
    return true;
}

bool isBipartite(vector<vector<int>>& graph) 
{
    int N = graph.size();
    vector<int> vis(N,-1);

    for(int i=0;i<N;i++)
    {
        if(vis[i] == -1)
        {
            if(!isBipartite_(graph, i,vis))
                return false;
        }
    }

    return true;
}

//leetcode 994
int orangesRotting(vector<vector<int>>& grid) {
    
    if(grid.size() == 0 || grid[0].size()==0)
        return 0;

    int m = grid.size();
    int n = grid[0].size();
    int dir[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};

    queue<pair<int,int>> que;

    int freshOranges = 0;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(grid[i][j] == 1)
                ++freshOranges;
            else if(grid[i][j] == 2)
                que.push({i,j});
        }
    }

    if(freshOranges == 0)   return 0;

    int time = 0;
    while(que.size()!=0)
    {
        int size = que.size();
        while(size--)
        {
            pair<int,int> rIdx = que.front();
            que.pop();

            for(int i=0;i<4;i++)
            {
                int r = rIdx.first + dir[i][0];
                int c = rIdx.second + dir[i][1];

                if(r>=0 && c>=0 && r<m && c<n && grid[r][c] == 1)
                {
                    que.push({r,c});
                    grid[r][c] = 2;
                    --freshOranges;
                }
            }
        }
        ++time;
        if(freshOranges == 0)   return time;
    }

    return -1;
}

//leetcode 1091
int shortestPathBinaryMatrix(vector<vector<int>>& grid) {

    if(grid.size() == 0 || grid[0].size()==0)
        return -1;

    int m = grid.size();
    int n = grid[0].size();

    if(grid[0][0] == 1 || grid[m-1][n-1] == 1)  
        return -1;

    int dir[8][2] = {{0,1},{1,0},{0,-1},{-1,0},{-1,1},{1,-1},{1,1},{-1,-1}};

    queue<pair<int,int>> que;
    que.push({0,0});
    grid[0][0] = 1;

    int pathLength = 0;
    while(que.size()!=0)
    {
        int size = que.size();
        while(size--)
        {
            pair<int,int> rIdx = que.front();
            que.pop();

            if(rIdx.first == m-1 && rIdx.second == n-1) return pathLength + 1;

            for(int d = 0;d<8;d++)
            {
                int r = rIdx.first + dir[d][0];
                int c = rIdx.second + dir[d][1];

                if(r>=0 && c>=0 && r<m && c<n && grid[r][c] == 0)
                {
                    que.push({r,c});
                    grid[r][c] = 1;
                }
            }
        }
        ++pathLength;
    }

    return -1;
}

//leetcode 542
vector<vector<int>> updateMatrix(vector<vector<int>>& grid) {

    if(grid.size() == 0 || grid[0].size()==0)
        return grid;

    int m = grid.size();
    int n = grid[0].size();

    int dir[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};

    queue<pair<int,int>> que;
    vector<vector<int>> vis(m,vector<int>(n,-1));
    int countOnes = m*n;
    
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(grid[i][j] == 0)
            {
                --countOnes;
                que.push({i,j});
                vis[i][j] = 0;
            }
        }
    }

    while(que.size()!=0)
    {
        int size = que.size();
        while(size--)
        {
            pair<int,int> rIdx = que.front();
            que.pop();

            for(int d=0;d<4;d++)
            {
                int r = rIdx.first + dir[d][0];
                int c = rIdx.second + dir[d][1];

                if(r>=0 && c>=0 && r<m && c<n && grid[r][c] == 1 && vis[r][c] == -1)
                {
                    que.push({r,c});
                    vis[r][c] = vis[rIdx.first][rIdx.second] + 1;
                    countOnes--;
                }
            }
        }
        if(countOnes == 0)  break;;
    }

    return vis;
}

//leetcode 815
int numBusesToDestination(vector<vector<int>>& routes, int src, int dest) {

    int n = routes.size();
    unordered_map<int, vector<int>> BusStandToBus;

    for(int i=0;i<n;i++)
    {
        for(int j:routes[i])
            BusStandToBus[j].push_back(i);
    }

    vector<bool> vis_bus(n,false);
    unordered_set<int> vis_busStand;

    queue<int> que;
    que.push(src);
    vis_busStand.insert(src);

    int level = 0;

    while(que.size()!=0)
    {
        int size = que.size();
        while(size--)
        {
            int rStand = que.front();
            que.pop();

            if(rStand == dest)  return level;

            for(int Bus:BusStandToBus[rStand])
            {
                if(vis_bus[Bus])    continue;

                for(int i:routes[Bus])
                {
                    if(!vis_busStand.count(i))
                    {
                        que.push(i);
                        vis_busStand.insert(i);
                    }
                }
                vis_bus[Bus] = true;
            }
        }
        level++;
    }
    return -1;
}

//leetcode 286.=============================================================
void wallsAndGates(vector<vector<int>> &grid)
{
    if (grid.size() == 0 || grid[0].size() == 0)
        return;

    int n = grid.size();
    int m = grid[0].size();

    int dirA[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    queue<int> que;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == 0)
                que.push((i * m + j));

    int level = 1;
    while (que.size() != 0)
    {
        int size = que.size();
        while (size--)
        {
            int rvtx = que.front();
            que.pop();

            int r = rvtx / m;
            int c = rvtx % m;

            for (int d = 0; d < 4; d++)
            {
                int x = r + dirA[d][0];
                int y = c + dirA[d][1];

                if (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == 2147483647)
                {
                    que.push((x * m + y));
                    grid[x][y] = level;
                }
            }
        }
        level++;
    }
}

//leetcode 207 (using kahns algo based on bfs)
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {

    vector<vector<int>> graph(numCourses);
    vector<int> indegree(numCourses,0);
    for(vector<int> i:prerequisites)
    {
        graph[i[0]].push_back(i[1]);
        ++indegree[i[1]];
    }

    queue<int> que;
    int ans = 0;

    for(int i=0;i<numCourses;i++)
    {
        if(!indegree[i])
            que.push(i);
    }

    while(que.size()!=0)
    {
        int rVtx = que.front();
        que.pop();

        ans++;
        for(int i:graph[rVtx])
        {
            if(!(--indegree[i]))
                que.push(i);
        }
    }

    return (ans==numCourses);
}

//leetcode 207 (using dfs)
bool isCycleInTopo(int src,vector<bool> &vis,vector<bool> &myPath,vector<vector<int>> &graph)
{
    vis[src] = myPath[src] = true;

    bool res = false;
    for(int e:graph[src])
    {
        if(!vis[e])
            res = res || isCycleInTopo(e,vis,myPath,graph);
        else if(myPath[e])
            return true;
    }

    myPath[src] = false;
    return res;
}

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {

    vector<vector<int>> graph(numCourses);

    for(vector<int> i:prerequisites)
    {
        graph[i[0]].push_back(i[1]);
    }

    vector<bool> vis(numCourses,false);
    vector<bool> myPath(numCourses,false);

    for(int i=0;i<numCourses;i++)
        if(!vis[i] && isCycleInTopo(i,vis,myPath,graph))
            return false;

    return true;
}

//leetcode 210
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);
    vector<int> indegree(numCourses,0);
    for(vector<int> i:prerequisites)
    {
        graph[i[0]].push_back(i[1]);
        ++indegree[i[1]];
    }

    queue<int> que;
    vector<int> ans;

    for(int i=0;i<numCourses;i++)
    {
        if(!indegree[i])
            que.push(i);
    }

    while(que.size()!=0)
    {
        int rVtx = que.front();
        que.pop();

        ans.push_back(rVtx);
        for(int i:graph[rVtx])
        {
            if(!(--indegree[i]))
                que.push(i);
        }
    }

    if(ans.size() == numCourses)
        reverse(ans.begin(), ans.end());
    else
        ans.clear();
    
    return ans;
}

//leetcode 329
int longestIncreasingPath(vector<vector<int>>& matrix) {

    if(matrix.size() == 0 || matrix[0].size() == 0)
        return 0;
    
    int m = matrix.size();
    int n = matrix[0].size();

    vector<vector<int>> indegree(m,vector<int>(n,0));
    vector<vector<int>> dir = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            for(int d=0;d<4;d++)
            {
                int r = i + dir[d][0];
                int c = j + dir[d][1];

                if(r>=0 && c>=0 && r<m && c<n && matrix[r][c]>matrix[i][j])
                    ++indegree[r][c];
            }
        }
    }

    queue<pair<int,int>> que;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(!indegree[i][j])
                que.push({i,j});
        }
    }

    int level = 0;
    while(que.size()!=0)
    {
        int size = que.size();
        while(size--)
        {
            pair<int,int> p = que.front();
            que.pop();

            for(int d=0;d<4;d++)
            {
                int r = p.first + dir[d][0];
                int c = p.second + dir[d][1];

                if(r>=0 && c>=0 && r<m && c<n && matrix[r][c]> matrix[p.first][p.second] && --indegree[r][c] == 0)
                    que.push({r,c});
            }
        }
        level++;
    }

    return level;
}

//leetcode 684


//https://evanyang.gitbooks.io/leetcode/content/LeetCode/number_of_islands_ii.html
