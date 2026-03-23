#include<iostream>
#include<vector>
using namespace std;

int coin_permutation_infi_1(vector<int> &coins, int target, string ans)
{
    if(target==0)
    {
        cout<<ans<<"\n";
        return 1;
    }
    
    int count = 0;
    for(int i=0;i<coins.size();i++)
    {
        if(target-coins[i]>=0)
            count += coin_permutation_infi_1(coins,target-coins[i],ans+to_string(coins[i]));
    }

    return count;
}

int coin_permutation_1(vector<int> &coins, bool chk[], int target, string ans)
{
    if(target==0)
    {
        cout<<ans<<"\n";
        return 1;
    }
    
    int count = 0;
    for(int i=0;i<coins.size();i++)
    {
        if(!chk[i] && target-coins[i]>=0)
        {
            chk[i] = true;
            count += coin_permutation_1(coins,chk,target-coins[i],ans + to_string(coins[i]) + " ");
            chk[i] = false;
        }
    }

    return count;
}

int coin_combination_infi_1(vector<int> &coins,int idx, int target, string ans)
{
    if(target==0)
    {
        cout<<ans<<"\n";
        return 1;
    }
    
    int count = 0;
    for(int i=idx;i<coins.size();i++)
    {
        if(target-coins[i]>=0)
            count += coin_combination_infi_1(coins,i,target-coins[i],ans + to_string(coins[i]) + " ");
    }

    return count;
}

int coin_combination_1(vector<int> &coins,int idx, int target, string ans)
{
    if(target==0)
    {
        cout<<ans<<"\n";
        return 1;
    }
    
    int count = 0;
    for(int i=idx;i<coins.size();i++)
    {
        if(target-coins[i]>=0)
            count += coin_combination_1(coins,i+1,target-coins[i],ans + to_string(coins[i]) + " ");
    }

    return count;
}

int coin_permutation_infi_2(vector<int> &coins, int idx, int target, string ans)
{
    if(idx==coins.size() || target==0)
    {
        if(target==0)
        {
            cout<<ans<<"\n";
            return 1;
        }
        return 0;
    }
    
    int count = 0;
    if(target-coins[idx]>=0)
        count += coin_permutation_infi_2(coins,0,target-coins[idx],ans + to_string(coins[idx]) + " ");
    count += coin_permutation_infi_2(coins,idx+1,target,ans);

    return count;
}

int coin_permutation_2(vector<int> &coins, bool vis[], int idx, int target, string ans)
{
    if(idx==coins.size() || target==0)
    {
        if(target==0)
        {
            cout<<ans<<"\n";
            return 1;
        }
        return 0;
    }
    
    int count = 0;
    if(!vis[idx] && target-coins[idx]>=0)
    {
        vis[idx] = true;
        count += coin_permutation_2(coins,vis,0,target-coins[idx],ans + to_string(coins[idx]) + " ");
        vis[idx] = false;
    }
    count += coin_permutation_2(coins,vis,idx+1,target,ans);

    return count;
}

int coin_combination_infi_2(vector<int> &coins, int idx, int target, string ans)
{
    if(idx==coins.size() || target==0)
    {
        if(target==0)
        {
            cout<<ans<<"\n";
            return 1;
        }
        return 0;
    }
    
    int count = 0;
    if(target-coins[idx]>=0)
        count += coin_combination_infi_2(coins,idx,target-coins[idx],ans + to_string(coins[idx]) + " ");
    count += coin_combination_infi_2(coins,idx+1,target,ans);

    return count;
}

int coin_combination_2(vector<int> &coins, int idx, int target, string ans)
{
    if(idx==coins.size() || target==0)
    {
        if(target==0)
        {
            cout<<ans<<"\n";
            return 1;
        }
        return 0;
    }
    
    int count = 0;
    if(target-coins[idx]>=0)
        count += coin_combination_2(coins,idx+1,target-coins[idx],ans + to_string(coins[idx]) + " ");
    count += coin_combination_2(coins,idx+1,target,ans);

    return count;
}

int main()
{
    vector <int> coins = {2,3,5,7};
    // cout<<coin_permutation_infi_1(coins,10,"");
    bool vis[coins.size()];
    // cout<<coin_permutation_1(coins,vis,10,"");
    
    // cout<<coin_permutation_infi_2(coins,0,10,"");
    // cout<<coin_combination_infi_2(coins,0,10,"");

    // cout<<coin_permutation_2(coins,vis,0,10,"");
    cout<<coin_combination_2(coins,0,10,"");
    return 0;
}