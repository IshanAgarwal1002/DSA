#ifdef ONLINE_JUDGE
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#define NDEBUG
#endif

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <iomanip>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <stack>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define pb push_back
#define yn(cond) cout << &("NO\0YES"[3 * cond]) << "\n"
#define f(i, a, n) for (int i = a; i < n; i++)
// #define print(a) {for(auto it:a)cout<<it<<" ";cout<<endl;}

#define MOD 1000000007
#define mod_add(a, b, m) (((((a % m) + (b % m)) % m) + m) % m)
#define mod_mul(a, b, m) (((((a % m) * (b % m)) % m) + m) % m)

int maxArea(vector<int> &height)
{
  int i = 0, j = height.size() - 1, ans = 0;

  while (i < j)
  {
    ans = max(ans, (j - i) * min(height[i], height[j]));
    if (height[i] < height[j])
      ++i;
    else
      --j;
  }

  return ans;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
  cout << maxArea(height);

  return 0;
}