#include <bits/stdc++.h>
using namespace std;
const int N = 505;
int T, n, a[N], dp[N][N], mx[N][N], ans;
int main() {
	freopen ("swap.in", "r", stdin);
	freopen ("swap.out", "w", stdout);
	cin >> T;
	while (T --) {
		scanf ("%d", &n);
		for (int i=1; i<=n; i++)
			scanf ("%d", &a[i]);
		for (int j=0; j<=n; j++)
			for (int k=0; k<=n; k++)
				dp[j][k] = mx[j][k] = - 2e9;
		dp[1][1] = a[1], dp[2][0] = a[2];
		for (int i=2; i<=n; i++) {
			for (int j=1; j<=min(i<<1,n); j++)
				for (int k=0; k<i; k++)
					mx[j][k] = max(mx[j-1][k], dp[j][k]);
			for (int j=1; j<=min(i<<1,n); j++)
				for (int k=0; k<=i; k++) {
					int _k = k + j - i - 1;
					if (_k >= max(k - 1, 0) && _k < i)
						dp[j][k] = max(dp[j][k], mx[j-1][_k]);
					dp[j][k] += a[j];
				}
		} ans = 0;
		for (int j=1; j<=n; j++)
			for (int k=0; k<=n; k++)
				ans = max(ans, dp[j][k]);
		printf ("%d\n", ans);
	}
}
