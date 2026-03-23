import java.util.AbstractMap.SimpleEntry;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;

class Solution {

  class Pair<K, V> extends SimpleEntry<K, V> {

    public Pair(K key, V value) {
      super(key, value);
    }
  }

  // https://leetcode.com/problems/two-sum/
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
  public int maxArea(int[] height) {
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
  public int square(int n) {
    return n * n;
  }

  public int[] sortedSquares(int[] nums) {
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
  public int majorityElement1(int[] nums) {
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
  public int majorityElement2(int[] nums) {
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
  public int majorityElement3(int[] nums) {
    Arrays.sort(nums);
    int n = nums.length;
    return nums[n / 2];
  }

  // Leetcode 229: https://leetcode.com/problems/majority-element-ii/description/
  // Solution 1: Hash Map
  // Time: O(N), Space: O(N)
  public List<Integer> majorityElement21(int[] nums) {
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
  public List<Integer> majorityElement22(int[] nums) {
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

  public static void main(String[] args) {
    System.out.println(isLongPressedName("saeed", "ssaaedd"));
  }
}
