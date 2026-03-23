#include<iostream>
#include<vector>
using namespace std;

int OffToOn(int num, int k)     //kth bit 0,1,2,....,k
{
    int mask = (1 << k);
    return (mask | num);
}

int OnToOff(int num, int k)
{
    int mask = ~(1 << k);
    return (mask & num);
}

int countSetBits(unsigned int num)
{
    int count = 0;
    while(num>0)
    {
        count += num & 1;
        num >>= 1;
    }
    return count;
}

int countSetBits2(unsigned int num)
{
    int count = 0;
    while(num>0)
    {
        num &= (num-1);
        count++;
    }
    return count;
}

//leetcode 338
vector<int> countBits(int num) 
{
    vector <int> ans;
    for(int i=0;i<=num;i++)
    {
        int count=0,n=i;
        while(n>0)
        {
            count++;
            n &= (n-1);
        }
        ans.push_back(count);
    }        
    return ans;
}

//leetcode 137
int singleNumber2(vector<int> &nums)
{
    int ans;
    for(int i=0;i<32;i++)
    {
        int count = 0;
        int mask = (1<<i);
        for(int ele:nums)
        {
            if((ele & mask) != 0)
                count++;
        }
        if((count % 3) != 0)
            ans |= mask;
    }
    return ans;
}

//leetcode 260
vector<int> singleNumber3(vector<int> &nums)
{
    int xorNum = 0;
    for (int ele : nums)
        xorNum ^= ele;

    int LSB = (xorNum & (-xorNum));
    int a = 0;
    int b = 0;
    for (int ele : nums)
    {
        if ((LSB & ele) != 0)
            a ^= ele;
        else
            b ^= ele;
    }

    return {a, b}; // java: new int[]{a,b};
}

//leetcode 231
bool isPowerOfTwo(int n) 
{
    return n>0 && !(n&(n-1));
}
//leetcode 342
bool isPowerOfFour(int n) 
{
    return (n>0) && !(n&(n-1)) && !((n-1)%3);
}

int findUniqueNum(vector<int> num, int k)
{
    int ans;
    if(k&1)
    {
        int ans;
        for(int i=0;i<32;i++)
        {
            int count = 0;
            int mask = (1<<i);
            for(int ele:num)
            {
                if((ele & mask) != 0)
                    count++;
            }
            if((count % k) == 0)
                ans |= mask;
        }
    }
    else
    {
        for(int i=0;i<num.size();i++)
        {
            ans ^= num[i];     
        }
    }
    return ans;
}

int main()
{
    unsigned int num = 123;
    cout<<countSetBits2(num);
    return 0;
}