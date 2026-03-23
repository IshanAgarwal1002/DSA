#include<iostream>
#include<list>
#include<vector>
using namespace std;

void display(vector<int> &arr)
{
    for(int i:arr)
        cout<<i<<" ";
    cout<<"\n";
}

void display2D(vector<vector<int>> &arr)
{
    for(vector<int> ar:arr)
        display(ar);
    cout<<"\n";
}

int fibo(int n, vector<int> &dp)           //memoization
{
    if(n<=1)    
        return dp[n] = n;
    if(dp[n]!=-1)
        return dp[n];
    int ans = fibo(n-1,dp) + fibo(n-2,dp);
    return dp[n] = ans;
}

int fiboDP(int N, vector<int> &dp)        //tabulation
{
    for(int n = 0;n<=N;n++)
    {
        if(n<=1)    
        {
            dp[n]  = n;
            continue;
        }

        int ans = dp[n-1] + dp[n-2];//fibo(n-1,dp) + fibo(n-2,dp);
        dp[n] = ans;
    }

    return dp[N];
}

int fibo_btr(int n)
{
    int a = 0;  //F(0)
    int b = 1;  //F(1)
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum = a + b;
        a = b;
        b = sum;
    }

    return a;
}

void set1()
{
    int n = 5;
    vector<int> dp(n+1,-1);
    cout<<fibo(n,dp)<<"\n";
    display(dp);

    cout<<fiboDP(n,dp)<<"\n";
    display(dp);
}

//----------------------------------------------------------------------------------------------------------------------

int mazePathHVD(int sr,int sc,int er,int ec, vector<vector<int>> &dp)
{
    if(sr == er && sc == ec)
    {
        return dp[sr][sc] = 1;
    }

    if(dp[sr][sc] != 0)
        return dp[sr][sc];

    int count = 0;
    if(sr+1<=er)
        count += mazePathHVD(sr+1,sc,er,ec,dp);
    if(sr+1<=er && sc+1<=ec)
        count += mazePathHVD(sr+1,sc+1,er,ec,dp);
    if(sc+1<=ec)
        count += mazePathHVD(sr,sc+1,er,ec,dp);

    return dp[sr][sc] = count;
}

int mazePathHVD_DP(int sr,int sc,int er,int ec, vector<vector<int>> &dp)
{
    for(sr = er;sr>=0;sr--)
    {
        for(sc = ec;sc>=0;sc--)
        {
            if(sr == er && sc == ec)
            {
                dp[sr][sc] = 1;
                continue;
            }

            int count = 0;
            if(sr+1<=er)
                count += dp[sr+1][sc];//mazePathHVD(sr+1,sc,er,ec,dp);
            if(sr+1<=er && sc+1<=ec)
                count += dp[sr+1][sc+1];//mazePathHVD(sr+1,sc+1,er,ec,dp);
            if(sc+1<=ec)
                count += dp[sr][sc+1];//mazePathHVD(sr,sc+1,er,ec,dp);

            dp[sr][sc] = count;
        }
    }
    return dp[0][0];
}

int mazePathHVD_multi(int sr,int sc,int er,int ec,vector<vector<int>> &dp)
{
    if(sr==er && sc == ec)
    {
        return dp[sr][sc] = 1;
    }

    if(dp[sr][sc] != 0)
        return dp[sr][sc];

    int count = 0;
    for(int jump = 1;sr + jump <= er;jump++)
        count += mazePathHVD_multi(sr+jump,sc,er,ec,dp);

    for(int jump = 1;sr + jump <= er && sc + jump <= ec;jump++)
        count += mazePathHVD_multi(sr+jump,sc+jump,er,ec,dp);
        
    for(int jump = 1;sc + jump <= ec;jump++)
        count += mazePathHVD_multi(sr,sc+jump,er,ec,dp);

    return dp[sr][sc] = count;
}

int mazePathHVD_multi_DP(int sr,int sc,int er,int ec,vector<vector<int>> &dp)
{
    for(sr=er;sr>=0;sr--)
    {
        for(sc = ec;sc>=0;sc--)
        {
            if(sr==er && sc == ec)
            {
                dp[sr][sc] = 1;
                continue;
            }

            int count = 0;
            for(int jump = 1;sr + jump <= er;jump++)
                count += dp[sr+jump][sc];//mazePathHVD_multi(sr+jump,sc,er,ec,dp);

            for(int jump = 1;sr + jump <= er && sc + jump <= ec;jump++)
                count += dp[sr+jump][sc+jump];//mazePathHVD_multi(sr+jump,sc+jump,er,ec,dp);
        
            for(int jump = 1;sc + jump <= ec;jump++)
                count += dp[sr][sc+jump];//mazePathHVD_multi(sr,sc+jump,er,ec,dp);

            dp[sr][sc] = count;
        }
    }
    return dp[0][0];
}

void pathSet()
{
    int sr = 0, sc = 0, er = 2,ec = 2;
    vector<vector<int>> dp(3,vector<int>(3,0));
    // cout<<mazePathHVD(sr,sc,er,ec,dp)<<"\n";
    cout<<mazePathHVD_multi(sr,sc,er,ec,dp)<<"\n";
    display2D(dp);

    // cout<<mazePathHVD_DP(sr,sc,er,ec,dp)<<"\n";
    cout<<mazePathHVD_multi_DP(sr,sc,er,ec,dp)<<"\n";
    display2D(dp);
}

int boardPath(int sp,int ep,vector<int> &dp)
{
    if (sp == ep)
    {
        return dp[sp] = 1;
    }

    if (dp[sp] != 0)
        return dp[sp];

    int count = 0;
    for (int dice = 1; sp + dice <= ep && dice <= 6; dice++)
        count += boardPath(sp + dice, ep, dp);

    return dp[sp] = count;
}

int boardPathDP(int sp, int ep, vector<int> &dp)
{

    for (sp = ep; sp >= 0; sp--)
    {
        if (sp == ep)
        {
            dp[sp] = 1;
            continue;
        }

        int count = 0;
        for (int dice = 1; sp + dice <= ep && dice <= 6; dice++)
            count += dp[sp + dice]; //boardPath(sp + dice, ep, dp);
        dp[sp] = count;
    }

    return dp[0];
}

int boardPath_best(int sp, int ep)
{
    list<int> ll;
    for (sp = ep; sp >= 0; sp--)
    {
        if (sp > ep - 2)
        {
            ll.push_front(1);
            continue;
        }

        if (ll.size() <= 6)
            ll.push_front(2 * ll.front());
        else
        {
            ll.push_front(2 * ll.front() - ll.back());
            ll.pop_back();
        }
    }

    return ll.front();
}

int boardPathWithDiceArrayDP(int sp, int ep, vector<int> &dp, vector<int> &diceArray)
{

    for (sp = ep; sp >= 0; sp--)
    {
        if (sp == ep)
        {
            dp[sp] = 1;
            continue;
        }

        int count = 0;
        for (int dice = 0; sp + diceArray[dice] <= ep && dice < diceArray.size(); dice++)
            count += dp[sp + diceArray[dice]]; //boardPath(sp + dice, ep, dp);
        dp[sp] = count;
    }

    return dp[0];
}

int friendsPairing(int n, vector<int> &dp)
{
    if(n<=1)
        return dp[n] = 1;
    if(dp[n] != 0)
        return dp[n];
    
    int single = friendsPairing(n-1,dp);
    int paired = friendsPairing(n-2,dp)*(n-1);

    return dp[n] = single + paired;
}

int friendsPairingDP(int N, vector<int> &dp)
{
    for(int n=0;n<=N;n++)
    {
        if(n<=1)
        {
            dp[n] = 1;
            continue;
        }
    
        int single = dp[n-1];   //friendsPairing(n-1,dp);
        int paired = dp[n-2] * (n-1);   //friendsPairing(n-2,dp)*(n-1);

        dp[n] = single + paired;
    }
    return dp[N];
}

//leetcode 64
int minPathSum_(vector<vector<int>>& grid, int sr, int sc, int er, int ec,vector<vector<int>> &dp) {
    if(sr == er && sc == ec)
    {
        return dp[sr][sc] = grid[sr][sc];
    }

    if(dp[sr][sc] != 0)
        return dp[sr][sc];

    int ans = 1e8;
    if(sr+1<=er)
        ans = min(ans,minPathSum_(grid,sr+1,sc,er,ec,dp));
    if(sc+1<=ec)
        ans = min(ans,minPathSum_(grid,sr,sc+1,er,ec,dp));

    return dp[sr][sc] = ans + grid[sr][sc];
}

int minPathSum_2(vector<vector<int>>& grid, int sr, int sc, int er, int ec,vector<vector<int>> &dp) {
    for(sr = er;sr>=0;sr--)
    {
        for(sc = ec;sc>=0;sc--)
        {
            if(sr == er && sc == ec)
            {
                dp[sr][sc] = grid[sr][sc];
                continue;
            }

            int ans = 1e8;
            if(sr+1<=er)
                ans = min(ans,dp[sr+1][sc]);
            if(sc+1<=ec)
                ans = min(ans,dp[sr][sc+1]);

            dp[sr][sc] = ans + grid[sr][sc];
        }
    }
    return dp[0][0];
}

int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> dp(m,vector<int>(n,0));
    return minPathSum_(grid,0,0,m-1,n-1,dp);
}


void set2()
{
    int sp = 0, ep = 10;
    vector<int> dp(ep + 1, 0);
    // vector<int> diceArray{1, 2, 3, 4, 5, 6};
    cout << boardPathDP(sp, ep, dp) << endl;
    // cout << boardPathWithDiceArrayDP(sp, ep, dp, diceArray) << endl;
    cout << boardPath_best(sp, ep);

    // display(dp);
    // display2D(dp);
}

//substring and subsequence series================================================

vector<bool> isPalindromeSubstring(string str)
{

}

int longestPalindromeSubstring(string str)
{
    
}


//coin series======================================================================

















//ques - can use each coin only once, lowest no. of coins needed
int targetSum(vector<int> &coins, int tar, int idx)
{
    if(tar == 0 || idx == coins.size())
    {
        if(tar == 0)
            return 1;
        return 0;
    }

    int 
}



//LIS type============================================================

int LIS_LeftToRight(vector<int> &arr)
{
    for(int i=0;i<)
}




void solve()
{
    // set1();
    // pathSet();
    set2();
}

int main()
{
    solve();
    return 0;
}