#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// https://leetcode.com/problems/remove-duplicates-from-sorted-array/description/
// Using two pointer method
// Time: O(N), Space: O(1)
int removeDuplicates(vector<int>& nums) {
  int j = 1;
  for (int i = 1; i < nums.size(); i++) {
    if (nums[i] != nums[i - 1]) {
      nums[j++] = nums[i];
    }
  }
  return j;
}

// https://leetcode.com/problems/fibonacci-number/
// 1. Using Recursion
// Time: O(2^N), Space: O(N)
int fib1(int n) {
  if (n <= 1) return n;
  return fib1(n - 1) + fib1(n - 2);
}

// 2. Using memoization
// Time: O(N), Space: O(2*N)  // 2*N because of recursion stack
int fib2_(int n, vector<int>& dp) {
  if (n <= 1) return dp[n] = n;

  if (dp[n] != -1) return dp[n];

  int ans = fib2_(n - 1, dp) + fib2_(n - 2, dp);
  return dp[n] = ans;
}

int fib2(int n) {
  vector<int> dp(n + 1, -1);
  return fib2_(n, dp);
}

// 3. Using Dynamic Programming
// Time: O(N), Space: O(N)
int fib3(int n) {
  if (n <= 1) return n;

  vector<int> dp(n + 1);
  dp[0] = 0;
  dp[1] = 1;

  for (int i = 0; i <= n; i++) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }

  return dp[n];
}

// 4. Using space optimized DP or two pointer method
// Time: O(N), Space: O(1)
int fib4(int n) {
  if (n <= 1) return n;

  int a = 0, b = 1;
  for (int i = 2; i <= n; i++) {
    int sum = a + b;
    a = b;
    b = sum;
  }

  return b;
}

// https://leetcode.com/problems/house-robber/
// 1. Using Recursion
// Time: O(2^N), Space: O(N)
int rob1_(vector<int>& nums, int index) {
  if (index >= nums.size()) return 0;

  int ans1 = rob1_(nums, index + 1);
  int ans2 = nums[index] + rob1_(nums, index + 2);

  return max(ans1, ans2);
}

int rob1(vector<int>& nums) { return rob1_(nums, 0); }

// 2. Using memoization
// Time: O(N), Space: O(2*N)  // 2*N because of recursion stack
int rob2_(vector<int>& nums, int index, vector<int>& dp) {
  if (index >= nums.size()) return 0;

  if (dp[index] != -1) return dp[index];

  int ans1 = rob2_(nums, index + 1, dp);
  int ans2 = nums[index] + rob2_(nums, index + 2, dp);

  return dp[index] = max(ans1, ans2);
}

int rob2(vector<int>& nums) {
  vector<int> dp(nums.size(), -1);
  return rob2_(nums, 0, dp);
}

// 3. Using Dynamic Programming
// Time: O(N), Space: O(N)
int rob3(vector<int>& nums) {
  int n = nums.size();
  if (n == 1) return nums[0];

  vector<int> dp(n);
  dp[0] = nums[0];
  dp[1] = max(nums[0], nums[1]);

  for (int i = 2; i < n; i++) {
    dp[i] = max(dp[i - 1], nums[i] + dp[i - 2]);
  }

  return dp[n - 1];
}

// 4. Using space optimized DP or two pointer method
// Time: O(N), Space: O(1)
int rob4(vector<int>& nums) {
  int n = nums.size();
  if (n == 1) return nums[0];

  int a = nums[0], b = max(nums[0], nums[1]);

  for (int i = 2; i < n; i++) {
    int ans = max(b, nums[i] + a);
    a = b;
    b = ans;
  }

  return b;
}

// https://leetcode.com/problems/decode-ways/description/
// 1. Using Recursion
// Time: O(2^N), Space: O(N)
int numDecodings1_(string& s, int i) {
  int n = s.size();
  if (i >= n) return 1;
  if (s[i] == '0') return 0;

  int ans = numDecodings1_(s, i + 1);

  if ((i + 2 <= n) && ((s[i] == '1') || (s[i] == '2' && s[i + 1] <= '6'))) {
    ans += numDecodings1_(s, i + 2);
  }

  return ans;
}

int numDecodings1(string s) { return s.empty() ? 0 : numDecodings1_(s, 0); }

// 2. Using memoization
// Time: O(N), Space: O(2*N)  // 2*N because of recursion stack
int numDecodings2_(string& s, int i, vector<int>& dp) {
  int n = s.size();

  if (dp[i] != -1) return dp[i];
  if (i == n) return dp[i] = 1;
  if (s[i] == '0') return dp[i] = 0;

  int ans = numDecodings2_(s, i + 1, dp);

  if ((i + 2 <= n) && ((s[i] == '1') || (s[i] == '2' && s[i + 1] <= '6'))) {
    ans += numDecodings2_(s, i + 2, dp);
  }

  return dp[i] = ans;
}

int numDecodings2(string s) {
  vector<int> dp(s.size() + 1, -1);
  return s.empty() ? 0 : numDecodings2_(s, 0, dp);
}

// 3. Using Dynamic Programming
// Time: O(N), Space: O(N)
int numDecodings3(string s) {
  if (s.empty() || s[0] == '0') return 0;
  int n = s.size();
  vector<int> dp(n + 1, 0);
  dp[n] = 1;

  for (int i = n - 1; i >= 0; i--) {
    if (s[i] == '0')
      dp[i] = 0;
    else {
      dp[i] = dp[i + 1];
      if ((i + 2 <= n) && ((s[i] == '1') || (s[i] == '2' && s[i + 1] <= '6'))) {
        dp[i] += dp[i + 2];
      }
    }
  }

  return dp[0];
}

// 4. Using space optimized DP or two pointer method
// Time: O(N), Space: O(1)
int numDecodings4(string s) {
  if (s.empty() || s[0] == '0') return 0;
  int n = s.size();
  // lets assume a is pointing to (n+1)th index
  // and b is pointing to n-th index
  int a, b = 1;

  for (int i = n - 1; i >= 0; i--) {
    int ans = (s[i] == '0') ? 0 : b;
    if ((i + 2 <= n) && ((s[i] == '1') || (s[i] == '2' && s[i + 1] <= '6'))) {
      ans += a;
    }
    a = b;
    b = ans;
  }

  return b;
}

// https://leetcode.com/problems/two-sum/
// 1. Brute force approach
// Time: O(N^2), Space: O(1)
vector<int> twoSum1(vector<int>& nums, int target) {
  for (int i = 0; i < nums.size(); i++) {
    for (int j = i + 1; j < nums.size(); j++) {
      if (target == nums[i] + nums[j]) {
        return {i, j};
      }
    }
  }

  return {};
}

// 2. Storing index and value in another vector. Sorting it. Then using two
// pointer method Time: O(N + NlogN + N), Space: O(N)
vector<int> twoSum2(vector<int>& nums, int target) {
  int n = nums.size();
  vector<pair<int, int>> sortedArr(n);
  for (int i = 0; i < n; i++) {
    sortedArr[i] = {i, nums[i]};
  }
  sort(
      sortedArr.begin(), sortedArr.end(),
      [](pair<int, int>& a, pair<int, int>& b) { return a.second < b.second; });

  vector<int> result(2);
  int a = 0, b = n - 1;
  while (a < b) {
    int sum = sortedArr[a].second + sortedArr[b].second;
    if (sum == target) {
      result[0] = sortedArr[a].first;
      result[1] = sortedArr[b].first;
      break;
    } else if (sum > target) {
      --b;
    } else {
      ++a;
    }
  }

  return result;
}

// 3. Using Hash Map - Two pass
// Time: O(N), Space: O(N)
vector<int> twoSum3(vector<int>& nums, int target) {
  int n = nums.size();
  unordered_map<int, int> m;
  for (int i = 0; i < n; i++) {
    m[nums[i]] = i;
  }

  for (int i = 0; i < nums.size(); i++) {
    int val = target - nums[i];
    if (m.count(val) && i != m[val]) {
      return {i, m[val]};
    }
  }

  return {};
}

// 4. Using Hash Map - One pass
// Time: O(N), Space: O(N)
vector<int> twoSum4(vector<int>& nums, int target) {
  int n = nums.size();
  unordered_map<int, int> m;

  for (int i = 0; i < nums.size(); i++) {
    int val = target - nums[i];
    if (m.count(val)) {
      return {i, m[val]};
    }
    m[nums[i]] = i;
  }

  return {};
}

// https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/
// 1. Using two pointer method
// Time: O(N), Space: O(1)
vector<int> twoSum(vector<int>& arr, int target) {
  int a = 0, b = arr.size() - 1;
  while (a < b) {
    int sum = arr[a] + arr[b];
    if (sum == target) {
      return {a + 1, b + 1};
    } else if (sum > target) {
      --b;
    } else {
      ++a;
    }
  }

  return {};
}

// https://leetcode.com/problems/4sum/description/
// 1. Brute force approach. Use 4 loops.
// Time: O(N^4), Space: O(1)
// Not coding it here

// 2.

// https://leetcode.com/problems/container-with-most-water/
// 1. Brute force approach. Calculate area for all possible pairs.
// Time: O(N^2), Space: O(1)

// 2. Two pointer method
// Time: O(N), Space: O(1)
int maxArea(vector<int>& arr) {
  int i = 0, j = arr.size() - 1;
  int maxWater = 0;
  while (i < j) {
    maxWater = max(maxWater, (j - i) * min(arr[i], arr[j]));
    if (arr[i] < arr[j])
      ++i;
    else
      --j;
  }

  return maxWater;
}

// https://leetcode.com/problems/shortest-word-distance-ii/description/

//
//
//
//
//
//
// To do
//
//
//
//
//
//
//
//
//
//

// Leetcode 925: https://leetcode.com/problems/long-pressed-name/
// Solution 1: Two pointer method
// Time: O(N+M), Space: O(1)
bool isLongPressedName(string name, string typed) {
  int n = name.size(), m = typed.size(), i = 0, j = 0;
  if (n > m) return false;

  for (; i < n && j < m; i++, j++) {
    if (name[i] != typed[j]) return false;

    int count_name = 1, count_typed = 1;

    while (i + 1 < n && name[i] == name[i + 1]) {
      ++count_name;
      ++i;
    }

    while (j + 1 < m && typed[j] == typed[j + 1]) {
      ++count_typed;
      ++j;
    }

    if (count_name > count_typed) return false;
  }

  return j == m && i == n;
}

// Leetcode 11: https://leetcode.com/problems/container-with-most-water/
// Solution 1: Two pointer method
// Time: O(N), Space: O(1)
int maxArea(vector<int>& height) {
  int i = 0, j = height.size() - 1, ans = 0;

  while (i < j) {
    ans = max(ans, (j - i) * min(height[i], height[j]));
    if (height[i] < height[j])
      ++i;
    else
      --j;
  }

  return ans;
}

// Leetcode 977: https://leetcode.com/problems/squares-of-a-sorted-array/
// Solution 1: Two pointer method
// Time: O(N), Space: O(1)
int square(int n) { return n * n; }

vector<int> sortedSquares(vector<int>& nums) {
  int n = nums.size(), i = 0, j = n - 1, k = n - 1;
  vector<int> result(n);

  while (i <= j) {
    if (abs(nums[i]) > abs(nums[j])) {
      result[k--] = square(nums[i++]);
    } else {
      result[k--] = square(nums[j--]);
    }
  }

  return result;
}

// Leetcode 169: https://leetcode.com/problems/majority-element/description/
// Solution 1: Hash Map
// Time: O(N), Space: O(N)
int majorityElement1(vector<int>& nums) {
  unordered_map<int, int> m;
  int ans = 0, maxCount = 0;

  for (int n : nums) {
    m[n]++;

    if (m[n] > maxCount) {
      ans = n;
      maxCount = m[n];
    }
  }

  return ans;
}

// Leetcode 169: https://leetcode.com/problems/majority-element/description/
// Solution 2: Boyer-Moore Majority Vote Algorithm
// Time: O(N), Space: O(1)
int majorityElement2(vector<int>& nums) {
  int ans = 0, maxCount = 0;

  for (int n : nums) {
    if (maxCount == 0) {
      ans = n;
    }

    maxCount += (ans == n ? 1 : -1);
  }
f
  return ans;
}

// Leetcode 169: https://leetcode.com/problems/majority-element/description/
// Solution 3: Sorting
// Time: O(N * log(N)), Space: O(1)
int majorityElement3(vector<int>& nums) {
  sort(nums.begin(), nums.end());
  int n = nums.size();
  return nums[n / 2];
}

// Leetcode 229: https://leetcode.com/problems/majority-element-ii/description/
// Solution 1: Hash Map
// Time: O(N), Space: O(N)
vector<int> majorityElement21(vector<int>& nums) {
  int len = nums.size();
  unordered_map<int, int> m;
  vector<int> result;

  for (int n : nums) m[n]++;

  for (pair<int, int> p : m)
    if (p.second > (len / 3)) result.push_back(p.first);

  return result;
}

// Leetcode 229: https://leetcode.com/problems/majority-element-ii/description/
// Solution 2: Boyer-Moore Majority Vote Algorithm
// Time: O(N), Space: O(1)
vector<int> majorityElement22(vector<int>& nums) {
  int len = nums.size(), majority1 = 0, majority2 = 0, count1 = 0, count2 = 0;

  for (int n : nums) {
    if (n == majority1)
      ++count1;
    else if (n == majority2)
      ++count2;
    else if (count1 == 0) {
      majority1 = n;
      ++count1;
    } else if (count2 == 0) {
      majority2 = n;
      ++count2;
    } else {
      --count1;
      --count2;
    }
  }

  count1 = count2 = 0;

  for (int n : nums) {
    if (n == majority1)
      ++count1;
    else if (n == majority2)
      ++count2;
  }

  vector<int> result;
  if (count1 > (len / 3)) result.push_back(majority1);
  if (count2 > (len / 3)) result.push_back(majority2);

  return result;
}
