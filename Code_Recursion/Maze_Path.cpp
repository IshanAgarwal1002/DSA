#include<iostream>
#include<vector>
using namespace std;

vector <string> mazePath_HV_1(int sr,int sc, int er, int ec)
{
    if(sr==er && sc==ec)
    {
        vector <string> base = {""};
        return base;
    }
    
    vector<string> ans;

    if(sr + 1 <= er)
    {
        vector <string> Ver = mazePath_HV_1(sr+1,sc,er,ec);
        for(string s:Ver)
            ans.push_back("V"+s);
    }

    if(sc + 1 <= ec)
    {
        vector <string> Hor = mazePath_HV_1(sr,sc+1,er,ec);
        for(string s:Hor)
            ans.push_back("H"+s);
    }
    
    return ans;
}

int mazePath_HV_2(int sr,int sc, int er, int ec,string ans)
{
    if(sr==er && sc==ec)
    {
        cout<<ans<<"\n";
        return 1;
    }

    int count = 0;

    if(sr + 1 <= er)
        count += mazePath_HV_2(sr+1,sc,er,ec,ans+"V");

    if(sc + 1 <= ec)
        count += mazePath_HV_2(sr,sc+1,er,ec,ans+"H");
    
    return count;
}

vector <string> mazePath_HVD_1(int sr,int sc,int er,int ec)
{
    if(sc == ec && sr == er)
    {
        vector <string> base = {""};
        return base;
    }

    vector <string> ans;

    if(sr+1 <= er)
    {
        vector <string> Ver = mazePath_HVD_1(sr+1,sc,er,ec);
        for(string s:Ver)
            ans.push_back("V"+s);
    }

    if(sc+1 <= ec  && sr+1 <= er)
    {
        vector <string> Dia = mazePath_HVD_1(sr+1,sc+1,er,ec);
        for(string s:Dia)
            ans.push_back("D"+s);
    }

    if(sc+1 <= ec)
    {
        vector <string> Hor = mazePath_HVD_1(sr,sc+1,er,ec);
        for(string s:Hor)
            ans.push_back("H"+s);
    }

    return ans;
}

int mazePath_HVD_2(int sr,int sc,int er,int ec,string ans)
{
    if(sc == ec && sr == er)
    {
        cout<<ans<<"\n";
        return 1;
    }

    int count = 0;

    if(sr+1 <= er)
        count += mazePath_HVD_2(sr+1,sc,er,ec,ans+"V");

    if(sc+1 <= ec  && sr+1 <= er)
        count += mazePath_HVD_2(sr+1,sc+1,er,ec,ans+"D");

    if(sc+1 <= ec)
        count += mazePath_HVD_2(sr,sc+1,er,ec,ans+"H");
    return count;
}

vector <string> mazePath_multi_HVD_1(int sr,int sc,int er,int ec)
{
    if(sc == ec && sr == er)
    {
        vector <string> base = {""};
        return base;
    }

    vector <string> ans;

    for(int jump = 1;sr+jump <= er;jump++)
    {
        vector <string> Ver = mazePath_multi_HVD_1(sr+jump,sc,er,ec);
        for(string s:Ver)
            ans.push_back("V" + to_string(jump) + s);
    }

    for(int jump = 1;sr+jump <= er && sc+jump <= ec; jump++)
    {
        vector <string> Dia = mazePath_multi_HVD_1(sr+jump,sc+jump,er,ec);
        for(string s:Dia)
            ans.push_back("D" + to_string(jump) + s);
    }

    for(int jump = 1;sc+jump <= ec;jump++)
    {
        vector <string> Hor = mazePath_multi_HVD_1(sr,sc+jump,er,ec);
        for(string s:Hor)
            ans.push_back("H"+ to_string(jump) + s);
    }

    return ans;
}

int mazePath_multi_HVD_2(int sr,int sc,int er,int ec,string ans)
{
    if(sc == ec && sr == er)
    {
        cout<<ans<<"\n";
        return 1;
    }

    int count=0;

    for(int jump = 1;sr+jump <= er;jump++)
        count += mazePath_multi_HVD_2(sr+jump,sc,er,ec,ans + "V" + to_string(jump));

    for(int jump = 1;sr+jump <= er && sc+jump <= ec; jump++)
        count += mazePath_multi_HVD_2(sr+jump,sc+jump,er,ec,ans + "D" + to_string(jump));

    for(int jump = 1;sc+jump <= ec;jump++)
        count += mazePath_multi_HVD_2(sr,sc+jump,er,ec,ans + "H" + to_string(jump));

    return count;
}

vector<vector<int>> dir4 = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};      //coordinates (y,x)
vector<string> dirN4 = {"R", "U", "L", "D"};

bool isValid(int r, int c, vector<vector<int>> &board)
{
    if(r<0 || c<0 || r >= board.size() || c >= board[0].size() || board[r][c]==0)
        return false;

    return true;
}

int mazePath_4D_1(int sr,int sc,int er, int ec, vector <vector <int>> &board, string ans)
{
    if(sr==er && sc==ec)
    {
        cout<<ans<<"\n";
        return 1;
    }

    int count=0;
    board[sr][sc]=0;

    for(int d=0;d<dir4.size();d++)
    {
        int r = sr + dir4[d][0];
        int c = sc + dir4[d][1]; 
        if(isValid(r,c,board))
        {
            count += mazePath_4D_1(r, c, er, ec, board, ans + dirN4[d]);
        }
    }

    board[sr][sc]=1;

    return count;
}

vector<string> mazePath_4D_2(int sr,int sc,int er, int ec, vector <vector <int>> &board)
{
    if(sr==er && sc==ec)
    {
        vector<string> base = {""};
        return base;
    }

    vector <string> ans;
    board[sr][sc]=0;

    for(int d=0;d<dir4.size();d++)
    {
        int r = sr + dir4[d][0];
        int c = sc + dir4[d][1]; 
        if(isValid(r,c,board))
        {
            vector<string> recAns = mazePath_4D_2(r, c, er, ec, board);
            for(string s:recAns)
                ans.push_back(dirN4[d]+s);
        }
    }

    board[sr][sc]=1;

    return ans;
}

vector<vector<int>> dir8 = {{0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}};      //coordinates (y,x)
vector<string> dirN8 = {"R", "E", "U", "N", "L", "W", "D", "S"};

int mazePath_8D_1(int sr,int sc,int er, int ec, vector <vector <int>> &board, string ans)
{
    if(sr==er && sc==ec)
    {
        cout<<ans<<"\n";
        return 1;
    }

    int count=0;
    board[sr][sc]=0;

    for(int d=0;d<dir8.size();d++)
    {
        int r = sr + dir8[d][0];
        int c = sc + dir8[d][1]; 
        if(isValid(r,c,board))
        {
            count += mazePath_8D_1(r, c, er, ec, board, ans + dirN8[d]);
        }
    }

    board[sr][sc]=1;

    return count;
}

vector<string> mazePath_8D_2(int sr,int sc,int er, int ec, vector <vector <int>> &board)
{
    if(sr==er && sc==ec)
    {
        vector<string> base = {""};
        return base;
    }

    vector <string> ans;
    board[sr][sc]=0;

    for(int d=0;d<dir8.size();d++)
    {
        int r = sr + dir8[d][0];
        int c = sc + dir8[d][1]; 
        if(isValid(r,c,board))
        {
            vector<string> recAns = mazePath_8D_2(r, c, er, ec, board);
            for(string s:recAns)
                ans.push_back(dirN8[d]+s);
        }
    }

    board[sr][sc]=1;

    return ans;
}

int mazePath_multi_8D_1(int sr,int sc,int er, int ec, int rad, vector <vector <int>> &board, string ans)
{
    if(sr==er && sc==ec)
    {
        cout<<ans<<"\n";
        return 1;
    }

    int count=0;
    board[sr][sc]=0;

    for(int d=0;d<dir8.size();d++)
    {
        for(int jump = 1;jump <= rad;jump++)
        {
            int r = sr + jump*dir8[d][0];
            int c = sc + jump*dir8[d][1]; 
            if(isValid(r,c,board))
            {
                count += mazePath_multi_8D_1(r, c, er, ec, rad, board, ans + dirN8[d] + to_string(jump));
            }   
        }
    }

    board[sr][sc]=1;

    return count;
}

vector<string> mazePath_multi_8D_2(int sr,int sc,int er, int ec, int rad, vector <vector <int>> &board)
{
    if(sr==er && sc==ec)
    {
        vector<string> base = {""};
        return base;
    }

    vector <string> ans;
    board[sr][sc]=0;

    for(int d=0;d<dir8.size();d++)
    {
        for(int jump = 1;jump <= rad;jump++)
        {
            int r = sr + jump*dir8[d][0];
            int c = sc + jump*dir8[d][1]; 
            if(isValid(r,c,board))
            {
                vector<string> recAns = mazePath_multi_8D_2(r, c, er, ec, rad, board);
                for(string s:recAns)
                    ans.push_back(dirN8[d] + to_string(jump) + s);
            }
        }
    }

    board[sr][sc]=1;

    return ans;
}

//==========Height of tree or longest path length =================

int mazePath_Height(int sr,int sc,int er,int ec,vector<vector<int>> &board)
{
    if(sr==er && sc==ec)
    {      
        return 0;
    }

    int maxHeight = 0;
    board[sr][sc]=0;

    for(int d=0;d<dir8.size();d++)
    {
        int r = sr + dir8[d][0];
        int c = sc + dir8[d][1];
        if(r>=0 && c>=0 && r<board.size() && c<board[0].size() && board[r][c]==1)
        {
            int recHeight = mazePath_Height(r,c,er,ec,board) + 1;
            maxHeight = max(maxHeight,recHeight);
        }
    }

    board[sr][sc]=1;
    return maxHeight;
}

class Pair{
    public:

    int len;
    string str;

    Pair(int len, string str)
    {
        this->len = len;
        this->str = str;
    }
};

Pair longestPath(int sr,int sc,int er,int ec,vector<vector<int>> &board)
{
    if(sr==er && sc==ec)
    {
        Pair p(0,"");
        return p;
    }

    Pair maxPath(0,"");
    board[sr][sc]=0;

    for(int d=0;d<dir8.size();d++)
    {
        int r = sr + dir8[d][0];
        int c = sc + dir8[d][1];
        if(isValid(r,c,board))
        {
            Pair ans = longestPath(r,c,er,ec,board);
            if(ans.len + 1 > maxPath.len)
            {
                maxPath.len = ans.len + 1;
                maxPath.str = dirN8[d] + ans.str;
            }
        }
    }

    board[sr][sc] = 1;
    return maxPath;    
}

Pair shortestPath(int sr,int sc,int er,int ec,vector<vector<int>> &board)
{
    if(sr==er && sc==ec)
    {
        Pair p(0,"");
        return p;
    }

    Pair shortPath(10000,"");
    board[sr][sc]=0;

    for(int d=0;d<dir8.size();d++)
    {
        int r = sr + dir8[d][0];
        int c = sc + dir8[d][1];
        if(isValid(r,c,board))
        {
            Pair ans = shortestPath(r,c,er,ec,board);
            if(ans.len + 1 < shortPath.len)
            {
                shortPath.len = ans.len + 1;
                shortPath.str = dirN8[d] + ans.str;
            }
        }
    }

    board[sr][sc] = 1;
    return shortPath;    
}

int main()
{
    int sr=0,sc=0,er=2,ec=2;
    // cout<<mazePath_HVD_2(0,0,2,2,"");
    // vector <string> ans = mazePath_multi_HVD_1(0,0,2,2);
    // for(string s:ans)
    //     cout<<s<<"\n";
    int rad = max(er,ec);
    vector <vector<int>> board(3,vector<int>(3,1));
    // cout<<mazePath_multi_8D_1(sr,sc,er,ec,rad,board,"");
    // vector <string> ans = mazePath_multi_8D_2(sr,sc,er,ec,rad,board);
    // for(string s:ans)
    //     cout<<s<<"\n";
    // cout<<mazePath_Height(sr,sc,er,ec,board);
    Pair p = shortestPath(sr,sc,er,ec,board);
    cout<<p.len<<" "<<p.str; 
    return 0;
}