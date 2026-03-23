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

void solve()
{
  int n;
  cin >> n;
  unordered_map<int, int> m;
  vector<int> result(n);

  for (int i = 1; i <= n; i++)
  {
    m[i] = i;
  }
  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= n; j++)
    {
      char x;
      cin >> x;
      if (i == j)
      {
        continue;
      }
      // cout << "x: " << x << " i: " << i << " j: " << j << endl;
      if ((x == '1' && ((i < j && m[i] > m[j]) || (i > j && m[i] < m[j]))) || (x == '0' && ((i < j && m[i] < m[j]) || (i > j && m[i] > m[j]))))
      {
        int temp = m[i];
        m[i] = m[j];
        m[j] = temp;
      }
    }
  }
  for (auto it : m)
  {
    result[it.second - 1] = it.first;
  }
  for (int i : result)
  {
    cout << i << " ";
  }
  cout << "\n";
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int t;
  cin >> t;

  while (t--)
  {
    solve();
  }

  return 0;
}