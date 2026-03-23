#include<iostream>
#include<vector>
using namespace std;

void display(vector<int> &arr)
{
    for(int i:arr)
        cout<<i<<" ";
    cout<<"\n";
}

//leetcode 70
// int climbStairs(int n,vector<int> &dp) {
//     if(n==0)
//     {
//         return dp[n] = 1;
//     }
//     if(dp[n] != 0)  
//         return dp[n];
//     int count = 0;
//     for(int i=1;i<=2 && n-i>=0;i++)
//         count += climbStairs(n-i,dp);
//     return dp[n] = count;
// }

int climbStairs_(int N,vector<int> &dp) {
    for(int n=0;n<=N;n++)
    {
        if(n==0)
        {
            dp[n] = 1;
            continue;
        }
        int count = 0;
        for(int i=1;i<=2 && n-i>=0;i++)
            count += dp[n-i];//climbStairs(n-i,dp);
        dp[n] = count;
    }  
    return dp[N];
}

int climbStairs(int n) 
{
    vector<int> dp(n+1,0);
    return climbStairs_(n,dp);
}

void solve()
{
    int n = 6;
    vector<int> dp(n+1,0);
    cout<<climbStairs(n,dp)<<"\n";
    display(dp);
}

int main()
{
    solve();
    return 0;
}