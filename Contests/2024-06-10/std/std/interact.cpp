#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 6, B = 1e9 + 7, MOD = 998244353; const ll P = (1ull << 63) - 25;
int T, n, m, F[N]; ll h[N];
int read() {
	int s = 0; char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s;
}
int main() {
	freopen ("interact.in", "r", stdin);
	freopen ("interact.out", "w", stdout);
	for (int i=F[0]=1; i<=300000; i++)
		F[i] = 1ll * F[i-1] * i % MOD;
	T = read();
	while (T --) {
		n = read(), m = read();
		for (int i=1; i<=n<<1; i++)
			h[i] = 0;
		while (m --)
			for (int i=1; i<=n<<1; i++)
				h[i] = ((__int128) h[i] * B + read()) % P;
		sort (h+1, h+n+1), sort (h+n+1, h+(n<<1)+1);
		int ans = 1;
		for (int i=1; i<=n; i++)
			if (h[i] ^ h[n+i])
				{ ans = 0; break; }
		if (ans) for (int i=1; i<=n; ) {
			int j = i;
			while (j <= n && h[j] == h[i]) j ++;
			ans = 1ll * ans * F[j-i] % MOD, i = j;
		} printf ("%d\n", ans);
	}
}
