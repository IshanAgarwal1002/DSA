import java.util.AbstractMap.SimpleEntry;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Deque;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;
import java.util.List;
import java.util.Map;
import java.util.Stack;

import util.Utility;

class Solution {

  class Pair<K, V> extends SimpleEntry<K, V> {

    public Pair(K key, V value) {
      super(key, value);
    }
  }

  // Leetcode 1: https://leetcode.com/problems/two-sum/
  public int[] twoSum(int[] nums, int target) {
    ArrayList<Pair<Integer, Integer>> sortedArr = new ArrayList<>();
    for (int i = 0; i < nums.length; i++) {
      sortedArr.add(new Pair(i, nums[i]));
    }
    sortedArr.sort((a, b) -> a.getValue() - b.getValue());

    int[] result = new int[2];
    int a = 0, b = nums.length - 1;
    while (a < b) {
      int sum = sortedArr.get(a).getValue() + sortedArr.get(b).getValue();
      if (sum == target) {
        result[0] = sortedArr.get(a).getKey();
        result[1] = sortedArr.get(b).getKey();
        break;
      } else if (sum > target) {
        --b;
      } else {
        ++a;
      }
    }

    return result;
  }

  // Leetcode 925: https://leetcode.com/problems/long-pressed-name/
  // Solution 1: Two pointer method
  // Time: O(N+M), Space: O(1)
  public static boolean isLongPressedName(String name, String typed) {
    int i = 0, j = 0, n = name.length(), m = typed.length();

    if (n > m)
      return false;

    while (i < n && j < m) {
      if (name.charAt(i) == typed.charAt(j)) {
        ++i;
        ++j;
      } else if (j >= 1 && typed.charAt(j) == typed.charAt(j - 1)) {
        ++j;
      } else {
        return false;
      }
    }

    while (j < m && typed.charAt(j) == typed.charAt(j - 1))
      ++j;

    return i == n && j == m;
  }

  // Leetcode 11: https://leetcode.com/problems/container-with-most-water/
  // Solution 1: Two pointer method
  // Time: O(N), Space: O(1)
  public static int maxArea(int[] height) {
    int i = 0, j = height.length - 1, ans = 0;

    while (i < j) {
      ans = Math.max(ans, (j - i) * Math.min(height[i], height[j]));
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
  public static int square(int n) {
    return n * n;
  }

  public static int[] sortedSquares(int[] nums) {
    int n = nums.length, i = 0, j = n - 1, k = n - 1;
    int[] result = new int[n];

    while (i <= j) {
      if (Math.abs(nums[i]) > Math.abs(nums[j])) {
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
  public static int majorityElement1(int[] nums) {
    HashMap<Integer, Integer> m = new HashMap<>();
    int ans = 0, maxCount = 0;

    for (int n : nums) {
      m.put(n, m.getOrDefault(n, 0) + 1);

      if (m.get(n) > maxCount) {
        ans = n;
        maxCount = m.get(n);
      }
    }

    return ans;
  }

  // Leetcode 169: https://leetcode.com/problems/majority-element/description/
  // Solution 2: Boyer-Moore Majority Vote Algorithm
  // Time: O(N), Space: O(1)
  public static int majorityElement2(int[] nums) {
    int ans = 0, maxCount = 0;

    for (int n : nums) {
      if (maxCount == 0) {
        ans = n;
      }

      maxCount += (ans == n ? 1 : -1);
    }

    return ans;
  }

  // Leetcode 169: https://leetcode.com/problems/majority-element/description/
  // Solution 3: Sorting
  // Time: O(N * log(N)), Space: O(1)
  public static int majorityElement3(int[] nums) {
    Arrays.sort(nums);
    int n = nums.length;
    return nums[n / 2];
  }

  // Leetcode 229: https://leetcode.com/problems/majority-element-ii/description/
  // Solution 1: Hash Map
  // Time: O(N), Space: O(N)
  public static List<Integer> majorityElement21(int[] nums) {
    HashMap<Integer, Integer> m = new HashMap<>();

    for (int n : nums) {
      m.put(n, m.getOrDefault(n, 0) + 1);
    }

    List<Integer> result = new ArrayList<>();
    for (HashMap.Entry<Integer, Integer> p : m.entrySet()) {
      if (p.getValue() > (nums.length / 3))
        result.add(p.getKey());
    }

    return result;
  }

  // Leetcode 229: https://leetcode.com/problems/majority-element-ii/description/
  // Solution 2: Boyer-Moore Majority Vote Algorithm
  // Time: O(N), Space: O(1)
  public static List<Integer> majorityElement22(int[] nums) {
    int len = nums.length, majority1 = 0, majority2 = 0, count1 = 0, count2 = 0;

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

    List<Integer> result = new ArrayList<>();
    if (count1 > (len / 3))
      result.add(majority1);
    if (count2 > (len / 3))
      result.add(majority2);

    return result;
  }

  // GFG: https://www.geeksforgeeks.org/dsa/given-an-array-of-of-size-n-finds-all-the-elements-that-appear-more-than-nk-times/
  // Solution 1: Hash Map
  // Time: O(N), Space: O(N)
  public static int countOccurence(int[] arr, int k) {
    // compute array size and frequency threshold
    int n = arr.length;
    int x = n / k;

    // store frequency of each element
    HashMap<Integer, Integer> freq = new HashMap<>();
    for (int num : arr)
      freq.put(num, freq.getOrDefault(num, 0) + 1);

    // count elements whose frequency exceeds n/k
    int count = 0;
    for (HashMap.Entry<Integer, Integer> e : freq.entrySet())
      if (e.getValue() > x)
        count++;

    // return the final count
    return count;
  }

  // GFG: https://www.geeksforgeeks.org/dsa/given-an-array-of-of-size-n-finds-all-the-elements-that-appear-more-than-nk-times/
  // Solution 2: Boyer-Moore Majority Vote Algorithm
  // Time: O(N * K), Space: O(k)
  static class EleCount {
    int e; // Element
    int c; // Count
  }

  public static void moreThanNdK(int[] arr, int k) {
    int n = arr.length;

    // k must be greater than 1 to get some output
    if (k < 2)
      return;

    // Step 1: Create a temporary array (contains element and count) of size k-1.
    // Initialize count of all elements as 0
    EleCount[] temp = new EleCount[k - 1];
    for (int i = 0; i < k - 1; i++) {
      temp[i] = new EleCount();
      temp[i].e = 0;
      temp[i].c = 0;
    }

    // Step 2: Process all elements of input array
    for (int i = 0; i < n; i++) {
      int j;

      // If arr[i] is already present in the temp array, then increment its count
      for (j = 0; j < k - 1; j++) {
        if (temp[j].e == arr[i]) {
          temp[j].c += 1;
          break;
        }
      }

      // If arr[i] is not present in temp[]
      if (j == k - 1) {
        int l;

        // If there is position available in temp[], then place arr[i] in the first
        // available position and set count as 1
        for (l = 0; l < k - 1; l++) {
          if (temp[l].c == 0) {
            temp[l].e = arr[i];
            temp[l].c = 1;
            break;
          }
        }

        // If all the position in the temp[] are filled, then decrease count of every
        // element by 1
        if (l == k - 1) {
          for (l = 0; l < k - 1; l++) {
            temp[l].c -= 1;
          }
        }
      }
    }

    // Step 3: Check actual counts of potential candidates in temp[]
    for (int i = 0; i < k - 1; i++) {
      // Calculate actual count of elements
      int ac = 0; // actual count
      for (int j = 0; j < n; j++) {
        if (arr[j] == temp[i].e)
          ac++;
      }

      // If actual count is more than n/k, then print it
      if (ac > n / k) {
        System.out.println("Number: " + temp[i].e
            + " Count: " + ac);
      }
    }
  }

  // Leetcode 556: https://leetcode.com/problems/next-greater-element-iii/description/
  // GFG: https://www.geeksforgeeks.org/dsa/find-next-greater-number-set-digits/
  // Solution 1: 
  // Time: O(d), Space: O(d)
  // Explanation:
  // d = number of digits in n (at most 10 for 32-bit integer)
  // Visual Summary:
  // ------------------------------------------------
  // | Step |	Operation	                    | Time  |
  // | 1    | Convert int to char array	    | O(d)  |
  // | 2    | Find pivot from right to left | O(d)  |
  // | 3    | Swap characters	              | O(d)  |
  // | 4    | Swap characters	              | O(1)  |
  // | 5    | Reverse subarray	            | O(d)  |
  // | 6    | Parse back to int	            | O(d)  |
  // ------------------------------------------------
  // Total Time Complexity:	O(d)
  // Total Space Complexity: O(d) for the char array storage
  public static void swap(char[] arr, int i, int j) {
    char temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }

  public static void reverse(char[] arr, int i, int j) {
    while (i < j) {
      swap(arr, i++, j--);
    }
  }

  public static int nextGreaterElement(int n) {
    // Convert int to char array
    char[] numArray = Integer.toString(n).toCharArray();
    int length = numArray.length;
    int i = length - 1, j = length - 1;

    // Find pivot from right to left
    while(i>0) {
      if (numArray[i-1] >= numArray[i]) {
        --i;
      } else {
        break;
      }
    }

    // n is something like 4321
    if (i == 0) return -1;

    // find index of smallest number greater than number at index i-1
    while (j >= i && numArray[i-1] >= numArray[j]) {
      --j;
    }

    // swap char at i-1 and j
    swap(numArray, i-1, j);

    // reverse from i to last
    reverse(numArray, i, length - 1);

    int result;
    try {
      // Parse back to int
      result = Integer.parseInt(new String(numArray));
    } catch (NumberFormatException e) {
      return -1;
    }

    return result;
  }

  // Leetcode 628: https://leetcode.com/problems/maximum-product-of-three-numbers/
  // Solution 1: Sorting
  // Time: O(N * log(N)), Space: O(1)
  public static int maximumProduct(int[] nums) {
    int n = nums.length;
    Arrays.sort(nums);
    int result = Math.max(nums[0]*nums[1]*nums[n-1], nums[n-1]*nums[n-2]*nums[n-3]);
    return result;
  }

  // Leetcode 628: https://leetcode.com/problems/maximum-product-of-three-numbers/
  // Solution 2: Find 3 highest positive and 2 lowest negative
  // Time: O(N), Space: O(1)
  public static int maximumProduct2(int[] nums) {
    int max1 = Integer.MIN_VALUE, max2 = Integer.MIN_VALUE, max3 = Integer.MIN_VALUE;
    int min1 = Integer.MAX_VALUE, min2 = Integer.MAX_VALUE;
    for (int n: nums) {
      if (n > max1) {
        max3 = max2;
        max2 = max1;
        max1 = n;
      } else if (n > max2) {
        max3 = max2;
        max2 = n;
      } else if (n > max3) {
        max3 = n;
      }

      if (n < min1) {
        min2 = min1;
        min1 = n;
      } else if (n < min2) {
        min2 = n;
      }
    }
    int result = Math.max(min1*min2*max1, max3*max2*max1);
    return result;
  }

  // Leetcode 747: https://leetcode.com/problems/largest-number-at-least-twice-of-others/description/
  // Solution 1: Find max and check the condition
  // Time: O(N), Space: O(1)
  public static int dominantIndex(int[] nums) {
    int max = 0;
    for (int i=1; i<nums.length; i++) {
      if (nums[i] > nums[max])  max = i;
    }

    for (int i=0; i<nums.length; i++) {
      if (i != max && nums[max] < (2*nums[i])) {
        return -1;
      }
    }

    return max;
  }
 
  // Leetcode 747: https://leetcode.com/problems/largest-number-at-least-twice-of-others/description/
  // Solution 2: Find max and secondMax
  // Time: O(N), Space: O(1)
  public static int dominantIndex2(int[] nums) {
    int max = -1, secondMax = -1, index = -1;
    for (int i=0; i<nums.length; i++) {
      if (nums[i] > max) {
        secondMax = max;
        max = nums[i];
        index = i;
      } else if (nums[i] > secondMax) {
        secondMax = nums[i];
      }
    }

    return max >= (secondMax*2) ? index : -1;
  }

  // Leetcode 769: https://leetcode.com/problems/max-chunks-to-make-sorted/
  // Solution 1: https://leetcode.com/problems/max-chunks-to-make-sorted/solutions/113528/simple-java-on-solution-with-detailed-ex-bl3v/
  // Time: O(N), Space: O(1)
  public static int maxChunksToSorted(int[] arr) {
    int result = 0, max = -1;

    for (int i=0; i<arr.length; i++) {
      max = Math.max(max, arr[i]);
      if (max == i) {
        ++result;
      }
    }

    return result;
  }

  // Leetcode 768: https://leetcode.com/problems/max-chunks-to-make-sorted-ii/
  // Solution 1: Prefix Sum
  // Time: O(N * log(N)), Space: O(N)
  public static int maxChunksToSorted21(int[] arr) {
    int[] sortedArr = arr.clone();  // O(N)
    Arrays.sort(sortedArr); // O(N * log(N))
    
    int result = 0, sum1 = 0, sum2 = 0;
    for (int i=0;i <arr.length;i++) {  // O(N)
      sum1 += arr[i];
      sum2 += sortedArr[i];
      if (sum1 == sum2) ++result;
    }

    return result;
  }

  // Leetcode 768: https://leetcode.com/problems/max-chunks-to-make-sorted-ii/
  // Solution 2: https://leetcode.com/problems/max-chunks-to-make-sorted-ii/solutions/595713/monotonic-stack-solution-with-detailed-e-kpf5/
  // Time: O(N), Space: O(N)
  public static int maxChunksToSorted22(int[] arr) {
    Stack<Integer> st = new Stack<>();
    for (int n:arr) {
      int largestInChunk = n;
      while(!st.isEmpty() && st.peek() > n) {
        largestInChunk = Math.max(largestInChunk, st.pop());
      }
      st.push(largestInChunk);
    }

    return st.size();
  }

  // Leetcode 795: https://leetcode.com/problems/number-of-subarrays-with-bounded-maximum/
  // Solution 1: https://leetcode.com/problems/number-of-subarrays-with-bounded-maximum/solutions/1117122/java-explained-solution-o1-space-2-point-yuzd/
  // Time: O(N), Space: O(1)
  public static int numSubarrayBoundedMax(int[] nums, int left, int right) {
    int i = 0, j = 0, result = 0, prevSubarrayCount = 0;

    while (i < nums.length) {
      if (nums[i] >= left && nums[i] <= right) {
        prevSubarrayCount = i - j + 1;
        result += prevSubarrayCount;
      } else if (nums[i] < left) {
        result += prevSubarrayCount;
      } else {
        j = i+1;
        prevSubarrayCount = 0;
      }
      ++i;
    }

    return result;
  }

  // Leetcode 795: https://leetcode.com/problems/number-of-subarrays-with-bounded-maximum/
  // Solution 2: https://algo.monster/liteproblems/795
  // Time: O(N), Space: O(1)
  /**
   * Counts the number of subarrays where the maximum element is within the range [left, right].
   * Uses the principle: subarrays with max in [left, right] = 
   * subarrays with max ≤ right - subarrays with max ≤ (left - 1)
   */
  public static int numSubarrayBoundedMax2(int[] nums, int left, int right) {
    // Count subarrays with max ≤ right minus subarrays with max ≤ (left - 1)
    return countSubarraysWithMaxAtMost(nums, right) - countSubarraysWithMaxAtMost(nums, left - 1);
  }

  /**
   * Counts the number of subarrays where all elements are at most the given threshold.
   * 
   * @param nums The input array
   * @param threshold The maximum allowed value for all elements in counted subarrays
   * @return The count of subarrays where all elements are ≤ threshold
   */
  private static int countSubarraysWithMaxAtMost(int[] nums, int threshold) {
    int totalCount = 0;
    int currentValidLength = 0;
  
    for (int currentValue : nums) {
      if (currentValue > threshold) {
        // Reset the valid subarray length when encountering a value exceeding threshold
        currentValidLength = 0;
      } else {
        // Extend the current valid subarray
        currentValidLength++;
      }
    
      // Add the number of valid subarrays ending at current position
      totalCount += currentValidLength;
    }
  
    return totalCount;
  }

  // Leetcode 280: https://www.lintcode.com/problem/508/
  // Solution 1: Sorting and swapping
  // Time: O(N * log(N)), Space: O(1)
  public static void wiggleSort(int[] nums) {
    Arrays.sort(nums);
    for (int i=2; i<nums.length;i+=2) {
      int temp = nums[i-1];
      nums[i-1] = nums[i];
      nums[i] = temp;
    }
    Utility.print("nums", nums);
  }

  // Leetcode 280: https://www.lintcode.com/problem/508/
  // Solution 2: Greedy approach
  // Time: O(N), Space: O(1)
  public static void swap(int[] arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }

  public static void wiggleSort2(int[] nums) {
    for (int i=1; i<nums.length;i++) {
      if (
        // odd index & condition violation
        ((i & 1) == 1 && nums[i-1] > nums[i]) ||
        // even index & condition violation
        ((i & 1) == 0 && nums[i-1] < nums[i])
      ) {
        swap(nums, i-1, i);
      }
    }
    Utility.print("nums", nums);
  }

  // Leetcode 345: https://leetcode.com/problems/reverse-vowels-of-a-string/
  // Solution 1: Two pointer
  // Time: O(N), Space: O(1)
  public static String reverseVowels(String s) {
    Set<Character> set = Set.of('a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U');
    int n = s.length(), i = 0, j = n-1;
    char[] arr = s.toCharArray();
    
    while (i<j) {
      while (i<=j && !set.contains(arr[i])) {
        ++i;
      }

      while (j>i && !set.contains(arr[j])) {
        --j;
      }

      if (i<j) {
        char temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        ++i;
        --j;
      }
    }

    return new String(arr);
  }

  // Leetcode 238: https://leetcode.com/problems/product-of-array-except-self/
  // Solution: https://leetcode.com/problems/product-of-array-except-self/solutions/1342916/3-minute-read-mimicking-an-interview-by-1fpyp/
  // 4 approaches in above solution. Check all. Coding the best here.
  // Time: O(N), Space: O(1)
  public static int[] productExceptSelf(int[] nums) {
    int n = nums.length;
    int[] ans = new int[n];

    int curr = 1; // prefix
    for (int i=0; i<n; i++) {
      ans[i] = curr;
      curr *= nums[i];
    }

    curr = 1; // suffix
    for (int i=n-1; i>=0; i--) {
      ans[i] *= curr;
      curr *= nums[i];
    }

    return ans;
  }

  // Leetcode 849: https://leetcode.com/problems/maximize-distance-to-closest-person/
  // Solution 1: Two pointer
  // Time: O(N), Space: O(1)
  public static int maxDistToClosest(int[] seats) {
    int prev = -1, i = 0, ans = 0;
    
    while(i < seats.length) {
      if (seats[i] == 0) {
        ++i;
        continue;
      }

      if (prev == -1) {
        ans = i;
      } else {
        ans = Math.max(ans, (int)Math.ceil((i - prev)/2));
      }

      prev = i;
      ++i;
    }

    ans = Math.max(ans, i - 1 - prev);
    
    return ans;
  }

  // Leetcode 41: https://leetcode.com/problems/first-missing-positive/description/
  // Solution 1: Use set and then find ans
  // Time: O(N), Space: O(N)

  // Leetcode 41: https://leetcode.com/problems/first-missing-positive/description/
  // Solution 2: Sort and then find ans
  // Time: O(N*log(N)), Space: O(1)

  // Leetcode 41: https://leetcode.com/problems/first-missing-positive/description/
  // Solution 3: https://leetcode.com/problems/first-missing-positive/solutions/5694826/video-use-index-to-count-numbers-by-niit-kgax/
  // Time: O(N), Space: O(1)
  public static int firstMissingPositive(int[] nums) {
    int n = nums.length;
    
    for (int i=0; i<n; i++) {
      if (nums[i] <= 0 || nums[i] > n) {
        nums[i] = n+1;
      }
    }

    for (int i=0; i<n; i++) {
      int index = Math.abs(nums[i]) - 1;
      if (index < n && nums[index] > 0)
        nums[index] = -nums[index];
    }

    int ans = n+1;
    for (int i=0; i<n; i++) {
      if (nums[i] > 0) {
        ans = i+1;
        break;
      }
    }

    return ans;
  }

  // Leetcode 370: https://www.lintcode.com/problem/903/
  // Solution 1: Brute force
  // Time: O(k * n), Space: O(n)

  // Leetcode 370: https://www.lintcode.com/problem/903/
  // Solution 2: Prefix Sum (Difference array technique)
  // Time: O(k + n), Space: O(n) 
  // k = number of updates
  // n = length of result array
  public static int[] getModifiedArray(int length, int[][] updates) {
    int[] result = new int[length];

    for (int i=0; i<updates.length; i++) {
      int start = updates[i][0];
      int end = updates[i][1];
      int value = updates[i][2];

      result[start] += value;
      if (end + 1 < length)
        result[end + 1] += -value;
    }

    for (int i=1; i<length; i++) {
      result[i] += result[i-1];
    }
 
    return result;
  }

  // Leetcode 296: https://algo.monster/liteproblems/296
  // Solution 1: Brute force
  // Time: O(k * m * n), Space: O(k)
  // where k = total number of friends in grid
  //       m * n = total cells in grid 

  // Leetcode 296: https://algo.monster/liteproblems/296
  // Solution 2: Using Median
  // Time: O(m*n + k*log(k)), Space: O(k)
  // where k = total number of friends in grid
  //       m * n = total cells in grid 
  public static int getTotalDistance(List<Integer> positions, int target) {
    int result = 0, n = positions.size();
    for (int i=0; i<n; i++) {
      result += Math.abs(positions.get(i) - target);
    }
    return result;
  }

  public static int minTotalDistance(int[][] grid) {
    int m = grid.length;
    int n = grid[0].length;

    List<Integer> rows = new ArrayList<>();
    List<Integer> cols = new ArrayList<>();

    for (int i=0; i<m; i++) {
      for (int j=0; j<n; j++) {
        if (grid[i][j] == 1) {
          rows.add(i);
          cols.add(j);
        }
      }
    }

    Collections.sort(cols);

    int medianRow = rows.get(rows.size() >> 1);
    int medianColumn = cols.get(cols.size() >> 1);

    return getTotalDistance(rows, medianRow) + getTotalDistance(cols, medianColumn);
  }

  // Leetcode 462: https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/description/
  // Solution 1: Using median
  // Time: O(n * log(n)), Space: O(1)
  public static int minMoves2(int[] nums) {
    int result = 0;

    Arrays.sort(nums);
    int median = nums[nums.length / 2];

    for (int i=0; i<nums.length; i++) {
      result += Math.abs(nums[i] - median);
    }

    return result;
  }

  // Leetcode 462: https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/description/
  // Solution 2: Using two pointer
  // Time: O(n * log(n)), Space: O(1)
  public static int minMoves22(int[] nums) {
    int result = 0, n = nums.length;

    Arrays.sort(nums);

    for (int i = 0; i < n / 2; i++) {
      result += Math.abs(nums[n - i - 1] - nums[i]);
    }

    return result;
  }

  // Leetcode 462: https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/description/
  // Solution 3: https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/solutions/2215732/c-3-approaches-full-explanation-by-tltan-rrpm/
  // Time: O(n), Space: O(1)
  // Java does not have direct equivalent of C++'s std::nth_element which partially sorts a collection 
  // so that the element at the position is what it would be in a fully sorted collection

  // Leetcode 905: https://leetcode.com/problems/sort-array-by-parity/description/
  // Solution 1: Two pointer
  // Time: O(n), Space: O(1)
  public static int[] sortArrayByParity(int[] nums) {
    int i = 0, j = nums.length - 1;

    while (i < j) {
      // even
      if((nums[i] & 1) == 0) {
        ++i;
      }
      // odd 
      else if((nums[j] & 1) == 1) {
        --j;
      } else {
        swap(nums, i, j);
        ++i;
        --j;
      }
    }

    return nums;
  }

  // Leetcode 670: https://leetcode.com/problems/maximum-swap/description/
  // Solution 1: Brute force
  // Time: O(d^2), Space: O(1)
  // d = total digits in num

  // Leetcode 670: https://leetcode.com/problems/maximum-swap/description/
  // Solution 2: Use stack
  // Time: O(d) or O(log(N)), Space: O(d)
  static class CustomPair {
    public char a;
    public int b;
    public CustomPair(char a, int b) {
      this.a = a;
      this.b = b;
    }
  }

  public static int maximumSwap(int num) {
    Deque<CustomPair> stack = new ArrayDeque<>();

    char[] arr = Integer.toString(num).toCharArray();

    for(int i=arr.length - 1; i>0; i--) {
      if (stack.isEmpty() || (stack.peek().a < arr[i])) {
        stack.push(new CustomPair(arr[i], i));
      }
    }

    for (int i=0; i < arr.length-1; i++) {
      if (stack.isEmpty())  break;

      CustomPair pair = stack.peek();
      if (pair.b == i) stack.pop();

      if (pair.a > arr[i]) {
        swap(arr, pair.b, i);
        return Integer.parseInt(new String(arr));
      }
    }

    return num;
  }

  // GFG: http://geeksforgeeks.org/dsa/minimum-number-platforms-required-railwaybus-station/
  // Solution 1: 
  // Time: O(N * log(N)), Space: O(1)
  public static int minPlatform(int[] arr, int[] dep) {
    int n = arr.length;
    int res = 0;

    Arrays.sort(arr);
    Arrays.sort(dep);

    int count = 1;
    int i = 1, j = 0;

    // Similar to merge in merge sort to process  all events in sorted order
    while (i < n && j < n) {

        // If next event in sorted order is arrival, increment count of platforms needed
        if (arr[i] <= dep[j]) {
            count++;
            i++;
        }
        // Else decrement count of platforms needed
        else if (arr[i] > dep[j]) {
            count--;
            j++;
        }

        // Update result if needed
        res = Math.max(res, count);
    }

    return res;
  }
  
  // GFG: https://www.geeksforgeeks.org/dsa/sieve-of-eratosthenes/
  // Solution 1:
  // Time: O(n*log(log(n))), Space: O(n)
  public static int[] sieve(int n) {
    boolean[] prime = new boolean[n + 1];
    for (int i = 0; i <= n; i++) {
      prime[i] = true;
    }

    for (int p = 2; p * p <= n; p++) {
      if (prime[p]) {
        // marking as false
        for (int i = p * p; i <= n; i += p)
          prime[i] = false;
      }
    }

    // Count number of primes
    int count = 0;
    for (int p = 2; p <= n; p++) {
      if (prime[p])
        count++;
    }

    // Store primes in an array
    int[] res = new int[count];
    int index = 0;
    for (int p = 2; p <= n; p++) {
      if (prime[p])
        res[index++] = p;
    }

    return res;
  }

  // SPOJ: https://www.spoj.com/problems/PRIME1/cstart=10
  // Solution 1:
  // Time: O(n*log(log(n))), Space: O(n)

  // GFG: https://www.geeksforgeeks.org/dsa/check-if-pair-with-given-sum-exists-in-array/
  // Solution 1: Generating all Possible Pairs - O(n^2) time and O(1) space
  // Solution 2: Sorting and Binary Search - O(n * log(n)) time and O(1) space
  // Solution 3: Sorting and Two-Pointer Technique - O(n * log(n)) time and O(1) space
  // Solution 4: Using Hash Set - O(n) time and O(n) space

  // GFG: https://www.geeksforgeeks.org/dsa/find-a-pair-with-the-given-difference/
  // Solution 1: Generating all Possible Pairs - O(n^2) time and O(1) space
  // Solution 2: Sorting and Binary Search - O(n * log(n)) time and O(1) space
  // Solution 3: Sorting and Two-Pointer Technique - O(n * log(n)) time and O(1) space
  // Solution 4: Using Hash Set - O(n) time and O(n) space

  // Leetcode 881: https://leetcode.com/problems/boats-to-save-people/description/
  // Solution 1: Sorting + Two-pointer
  // Time: O(n*log(n)), Space: O(1)
  public static int numRescueBoats(int[] people, int limit) {
    Arrays.sort(people);
    int totalBoats = 0, i=0, j=people.length-1;

    while (i <= j) {
      int sum = people[i] + people[j];

      if (sum > limit) {
        --j;
        ++totalBoats;
      } else {
        ++i;
        --j;
        ++totalBoats;
      }
    }

    return totalBoats;
  }

  public static void main(String[] args) {
    // Utility.measureTime("isLongPressedName", () -> isLongPressedName("saeed", "ssaaedd"));

    // Utility.measureTime("maxArea", () -> maxArea(new int[] { 1, 8, 6, 2, 5, 4, 8, 3, 7 }));

    // Utility.measureTime("sortedSquares", () -> sortedSquares(new int[] { -4, -1, 0, 3, 10 }));

    // Utility.measureTime("majorityElement1", () -> majorityElement1(new int[] { 3, 2, 3 }));
    // Utility.measureTime("majorityElement2", () -> majorityElement2(new int[] { 3, 2, 3 }));
    // Utility.measureTime("majorityElement3", () -> majorityElement3(new int[] { 3, 2, 3 }));

    // Utility.measureTime("majorityElement21", () -> majorityElement21(new int[] { 1, 2 }));
    // Utility.measureTime("majorityElement22", () -> majorityElement22(new int[] { 1, 2 }));

    // Utility.measureTime("countOccurence", () -> countOccurence(new int[] { 3, 4, 2, 2, 1, 2, 3, 3 }, 4));

    // Utility.measureTime("moreThanNdK", () -> moreThanNdK(new int[] { 3, 4, 2, 2, 1, 2, 3, 3 }, 4));

    // Utility.measureTime("nextGreaterElement", () -> nextGreaterElement(218765 ));
    // Utility.measureTime("nextGreaterElement", () -> nextGreaterElement(230241 ));
    // Utility.measureTime("nextGreaterElement", () -> nextGreaterElement(12443322 ));

    // Utility.measureTime("maximumProduct", () -> maximumProduct(new int[] {-1,-2,-3} ));
    // Utility.measureTime("maximumProduct", () -> maximumProduct(new int[] {1,2,3,4} ));

    // Utility.measureTime("maximumProduct2", () -> maximumProduct2(new int[] {-1,-2,-3} ));
    // Utility.measureTime("maximumProduct2", () -> maximumProduct2(new int[] {1,2,3,4} ));

    // Utility.measureTime("dominantIndex", () -> dominantIndex(new int[] {3,6,1,0} ));
    // Utility.measureTime("dominantIndex", () -> dominantIndex(new int[] {1,2,3,4} ));
    // Utility.measureTime("dominantIndex", () -> dominantIndex(new int[] {0,0,1,2} ));

    // Utility.measureTime("dominantIndex2", () -> dominantIndex2(new int[] {3,6,1,0} ));
    // Utility.measureTime("dominantIndex2", () -> dominantIndex2(new int[] {1,2,3,4} ));
    // Utility.measureTime("dominantIndex2", () -> dominantIndex2(new int[] {0,0,1,2} ));

    // Utility.measureTime("maxChunksToSorted", () -> maxChunksToSorted(new int[] {4,3,2,1,0} ));
    // Utility.measureTime("maxChunksToSorted", () -> maxChunksToSorted(new int[] {1,0,2,3,4} ));
    // Utility.measureTime("maxChunksToSorted", () -> maxChunksToSorted(new int[] {2,0,1} ));
    // Utility.measureTime("maxChunksToSorted", () -> maxChunksToSorted(new int[] {1,2,0,3} ));

    // Utility.measureTime("maxChunksToSorted21", () -> maxChunksToSorted21(new int[] {5,4,3,2,1} ));
    // Utility.measureTime("maxChunksToSorted21", () -> maxChunksToSorted21(new int[] {2,1,3,4,4} ));
    // Utility.measureTime("maxChunksToSorted21", () -> maxChunksToSorted21(new int[] {1,1,0,0,1} ));

    // Utility.measureTime("maxChunksToSorted22", () -> maxChunksToSorted22(new int[] {5,4,3,2,1} ));
    // Utility.measureTime("maxChunksToSorted22", () -> maxChunksToSorted22(new int[] {2,1,3,4,4} ));
    // Utility.measureTime("maxChunksToSorted22", () -> maxChunksToSorted22(new int[] {1,1,0,0,1} ));
    // Utility.measureTime("maxChunksToSorted22", () -> maxChunksToSorted22(new int[] {0,1,3,4,2} ));

    // Utility.measureTime("numSubarrayBoundedMax", () -> numSubarrayBoundedMax(new int[] {2,9,2,5,6}, 2, 8 ));
    // Utility.measureTime("numSubarrayBoundedMax", () -> numSubarrayBoundedMax(new int[] {2,1,4,3}, 2, 3 ));
    // Utility.measureTime("numSubarrayBoundedMax", () -> numSubarrayBoundedMax(new int[] {7,3,6,7,1}, 1, 4 ));
    // Utility.measureTime("numSubarrayBoundedMax", () -> numSubarrayBoundedMax(new int[] {73,55,36,5,55,14,9,7,72,52}, 32, 69 ));
    // Utility.measureTime("numSubarrayBoundedMax", () -> numSubarrayBoundedMax(new int[] {876,880,482,260,132,421,732,703,795,420,871,445,400,291,358,589,617,202,755,810,227,813,549,791,418,528,835,401,526,584,873,662,13,314,988,101,299,816,833,224,160,852,179,769,646,558,661,808,651,982,878,918,406,551,467,87,139,387,16,531,307,389,939,551,613,36,528,460,404,314,66,111,458,531,944,461,951,419,82,896,467,353,704,905,705,760,61,422,395,298,127,516,153,299,801,341,668,598,98,241}, 658, 719 ));
    
    // Utility.measureTime("wiggleSort", () -> wiggleSort(new int[] {3, 5, 2, 1, 6, 4}));
    // Utility.measureTime("wiggleSort", () -> wiggleSort(new int[] {1, 2, 2, 3, 3, 4, 5}));

    // Utility.measureTime("wiggleSort2", () -> wiggleSort2(new int[] {3, 5, 2, 1, 6, 4}));
    // Utility.measureTime("wiggleSort2", () -> wiggleSort2(new int[] {1, 2, 2, 3, 3, 4, 5}));
    
    // Utility.measureTime("reverseVowels", () -> reverseVowels("IceCreAm"));
    // Utility.measureTime("reverseVowels", () -> reverseVowels("leetcode"));
    
    // Utility.measureTime("productExceptSelf", () -> productExceptSelf(new int[] {1,2,3,4}));
    // Utility.measureTime("productExceptSelf", () -> productExceptSelf(new int[] {-1,1,0,-3,3}));

    // Utility.measureTime("maxDistToClosest", () -> maxDistToClosest(new int[] {1,0,0,0,1,0,1}));
    // Utility.measureTime("maxDistToClosest", () -> maxDistToClosest(new int[] {1,0,0,0}));
    // Utility.measureTime("maxDistToClosest", () -> maxDistToClosest(new int[] {0,1}));

    // Utility.measureTime("firstMissingPositive", () -> firstMissingPositive(new int[] {3,4,-1,1}));
    // Utility.measureTime("firstMissingPositive", () -> firstMissingPositive(new int[] {1,2,0}));
    // Utility.measureTime("firstMissingPositive", () -> firstMissingPositive(new int[] {7,8,9,11,12}));

    // Utility.measureTime("getModifiedArray", () -> getModifiedArray(
    //   5,
    //   new int[][] {
    //     {1,  3,  2},
    //     {2,  4,  3},
    //     {0,  2, -2}
    //   }
    // ));

    // Utility.measureTime("minTotalDistance", () -> minTotalDistance(
    //   new int[][] {
    //     {1, 0, 1},
    //     {0, 0, 0},
    //     {0, 1, 0}
    //   }
    // ));
    
    // Utility.measureTime("minMoves2", () -> minMoves2(new int[] {1,10,2,9}));
    // Utility.measureTime("minMoves2", () -> minMoves2(new int[] {1,100,100,100}));
    
    // Utility.measureTime("minMoves22", () -> minMoves22(new int[] {1,10,2,9}));
    // Utility.measureTime("minMoves22", () -> minMoves22(new int[] {1,100,100,100}));

    // Utility.measureTime("sortArrayByParity", () -> sortArrayByParity(new int[] {3,1,2,4}));

    // Utility.measureTime("maximumSwap", () -> maximumSwap(2736));
    // Utility.measureTime("maximumSwap", () -> maximumSwap(9973));

    Utility.measureTime("numRescueBoats", () -> numRescueBoats(new int[] {3,2,2,1}, 3));
  }
}
