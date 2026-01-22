#include<bits/stdc++.h>
#define L(i, j, k) for(int i = (j); i <= (k); ++i)
#define R(i, j, k) for(int i = (j); i >= (k); --i)
#define ll long long
#define sz(a) ((int) (a).size())
#define vi vector < int > 
#define me(a, x) memset(a, x, sizeof(a))
#define ull unsigned long long
#define ld __float128
using namespace std;
const int N = 1e6 + 7, mod = 998244353;
int n, k, a[N], que[N], rq[N], tp;
int Q[N], TP;
int f[1 << 4];
int cnt[10], dp[10], pw[10], C[10][10], ns;
int sum[1 << 16];
void solve(int x) {
	if(x == TP) {
		L(i, 0, (1 << tp) - 1) {
			int qwq = 0;
			L(j, 0, tp - 1) if(i >> j & 1) qwq |= 1 << rq[j];
			f[i] = sum[qwq];
		}
		L(i, 0, tp - 1) L(j, 0, (1 << tp) - 1) if(!(j >> i & 1)) f[j] -= f[j + (1 << i)];
		int s = 0, all = (1 << tp) - 1;
		L(i, 0, all) (s += (ll) f[i] * f[all ^ i] % mod) %= mod; 
		me(dp, 0);
		dp[0] = 1;
		L(i, 0, tp - 1) {
			pw[0] = 1;
			L(x, 1, k) pw[x] = (ll) pw[x - 1] * (1 << que[i]) % mod; 
			R(x, k, 0) if(dp[x]) {
				L(y, 1, k - x) 
					(dp[x + y] += (ll) dp[x] * C[k - x][y] % mod * pw[y] % mod) %= mod;
				dp[x] = 0;
			}
		}
		(ns += (ll) s * dp[k] % mod) %= mod;
		return ;
	}
	L(bt, 1, 15) if(__builtin_popcount(bt) + tp <= k) {
		L(i, 0, 3) if(bt >> i & 1) que[tp] = Q[x] + i, rq[tp] = x * 4 + i, tp++;
		solve(x + 1);
		L(i, 0, 3) if(bt >> i & 1) --tp;
	} 
}
void dfs(int x) {
	if(x == 32) {
		me(sum, 0); 
		L(i, 1, n) {
			int s = 0;
			L(j, 0, TP - 1) s += (a[i] >> Q[j] & 15) << (j * 4);
			sum[s] += 1; 
		}
		L(i, 0, TP * 4 - 1) 
			for(int j = 0; j < (1 << (TP * 4)); j += (1 << (i + 1))) 
				L(k, j, j + (1 << i) - 1) 
					sum[k] += sum[k + (1 << i)];
		solve(0); 
		return ;
	}
	dfs(x + 4);
	if(TP < k) Q[TP++] = x, dfs(x + 4), --TP;
}
int main() {
	freopen("c4.in", "r", stdin);
	freopen("c4.out", "w", stdout);
	ios :: sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	L(i, 0, 5) C[i][0] = 1;
	L(i, 1, 5) L(j, 1, 5) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
	cin >> n >> k;
	L(i, 1, n) cin >> a[i];
	dfs(0);
	cout << ns << '\n';
	return 0;
} 
