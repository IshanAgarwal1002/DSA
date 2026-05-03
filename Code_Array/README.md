# Kadane's Algorithm

## Overview

Kadane's algorithm is an efficient **dynamic programming** technique used to find the maximum sum of a contiguous subarray within a one-dimensional numerical array. It operates in **O(n)** time complexity by traversing the array once, keeping track of the maximum sum ending at the current position and the overall maximum sum found so far.

---

## Key Concepts and Logic

### Goal
Find the subarray (contiguous) with the largest sum.

### Core Idea
For each element, decide whether to:
- Start a new subarray, or
- Extend the existing one

### Formula

$$\text{maxEndingHere} = \max(\text{currentElement}, \text{maxEndingHere} + \text{currentElement})$$

### Result
The maximum value obtained for `maxEndingHere` during the traversal is the result.

### Complexity
- **Time:** $O(n)$
- **Space:** $O(1)$

---

## Algorithm Approach

1. Initialize `maxEndingHere` and `maxSoFar` to the first element
2. Iterate through the array starting from the second element
3. At each position, decide whether to extend the current subarray or start a new one
4. Update `maxSoFar` if we find a larger sum
5. Return `maxSoFar`

---

## Example

For array `[-2, 1, -3, 4, -1, 2, 1, -5, 4]`:

| Index | Element | maxEndingHere | maxSoFar |
|-------|---------|---------------|----------|
| 0     | -2      | -2            | -2       |
| 1     | 1       | 1             | 1        |
| 2     | -3      | -2            | 1        |
| 3     | 4       | 4             | 4        |
| 4     | -1      | 3             | 4        |
| 5     | 2       | 5             | 5        |
| 6     | 1       | 6             | 6        |
| 7     | -5      | 1             | 6        |
| 8     | 4       | 5             | 6        |

**Result:** Maximum sum = `6` (subarray: `[4, -1, 2, 1]`)
