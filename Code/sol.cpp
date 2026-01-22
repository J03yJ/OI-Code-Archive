#include <bits/stdc++.h>
#define lb(x) (x & -x)
#define rep(i, a, b) for (ll i = (a); i <= (b); i++)
using namespace std;
using ll = long long;
constexpr ll N = 25, M = 220, P2N = 32778;
constexpr ll mod = 1000000007;
ll n, m, f[P2N], g[P2N], p2[M], G[P2N], cnt[P2N];
int main() {
   ios::sync_with_stdio(0), cin.tie(0);
   cin >> n >> m;
   p2[0] = 1;
   rep(i, 1, m) {
      ll u, v;
      cin >> u >> v;
      G[u - 1] += 1ll << (v - 1);
      p2[i] = p2[i - 1] * 2 % mod;
   }
   ll p2n = 1ll << n;
   rep(i, 0, p2n - 1) {
      for (ll j = i; j; j = (j - 1) & i) {
         cnt[j] = 0;
         rep(k, 0, n - 1) {
            if (i >> k & 1) {
               cnt[j] += __builtin_popcountll(G[k] & j);
            }
         }
      }
      g[i] = p2[cnt[i]];
      for (ll j = (i - 1) & i; j; j = (j - 1) & i) {
         (g[i] -= p2[cnt[i ^ j]] * g[j]) %= mod;
      }
      cout<<g[i]<<endl;
   }
   rep(i, 0, p2n - 1) {
      f[i] = g[i];
      ll ni = i ^ lb(i);
      for (ll j = (ni - 1) & ni; ni; j = (j - 1) & ni) {
         (f[i] += g[ni ^ j] * f[j ^ lb(i)]) %= mod;
         if (!j) {
            break;
         }
      }
      cout<<f[i]<<endl;
   }
   cout << (f[p2n - 1] + mod) % mod << '\n';
   return 0;
}