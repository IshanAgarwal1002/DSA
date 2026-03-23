#include<iostream>
#include<vector>
#include<stack>
#include<unordered_map>
#include<algorithm>
using namespace std;

//next greater on right
vector<int> ngor(vector<int> &arr)
{
    stack<int> st;
    vector<int> ans(arr.size(),arr.size());     //(size,default value)
    for(int i=0;i<arr.size();i++)
    {
        while(st.size()!=0 && arr[st.top()]<arr[i])     // for smaller replace to '<' to '>'
        {
            ans[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }

    return ans;
}

//next smaller on right
vector<int> nsor(vector<int> &arr)
{
    stack<int> st;
    int n = arr.size();
    vector<int> ans(n,n);

    for(int i=0;i<n;i++)
    {
        while(st.size() != 0 && arr[st.top()] > arr[i])
        {
            ans[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }

    return ans;
}

//next greater on left
vector<int> ngol(vector<int> &arr)
{
    stack<int> st;
    vector<int> ans(arr.size(),-1);     //(size,default value)
    for(int i = arr.size() - 1; i >= 0; i--)
    {
        while(st.size()!=0 && arr[st.top()]<arr[i])     // for smaller replace to '<' to '>'
        {
            ans[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }

    return ans;
}

//next smaller on left
vector<int> nsol(vector<int> &arr)
{
    stack<int> st;
    vector<int> ans(arr.size(), -1);

    for(int i=arr.size() - 1;i>=0;i--)
    {
        while(st.size() != 0 && arr[st.top()] > arr[i])
        {
            ans[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }

    return ans;
}

//leetcode 20 - Valid Parentheses
bool isValid(string s) 
{
    stack<char> st;
    for(int i=0;s[i]!='\0';i++)
    {
        char ch = s[i];

        if(ch == '(' || ch == '{' || ch == '[')
            st.push(ch);
        else
        {
            if(st.size() == 0)      
                return false;
            else if((st.top() == '(' && ch != ')') || (st.top() == '{' && ch != '}') || (st.top() == '[' && ch != ']'))
                return false;
            else
                st.pop();
        }
    }

    return st.size()==0;
}

//leetcode 1021 - Remove Outermost Parentheses
string removeOuterParentheses(string S) {
    string ans = "";
    int count = 0;
    for(int i=0;S[i]!='\0';i++)
    {
        char ch = S[i];
        if(ch == '(' && count++ > 0)    ans += '(';
        if(ch == ')' && count-- > 1)    ans += ')';
    }

    return ans;
}

string removeOuterParentheses(string s) {
    if(s == "") return "";
    string ans="";
    stack<char> st;

    for(int i=0;s[i]!='\0';i++)
    {
        if(s[i] == '(')
        {
            if(st.size() >= 1)  
                ans+=s[i];
            st.push(s[i]);
        }
        else{
            if(st.size() > 1)
                ans+=s[i];
            st.pop();
        }
    }
    return ans;
}

// 496. Next Greater Element I
void ngor(vector<int> &arr, unordered_map<int,int> &ans)
{
    stack<int> st;
    for(int i=0;i<arr.size();i++)
    {
        while((st.size() != 0) && (st.top() < arr[i]))
        {
            ans[st.top()] = arr[i];
            st.pop();
        }
        st.push(arr[i]);
        ans[arr[i]] = -1;
    }
}
    
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    unordered_map<int,int> subAns;
    ngor(nums2, subAns);
    vector<int> ans(nums1.size());
    for(int i=0;i<nums1.size();i++)
    {
        ans[i] = subAns[nums1[i]];
    }
        
    return ans;
}

//leetcode 503 - Next Greater Element II
vector<int> nextGreaterElements(vector<int>& arr) {
    stack<int> st;
    int n = arr.size();
    vector<int> ans(n,-1);
    for(int i=0;i<2*n;i++)
    {
        while(st.size() != 0 && arr[st.top()]<arr[i%n])
        {
            ans[st.top()] = arr[i%n];
            st.pop();
        }

        if(i<n)     st.push(i);
    }
    return ans;
}

//leetcode 901. Online Stock Span
class StockSpanner {
    stack<pair<int,int>> st;  // { index, price }
    int i;
public:
    StockSpanner() {
        st.push({-1,-1});
        i=0;
    }
    
    int next(int price) {
        int ans = 1;
        while(st.top().first != -1 && st.top().second <= price)
        {
            st.pop();
        }
        ans = i - st.top().first;
        st.push({i,price});
        i++;

        return ans;
    }
};

class StockSpanner {
    stack<pair<int, int>> st;   // { price, result }

public:
    StockSpanner() {}

    int next(int price) {
        int res = 1;
        while(!st.empty() && price >= st.top().first) {
            res += st.top().second;
            st.pop();
        }
        st.push({ price, res });
        return res;
    }
};

//leetcode 921  Minimum Add to Make Parentheses Valid
int minAddToMakeValid(string S) {
    int openingBracketsReq = 0, closingBracketsReq = 0;
    for(int i=0;S[i]!='\0';i++)
    {
        if(S[i] == '(')
            closingBracketsReq++;
        else if(closingBracketsReq>0)
            closingBracketsReq--;
        else
            openingBracketsReq++;
    }
    return openingBracketsReq+closingBracketsReq;
}

int minAddToMakeValid(string S) {
        int ob = 0, cb = 0;     //opening bracket, closing bracket
        for(int i=0;S[i] != '\0';i++)
        {
            if(S[i] == '(')
                ob++;
            else if(ob == 0)
                cb++;
            else
                ob--;
        }
        
        return ob+cb;
    }

// Using stack
int minAddToMakeValid(string S) {
        if(S == "") return 0;
        stack<char> st;
        int ans = 0;
        for(int i=0;S[i] != '\0'; i++)
        {
            if(S[i] == '(')
                st.push('(');
            else if(st.size() == 0)
                ++ans;
            else
                st.pop();
        }
        
        return ans+st.size();
    }

//leetcode 1249 Minimum Remove to Make Valid Parentheses
string minRemoveToMakeValid(string s) {
    vector<bool> chk(s.size(), false);
    stack<int> st;
        
    for(int i=0;s[i] != '\0'; i++)
    {
        if(st.size() != 0 && s[i] == ')')
        {
            chk[i] = chk[st.top()] = true;
            st.pop();
        }
        else if(s[i] == '(')
            st.push(i);
        else if(s[i] != ')')
            chk[i] = true;
    }
        
    string ans = "";
    for(int i=0;i<chk.size(); i++)
        if(chk[i])
            ans+=s[i];
        
    return ans;
}

//slightly faster
string minRemoveToMakeValid(string s) {
    vector<bool> chk(s.size(), true);
    stack<int> st;
        
    for(int i=0;s[i] != '\0'; i++)
    {
        if(s[i] == '(')
            st.push(i);
        else if(s[i] == ')' && st.size() == 0)
            chk[i] = false;
        else if(s[i] == ')')
            st.pop();
    }
        
    while(st.size() != 0)
    {
        chk[st.top()] = false;
        st.pop();
    }
        
    string ans = "";
    for(int i=0;i<chk.size(); i++)
        if(chk[i])
            ans+=s[i];
        
    return ans;
}

//no extra space solution
string minRemoveToMakeValid(string str)
{
    int n = str.length();

    stack<int> st;

    for (int i = 0; i < n; i++)
    {
        if (str[i] == ')')
        {
            if (st.size() != 0)
                st.pop();
            else
                str[i] = '*';
        }
        else if (str[i] == '(')
            st.push(i);
    }

    while (st.size() != 0)
    {
        str[st.top()] = '*';
        st.pop();
    }

    string ans = "";
    for (int i = 0; i < n; i++)
    {
        if (str[i] != '*')
            ans += str[i];
    }

    return ans;
}

// 1190. Reverse Substrings Between Each Pair of Parentheses
string reverseParentheses(string s) 
{
    stack<int> st;
        
    for(int i=0;s[i] != '\0'; i++)
    {
        if(s[i] == '(')       
        {
            st.push(i);
        }   
        else if(s[i] == ')')
        {
            reverse( s.begin() + (st.top()+1), s.begin() + i);
            st.pop();
        }

    }

    string ans = "";
    for(int i=0;s[i]!='\0';i++)
    {
        if(s[i] != '(' && s[i] != ')')
            ans+=s[i];
    }

    return ans;
}

//much better solution (using extra O(N) space)
string reverseParentheses(string s) 
{
    int n=s.size();
    vector<int> bracket, pair(n,0);
    for(int i=0;i<n;i++)
    {
        if(s[i]=='(')
        {
            bracket.push_back(i);
        }
        if(s[i]==')')
        {
            int val=bracket.back();
            bracket.pop_back();
            pair[i]=val;
            pair[val]=i;
        }
    }
    string ans="";
    for(int i=0,d=1;i<n;i+=d)
    {
        if(s[i]==')'||s[i]=='(')
        {
            d=-d;
            i=pair[i];
        }
        else
        {
            ans+=s[i];
        }
    }
    return ans;
}

// 735. Asteroid Collision
vector<int> asteroidCollision(vector<int>& asteroids) {
    
    vector<int> st;
    for(int i=0;i<asteroids.size();i++)
    {
        bool flag = true;
        while(!st.empty() && st.back()>0 && asteroids[i]<0)
        {
            if(st.back() < -asteroids[i])
            {
                st.pop_back();
            }
            else 
            {
                if(st.back() == -asteroids[i])
                    st.pop_back();
                flag = false;
                break;
            }
        }
   
        if(flag)
            st.push_back(asteroids[i]);
    }

    return st;
}

//leetcode 32
int longestValidParentheses(string s) {
    int n = s.length();
    stack<int> st;
    st.push(-1);
    int ans = 0;
    for(int i=0;i<n;i++)
    {
        if(st.top()!=-1 && s[i] == ')' && s[st.top()] == '(')
        {
            st.pop();
            ans = max(ans,i-st.top());
        }
        else
            st.push(i);
    }
    return ans;
}

//leetcode 84
int largestRectangleArea(vector<int>& heights) {
    vector<int> nsorA = nsor(heights);
    vector<int> nsolA = nsol(heights);
        
    int ans = 0;
    for(int i=0;i<heights.size();i++)
    {
        int width = nsorA[i] - nsolA[i] - 1;
        ans = max(ans, width*heights[i]);
    }
        
    return ans;
}

//better solution
int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    stack<int> st;
    st.push(-1);
    int maxArea = 0;
    for(int i=0;i<n;i++)
    {
        while(st.top() != -1 && heights[st.top()] >= heights[i])
        {
            int height = heights[st.top()];
            st.pop();
            int area = height * (i - st.top() - 1);
            maxArea = max(area,maxArea);
        }
        st.push(i);
    }

    while(st.top()!=-1)
    {
        int height = heights[st.top()];
        st.pop();
        int area = height * (n - st.top() - 1);
        maxArea = max(area,maxArea);
    }
    return maxArea;
}

//if you had to return the maxArea, left bound, right bound, height too
vector<int> largestRectangleArea_better(vector<int>& heights) {
    int n = heights.size();

    stack<int> st;
    st.push(-1);
    int lb=0,rb=0,h=0, maxArea=0;

    for(int i=0;i<n;i++)
    {
        while(st.top()!=-1 && heights[st.top()] >= heights[i])
        {
            int height = heights[st.top()];
            st.pop();
            int area = height* (i-st.top()-1);
            if(area > maxArea)
            {
                maxArea = area;
                lb = st.top()+1;
                rb = i-1;
                h = height;
            }
        }
        st.push(i);
    }

    while(st.top()!=-1)
    {
        int height = heights[st.top()];
        st.pop();
        int area = height* (n-st.top()-1);
        if(area > maxArea)
        {
            maxArea = area;
            lb = st.top()+1;
            rb = n-1;
            h = height;
        }
    }

    return {maxArea, lb, rb, h};
}

// leetcode 85. Maximal Rectangle
int maximalRectangle(vector<vector<char>>& matrix) 
{
    if(matrix.size() == 0 || matrix[0].size() == 0)
        return 0;
    
    int n = matrix.size();
    int m = matrix[0].size();

    vector<int> heights(m,0);
    int maxArea = 0;
    for(int r=0;r<n;r++)
    {
        for(int c=0;c<m;c++)
        {
            if(matrix[r][c] == '1')
                heights[c] += 1;
            else
                heights[c] = 0;
        }

        int area = largestRectangleArea(heights);
        if(area > maxArea)    maxArea = area;
    }        

    return maxArea;
}

// leetcode 42. Trapping Rain Water

//Time: 3*O(N), Space: 2*O(N)
int trap(vector<int>& height) {
    int n = height.size();
    vector<int> gol(n);     // greatest upto ith index
    vector<int> gor(n);     // greatest upto ith index from right

    int prev = 0;
    for(int i=0;i<n;i++)
    {
        gol[i] = max(prev, height[i]);
        prev = gol[i];
    }

    prev = 0;
    for(int i=n-1;i>=0;i--)
    {
        gor[i] = max(prev, height[i]);
        prev = gor[i];
    }

    int ans = 0;
    for(int i=0;i<n;i++)
    {
        ans += (min(gol[i], gor[i]) - height[i]);
    }

    return ans;
}

//Time: O(N), Space: O(N)
int trap_2(vector<int>& height) {
    int n = height.size();
    stack<int> st;

    int water = 0;
    for(int i=0;i<n;i++)
    {
        while(!st.empty() && height[i] >= height[st.top()])
        {
            int h = height[st.top()];
            st.pop();

            if(st.empty())
                break;

            int width = i - st.top() - 1;
            water += width*(min(height[i], height[st.top()]) - h);
        }
        st.push(i);
    }

    return water;
}

//two pointer approach - Time: O(N), Space: O(1)
int trap_3(vector<int>& height) {
    int li = 0, ri = height.size()-1;
    int lMaxBH = 0, rMaxBH = 0;     //left max bar height, right max bar height
    int water = 0;
    while(li<=ri)
    {
        lMaxBH = max(lMaxBH, height[li]);
        rMaxBH = max(rMaxBH, height[ri]);

        water += (lMaxBH <= rMaxBH)?(lMaxBH - height[li++]):(rMaxBH - height[ri--]);
    }        

    return water;
}

//leetcode 155. Min Stack
class MinStack {
    stack<long> st;
    long Min;
public:
    /** initialize your data structure here. */
    MinStack() {
        Min = 0;
    }
    
    void push(int val) {
        if(st.empty())
        {
            Min = val;
            st.push(val);
            return;
        }

        if(val < Min)
        {
            st.push(2*(long)val - Min);
            Min = val;
        }
        else
            st.push(val);
    }
    
    void pop() {
        if(st.top() < Min)
        {
            Min = 2*Min - st.top();
        }
        st.pop();
    }
    
    int top() {
        if(st.top() < Min)
            return (int)Min;
        return (int)st.top();
    }
    
    int getMin() {
        return (int)Min;
    }
};

// leetcode 946. Validate Stack Sequences
bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
    stack<int> st;

    int i=0;
    for(int ele:pushed)
    {
        st.push(ele);
        while(!st.empty() && st.top() == popped[i])
        {
            st.pop();
            i++;
        }
    }        

    return st.empty();
}

// leetcode 402. Remove K Digits
string removeKdigits(string num, int k) {
    if(num.size() == 0)
        return "0";

    string st;
    for(char i:num)
    {
        while(st.size() != 0 && k>0 && st.back()>i)
        {
            st.pop_back();
            --k;
        }
        st.push_back(i);
    }

    while(k--)
        st.pop_back();

    int i=0;
    while(st[i] == '0')
        ++i;

    return (st.size() - i == 0)?"0":st.substr(i);
}

//leetcode 316. Remove Duplicate Letters
string removeDuplicateLetters(string s) {
    if(s.empty())   return s;

    vector<int> freq(26,0);
    vector<bool> seen(26,false);

    for(char i:s)
    {
        freq[i-'a']++;
    }

    string st = "0";

    for(char i:s)
    {
        freq[i-'a']--;
        
        if(seen[i-'a']) continue;

        while(st.back() > i && freq[st.back() - 'a'] > 0)
        {
            seen[st.back() - 'a'] = false;
            st.pop_back();
        }

        seen[i-'a'] = true;
        st.push_back(i);
    }

    return st.substr(1);
}