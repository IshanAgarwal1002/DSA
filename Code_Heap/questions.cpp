#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<unordered_set>

using namespace std;

//leetcode 215
int findKthLargest(vector<int>& nums, int k) {

    priority_queue<int,vector<int>,greater<int>> pq;        //creating a minHeap 
    for(int i:nums)
    {
        pq.push(i);
        if(pq.size()>k)
            pq.pop();
    }
    return pq.top();
}

int findKthSmallest(vector<int>& nums, int k) {

    priority_queue<int> pq;        //creating a maxHeap
    for(int i:nums)
    {
        pq.push(i);
        if(pq.size()>k)
            pq.pop();
    }
    return pq.top();
}

//leetcode 703
class KthLargest {
public:
    priority_queue<int,vector<int>,greater<int>> pq;        //minHeap
    int size;
    KthLargest(int k, vector<int>& nums) {
        size = k;
        for(int i:nums)
        {
            pq.push(i);
            if(pq.size()>k)
                pq.pop();
        }
    }
    
    int add(int val) {
        pq.push(val);
        if(pq.size()>size)
            pq.pop();
        return pq.top();
    }
};

//leetcode 378
int kthSmallest(vector<vector<int>> &matrix, int k)
{
    int m = matrix.size();
    int n = matrix[0].size();

    priority_queue <vector<int>,vector<vector<int>>, greater<vector<int>>> pq;
    for(int i=0;i<m;i++)
        pq.push({matrix[i][0], i, 0});

    for(int i=0;i<k-1;i++)
    {
        vector<int> rEle = pq.top();
        pq.pop();
        if(++rEle[2]<n)
            pq.push({matrix[rEle[1]][rEle[2]], rEle[1], rEle[2]});
    }

    return pq.top()[0];
}

//leetcode 347
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int,int> m;
    for(int i=0;i<nums.size();i++)
        m[nums[i]]++;

    priority_queue <pair<int,int>, vector<pair<int,int>>, greater<pair<int ,int>>> pq;

    for(pair<int,int> p:m)
    {
        pq.push({p.second, p.first});
        if(pq.size()>k)
            pq.pop();
    }

    vector<int> ans;
    while(pq.size()!=0)
    {
        ans.push_back(pq.top().second);
        pq.pop();
    }

    return ans;
}

//leetcode 786
vector<int> kthSmallestPrimeFraction(vector<int>& A, int k) {
    int n = A.size();

    auto comparator = [](pair<int,int> a, pair<int,int> b){return A[a.first]*A[b.second] - A[a.second]*A[b.first]};
    priority_queue <pair<int,int>, vector<pair<int,int>>,decltype(comparator)> pq(comparator);

    for (int i = 1; i < n; i++) 
    {
        pq.push({ 0, i });
    }

    while (k-- > 1) 
    {
        pair<int,int> rvtx = pq.top();
        pq.pop();
        if (++rvtx.first < rvtx.second)
            pq.push({ rvtx.first, rvtx.second });
    }

    pair<int,int> rvtx = pq.top();
    return { rvtx.first, rvtx.second };
}

//leetcode 349
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {

    if(nums1.size()==0 || nums2.size()==0)
        return {};

    unordered_set<int> s(nums1.begin(),nums1.end());
    vector<int> ans;

    for(int i:nums2)
    {
        if(s.count(i))
        {
            ans.push_back(i);
            s.erase(i);
        }
    }

    return ans;
}

//leetcode 350
vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        
    if(nums1.size()==0 || nums2.size()==0)
        return {};
    
    unordered_map<int,int> m;
    vector<int> ans;

    for(int i:nums1)
    {
        m[i]++;
    }

    for(int i:nums2)
    {
        if(m.find(i) != m.end() && m[i] > 0)
        {
            ans.push_back(i);
            m[i]--;
            if(!m[i])   m.erase(i);
        }
    }

    return ans;
}

//leetcode 128
int longestConsecutive(vector<int> &nums)
{
    unordered_map<int, int> m;

    for (int ele : nums)
        m[ele]++;

    int len = 0;
    for (int ele : nums)
    {
        if (m.find(ele) == m.end())
            continue;

        m.erase(ele);
        int prevEle = ele - 1;
        int nextEle = ele + 1;

        while (m.find(prevEle) != m.end())
            m.erase(prevEle--);
        while (m.find(nextEle) != m.end())
            m.erase(nextEle++);

        len = max(len, nextEle - prevEle - 1);
    }

    return len;
}

//https://practice.geeksforgeeks.org/problems/largest-subarray-of-0s-and-1s/1


//https://practice.geeksforgeeks.org/problems/count-subarrays-with-equal-number-of-1s-and-0s/0

//leetcode 49
vector<vector<string>> groupAnagrams(vector<string> &strs)
{
    unordered_map<string, vector<string>> map; // HashMap<String,ArrayList<String>> map=new ..;
    for (string &str : strs)
    {
        vector<int> freq(26, 0);
        for (int i = 0; i < str.length(); i++)
            freq[str[i] - 'a']++;

        string code = "";
        for (int i = 0; i < 26; i++)
            if (freq[i] > 0)
                code += string(1, (char)(i + 'a')) + "" + to_string(freq[i]);

        // for java: map.putIfAbsent(code,new ArrayList<>());
        map[code].push_back(str);
    }

    vector<vector<string>> ans;
    for (auto keys : map)
        ans.push_back(keys.second);

    return ans;
}

//leetcode 380
class RandomizedSet
{
public:
    unordered_map<int, int> map;
    vector<int> list;
    RandomizedSet()
    {
    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val)
    {
        if (map.find(val) != map.end())
            return false;

        list.push_back(val);
        map[val] = list.size() - 1;
        return true;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val)
    {
        if (map.find(val) == map.end())
            return false;

        int index = map[val];
        swap(list[index], list[map.size() - 1]);
        map[list[index]] = index;

        map.erase(val);
        list.pop_back();
        return true;
    }

    /** Get a random element from the set. */
    int getRandom()
    {
        int loc = rand() % list.size();
        return list[loc];
    }
};


//leetcode 295
class MedianFinder {
public:
    priority_queue<int> leftRegion;
    priority_queue<int,vector<int>, greater<int>> rightRegion;
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if(num < leftRegion.top())
            leftRegion.push(num);
        else
            rightRegion.push(num);

        if(leftRegion.size() - rightRegion.size() == 2)
        {
            rightRegion.push(leftRegion.top());
            leftRegion.pop();
        }
        else if(rightRegion.size() > leftRegion.size()){
            leftRegion.push(rightRegion.top());
            rightRegion.pop();
        }
    }
    
    double findMedian() {
        if(leftRegion.size() == rightRegion.size())
            return (leftRegion.size() == 0)? 0 : (leftRegion.top() + rightRegion.top())/2.0;
        else
            return leftRegion.top();
    }
};